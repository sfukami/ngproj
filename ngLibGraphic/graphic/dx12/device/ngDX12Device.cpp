/*!
* @file		ngDX12Device.cpp
* @brief	DX12デバイス
* @date		2017-08-23
* @author	s.fukami
*/

#include <d3d12.h>
#include <DXGI1_4.h>	// for IDXGIFactory4
#include "ngLibGraphic/common/ngCommon.h"
#include "ngLibGraphic/graphic/dx12/common/ngDX12Common.h"
#include "ngDX12Device.h"

namespace ng
{
	const D3D_FEATURE_LEVEL CDX12Device::CreateParam::FeatureLevelDefault = D3D_FEATURE_LEVEL_12_1;

	CDX12Device::CreateParam::CreateParam()
		: featureLevel(FeatureLevelDefault)
		, isUseWarpDevice(false)
	{
	}

	CDX12Device::CreateDesc::CreateDesc()
	{
		Reset();
	}

	void CDX12Device::CreateDesc::Set(D3D_FEATURE_LEVEL level, IDXGIAdapter1* pIAdapter)
	{
		featureLevel = level;
		pIAdapter->GetDesc1(&adapterDesc);

		if(adapterDesc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
			driverType = eDX12DriverType::SOFTWARE;
		} else {
			driverType = eDX12DriverType::HARDWARE;
		}
	}

	void CDX12Device::CreateDesc::Reset()
	{
		driverType = eDX12DriverType::UNKNOWN;
		featureLevel = D3D_FEATURE_LEVEL_NONE;

		NG_ZERO_MEMORY(&adapterDesc, sizeof(adapterDesc));
	}

	CDX12Device::CDX12Device()
	{
	}

	CDX12Device::~CDX12Device()
	{
		Destroy();
	}

	NG_ERRCODE CDX12Device::Create(const CreateParam& param)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// DXGI1.1ファクトリを生成
		IDXGIFactory4* pIFactory = nullptr;
		if(NG_FAILED(ret = CreateDXGIFactory1(IID_PPV_ARGS(&pIFactory)))) {
			NG_DXERR("DX12Device", ret, CreateDXGIFactory1, "DXGI1.1ファクトリの作成に失敗");
			return ret;
		}

		ret = eNG_E_FAIL;

		// Warpデバイス生成
		if(param.isUseWarpDevice) {
			IDXGIAdapter1* pIAdapter = nullptr;
			// Warpデバイス対応アダプタの列挙
			if(NG_FAILED(ret = pIFactory->EnumWarpAdapter(IID_PPV_ARGS(&pIAdapter)))) {
				NG_DXERR("DX12Device", ret, EnumWarpAdapter, "Warpデバイス対応アダプタの列挙に失敗");
				return ret;
			}

			// デバイス生成
			ret = _createDeviceInOrder(pIAdapter, param.featureLevel);
			NG_SAFE_RELEASE(pIAdapter);
		}
		// その他デバイス生成
		else {
			// 指定の機能レベルでのデバイス生成を試す
			IDXGIAdapter1* pIAdapter = nullptr;
			for(int i = 0; pIFactory->EnumAdapters1(i, &pIAdapter) != DXGI_ERROR_NOT_FOUND; i++)
			{
				ret = _createDevice(pIAdapter, param.featureLevel);
				NG_SAFE_RELEASE(pIAdapter);
				if(NG_SUCCEEDED(ret)) {
					break;
				}
			}
			// 機能レベルを優先してデバイス生成
			if(NG_FAILED(ret)) {
				for(int i = 0; pIFactory->EnumAdapters1(i, &pIAdapter) != DXGI_ERROR_NOT_FOUND; i++)
				{
					ret = _createDeviceInOrder(pIAdapter, D3D_FEATURE_LEVEL_NONE);
					NG_SAFE_RELEASE(pIAdapter);
					if(NG_SUCCEEDED(ret)) {
						break;
					}
				}
			}
		}
		
		return ret;
	}

	void CDX12Device::Destroy()
	{
		NG_SAFE_RELEASE(m_pIDevice);
	}

	const CDX12Device::CreateDesc& CDX12Device::GetCreateDesc() const
	{
		return m_createDesc;
	}

	bool CDX12Device::IsValid() const
	{
		return (m_pIDevice != nullptr);
	}

	ID3D12Device* CDX12Device::Interface()
	{
		return m_pIDevice;
	}
	const ID3D12Device* CDX12Device::Interface() const
	{
		return m_pIDevice;
	}

	NG_ERRCODE CDX12Device::_createDevice(IDXGIAdapter1* pIAdapter, D3D_FEATURE_LEVEL featureLevel)
	{
		m_createDesc.Set(featureLevel, pIAdapter);

	#if defined(NG_DEBUG)
		{
			const DXGI_ADAPTER_DESC1& adapterDesc = m_createDesc.adapterDesc;
			NG_LOG("DX12Device",
				L"Creating device..."
				"\n FeatureLevel:%#0x"		// TODO: 文字列にしたい
				"\n <DXGI_ADAPTER_DESC>"
				"\n\tDescription:%s"
				"\n\tVendorId:%u DeviceId:%u SubSysId:%u Revision:%u"
				"\n\tDedicatedVideoMemory:%zu"
				"\n\tDedicatedSystemMemory:%zu"
				"\n\tSharedSystemMemory:%zu"
				"\n\tLUID LowPart:%d HighPart:%ld"
				"\n\tAdapterFlags:%#0x"
				, m_createDesc.featureLevel
				, adapterDesc.Description
				, adapterDesc.VendorId
				, adapterDesc.DeviceId
				, adapterDesc.SubSysId
				, adapterDesc.Revision
				, adapterDesc.DedicatedVideoMemory
				, adapterDesc.DedicatedSystemMemory
				, adapterDesc.SharedSystemMemory
				, adapterDesc.AdapterLuid.LowPart, adapterDesc.AdapterLuid.HighPart
				, adapterDesc.Flags
				);
		}
	#endif

		NG_ERRCODE ret = eNG_E_FAIL;
		if(featureLevel != D3D_FEATURE_LEVEL_NONE) {
			ret = D3D12CreateDevice(pIAdapter, featureLevel, IID_PPV_ARGS(&m_pIDevice));
		}

		if(NG_FAILED(ret)) {
			m_createDesc.Reset();
			return ret;
		}

		return ret;
	}

	NG_ERRCODE CDX12Device::_createDeviceInOrder(IDXGIAdapter1* pIAdapter, D3D_FEATURE_LEVEL featureLevel)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;
		D3D_FEATURE_LEVEL tryLevel = featureLevel;

		// まずは指定の機能レベルでデバイスの生成を試みる
		if(NG_SUCCEEDED(ret = _createDevice(pIAdapter, tryLevel))) {
			return ret;
		}

		// 指定の機能レベル以下のデバイスの生成を試みる
		const D3D_FEATURE_LEVEL* pSupportedFeatureLevels = GetSupportedDX12FeatureLevels();
		for(int i = 0; pSupportedFeatureLevels[i] != D3D_FEATURE_LEVEL_NONE; i++)
		{
			tryLevel = pSupportedFeatureLevels[i];
			if(featureLevel != D3D_FEATURE_LEVEL_NONE) {
				if(tryLevel > featureLevel) {
					continue;
				}
			}

			if(NG_SUCCEEDED(ret = _createDevice(pIAdapter, tryLevel))) {
				break;
			}
		}

		return ret;
	}

	NG_ERRCODE CDX12Device::_checkCreatableDevice(IDXGIAdapter1* pIAdapter, D3D_FEATURE_LEVEL featureLevel)
	{
		return D3D12CreateDevice(pIAdapter, featureLevel, _uuidof(ID3D12Device), nullptr);
	}

}	// namespace ng
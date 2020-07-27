/*!
* @file		ngDX12RootSignature.cpp
* @brief	DX12ルートシグネチャ
* @date		2017-09-24
* @author	s.fukami
*/

#include <d3d12.h>
#include <d3dx12.h>	// for CD3DX12_ROOT_SIGNATURE_DESC
#include "ngLibCore/common/ngCommon.h"
#include "../common/ngDX12Common.h"
#include "../device/ngDX12Device.h"
#include "ngDX12RootSignature.h"

namespace ng
{
	CDX12RootSignature::CDX12RootSignature()
		: m_pISignature(nullptr)
	{
	}

	CDX12RootSignature::~CDX12RootSignature()
	{
		Destroy();
	}

	NG_ERRCODE CDX12RootSignature::Create(CDX12Device& device, const CD3DX12_ROOT_SIGNATURE_DESC& desc)
	{
		NG_ASSERT(!IsValid());

		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		ID3D12Device* pIDevice = device.Interface();
		ID3DBlob* pIBuffer = nullptr;
		ID3DBlob* pIError = nullptr;

		// ルートシグネチャ生成のためのバッファを取得
		if(NG_FAILED(ret = D3D12SerializeRootSignature(
			&desc,
			D3D_ROOT_SIGNATURE_VERSION_1,
			&pIBuffer,
			&pIError
			))) {
			NG_DXERRLOG("DX12RootSignature", ret, D3D12SerializeRootSignature, "バッファの取得に失敗しました. pIError:%s", 
				pIError ? PointerCast<const char*>(pIError->GetBufferPointer()) : "none"
				);
			return ret;
		}

		// ルートシグネチャ生成
		if(NG_FAILED(ret = pIDevice->CreateRootSignature(
			0,
			pIBuffer->GetBufferPointer(),
			pIBuffer->GetBufferSize(),
			IID_PPV_ARGS(&m_pISignature)
			))) {
			NG_DXERRLOG("DX12RootSignature", ret, CreateRootSignature, "ルートシグネチャの生成に失敗しました.");
			return ret;
		}

		return ret;
	}

	void CDX12RootSignature::Destroy()
	{
		NG_SAFE_RELEASE(m_pISignature);
	}
	
	bool CDX12RootSignature::IsValid() const
	{
		return (m_pISignature != nullptr);
	}

	ID3D12RootSignature* CDX12RootSignature::Interface()
	{
		return m_pISignature;
	}
	const ID3D12RootSignature* CDX12RootSignature::Interface() const
	{
		return m_pISignature;
	}

}	// namespace ng
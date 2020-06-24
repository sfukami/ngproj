/*!
* @file		ngDX12DepthStencil.cpp
* @brief	DX12深度ステンシル
* @date		2019-08-12
* @author	s.fukami
*/

#include <d3dx12.h>
#include "ngLibCore/common/ngCommon.h"
#include "../../common/ngDX12Common.h"
#include "../../device/ngDX12Device.h"
#include "ngDX12DepthStencil.h"

namespace ng
{
	CDX12DepthStencil::CDX12DepthStencil()
	{
	}
	CDX12DepthStencil::~CDX12DepthStencil()
	{
		Destroy();
	}

	NG_ERRCODE CDX12DepthStencil::Create(
		CDX12Device& device,
		u32 width,
		u32 height
		)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// DX12ディスクリプタヒープ生成
		if(NG_FAILED(ret = m_descHeap.Create(
			device,
			D3D12_DESCRIPTOR_HEAP_TYPE_DSV,
			1,
			D3D12_DESCRIPTOR_HEAP_FLAG_NONE
			))) {
			return ret;
		}

		// リソース生成
		CD3DX12_HEAP_PROPERTIES heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
		CD3DX12_RESOURCE_DESC resDesc = CD3DX12_RESOURCE_DESC::Tex2D(
			DXGI_FORMAT_D32_FLOAT,
			static_cast<u64>(width), height,
			1,		// arraySize
			0,		// mipLevels
			1,		// sampleCount
			0,		// sampleQuality
			D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL
			);
		D3D12_CLEAR_VALUE clearValue{};
		clearValue.Format = resDesc.Format;
		clearValue.DepthStencil.Depth = 1.f;
		clearValue.DepthStencil.Stencil = 0;

		if(NG_FAILED(ret = m_resource.Create(
			device,
			heapProp,
			resDesc,
			D3D12_RESOURCE_STATE_DEPTH_WRITE,
			&clearValue
			))) {
			return ret;
		}

		// DX12深度ステンシルビュー生成
		D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
		dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
		dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Flags = D3D12_DSV_FLAG_NONE;

		device.Interface()->CreateDepthStencilView(
			m_resource.Interface(),
			&dsvDesc,
			GetCPUDescriptorHandle()
			);

		return ret;
	}

	void CDX12DepthStencil::Destroy()
	{
		m_resource.Destroy();
		m_descHeap.Destroy();
	}
	
	D3D12_CPU_DESCRIPTOR_HANDLE CDX12DepthStencil::GetCPUDescriptorHandle()
	{
		return m_descHeap.GetCPUDescriptorHandleForHeapStart();
	}

	bool CDX12DepthStencil::IsValid() const
	{
		return m_resource.IsValid();
	}

	CDX12Resource& CDX12DepthStencil::GetResource()
	{
		return m_resource;
	}
	const CDX12Resource& CDX12DepthStencil::GetResource() const
	{
		return m_resource;
	}

}	// namespace ng
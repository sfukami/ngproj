/*!
* @file		ngDX12RenderTarget.cpp
* @brief	DX12レンダーターゲット
* @date		2017-09-19
* @author	s.fukami
*/

#include <d3d12.h>
#include <DXGI1_2.h>	// for IDXGISwapChain1
#include <DXGI1_4.h>	// for IDXGISwapChain3
#include "ngLibCore/common/ngCommon.h"
#include "../../common/ngDX12Common.h"
#include "../../device/ngDX12Device.h"
#include "../../swapchain/ngDX12SwapChain.h"
#include "../../command/list/ngDX12CommandList.h"
#include "ngDX12RenderTarget.h"
#include "../../barrier/ngDX12ResourceBarrierTransition.h"

namespace ng
{
	CDX12RenderTarget::CDX12RenderTarget()
		: m_pIResource(nullptr)
	{
	}

	CDX12RenderTarget::~CDX12RenderTarget()
	{
		Destroy();
	}

	NG_ERRCODE CDX12RenderTarget::Create(CDX12Device& device, CDX12SwapChain& swapChain, u32 bufferIndex)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// DX12ディスクリプタヒープ生成
		if(NG_FAILED(ret = m_descriptorHeap.Create(
			device,
			D3D12_DESCRIPTOR_HEAP_TYPE_RTV,
			1,
			D3D12_DESCRIPTOR_HEAP_FLAG_NONE
			))) {
			return ret;
		}

		// スワップチェインよりバックバッファを取得
		if(NG_FAILED(ret = swapChain.Interface()->GetBuffer(bufferIndex, IID_PPV_ARGS(&m_pIResource)))) {
			NG_DXERRLOG("DX12RenderTarget", ret, GetBuffer, "スワップチェインよりバックバッファの取得に失敗しました.");
			return ret;
		}

		// DX12レンダーターゲットビュー生成
		D3D12_CPU_DESCRIPTOR_HANDLE RTVHndl = GetCPUDescriptorHandle();
		device.Interface()->CreateRenderTargetView(m_pIResource, nullptr, RTVHndl);

		return ret;
	}
	
	void CDX12RenderTarget::GetResourceBarrierForSetRenderTarget(CDX12ResourceBarrierTransition* pDest)
	{
		pDest->Initialize(
			m_pIResource,
			D3D12_RESOURCE_STATE_PRESENT,
			D3D12_RESOURCE_STATE_RENDER_TARGET
			);
	}

	void CDX12RenderTarget::GetResourceBarrierForPresent(CDX12ResourceBarrierTransition* pDest)
	{
		pDest->Initialize(
			m_pIResource,
			D3D12_RESOURCE_STATE_RENDER_TARGET,
			D3D12_RESOURCE_STATE_PRESENT
			);
	}

	void CDX12RenderTarget::Destroy()
	{
		NG_SAFE_RELEASE(m_pIResource);
		m_descriptorHeap.Destroy();
	}

	D3D12_CPU_DESCRIPTOR_HANDLE CDX12RenderTarget::GetCPUDescriptorHandle()
	{
		return m_descriptorHeap.GetCPUDescriptorHandleForHeapStart();
	}

	bool CDX12RenderTarget::IsValid() const
	{
		return (m_pIResource != nullptr);
	}

	ID3D12Resource* CDX12RenderTarget::Interface()
	{
		return m_pIResource;
	}
	const ID3D12Resource* CDX12RenderTarget::Interface() const
	{
		return m_pIResource;
	}

}	// namespace ng
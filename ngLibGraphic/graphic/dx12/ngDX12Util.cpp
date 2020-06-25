/*!
* @file		ngDX12Util.cpp
* @brief	DX12 ユーティリティ
* @date		2020-06-24
* @author	s.fukami
*/

#include "ngDX12Util.h"
#include "ngDX12Graphic.h"
#include "../ngGraphicManager.h"

namespace ng
{
	NG_DECL CDX12Graphic* GetDX12Graphic()
	{
		if(!CGraphicManager::IsExistInstance()) return nullptr;

		IGraphic* pGraphic = CGraphicManager::GetInstance().GetGraphic();

		return PointerCast<CDX12Graphic*>(pGraphic);
	}

	NG_DECL CDX12Device* GetDX12Device()
	{
		CDX12Graphic* pDX12Graphic = GetDX12Graphic();

		if(pDX12Graphic == nullptr) return nullptr;

		return &pDX12Graphic->GetDevice();
	}

	NG_DECL CDX12CommandAllocator* GetDX12CommandAllocator(u32 index)
	{
		CDX12Graphic* pDX12Graphic = GetDX12Graphic();

		if(pDX12Graphic == nullptr) return nullptr;

		return pDX12Graphic->GetCommandAllocatorMngr().GetCommandAllocator(index);
	}

	NG_DECL CDX12CommandList* GetDX12CommandList(u32 index)
	{
		CDX12Graphic* pDX12Graphic = GetDX12Graphic();

		if(pDX12Graphic == nullptr) return nullptr;

		return pDX12Graphic->GetCommandListMngr().GetCommandList(index);
	}

	NG_DECL CDX12CommandQueue* GetDX12CommandQueue(eDX12CommandQueueType type)
	{
		CDX12Graphic* pDX12Graphic = GetDX12Graphic();

		if(pDX12Graphic == nullptr) return nullptr;

		return pDX12Graphic->GetCommandQueueMngr().GetCommandQueue(type);
	}

	NG_DECL CDX12SwapChain* GetDX12SwapChain()
	{
		CDX12Graphic* pDX12Graphic = GetDX12Graphic();

		if(pDX12Graphic == nullptr) return nullptr;

		return &pDX12Graphic->GetSwapChain();
	}

	NG_DECL CDX12RenderTarget* GetDX12RenderTarget(eDX12RenderTargetId id)
	{
		CDX12Graphic* pDX12Graphic = GetDX12Graphic();

		if(pDX12Graphic == nullptr) return nullptr;

		return pDX12Graphic->GetRenderTargetMngr().GetRenderTarget(id);
	}

	NG_DECL CDX12DepthStencil* GetDX12DepthStencil(eDX12DepthStencilId id)
	{
		CDX12Graphic* pDX12Graphic = GetDX12Graphic();

		if(pDX12Graphic == nullptr) return nullptr;

		return pDX12Graphic->GetDepthStencilMngr().GetDepthStencil(id);
	}

	NG_DECL CDX12RenderTarget* GetDX12RenderTargetOfCurrentBackBuffer()
	{
		ng::CDX12SwapChain* pSwapChain = ng::GetDX12SwapChain();

		if(pSwapChain == nullptr) return nullptr;

		ng::u32 frameIndex = pSwapChain->GetCurrentBackBufferIndex();
		return ng::GetDX12RenderTarget(static_cast<ng::eDX12RenderTargetId>(frameIndex));
	}

}	// namespace ng
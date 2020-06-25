/*!
* @file		ngDX12Util.cpp
* @brief	DX12 ユーティリティ
* @date		2020-06-24
* @author	s.fukami
*/

#include "ngDX12Util.h"
#include "ngDX12Graphic.h"
#include "swapchain/ngDX12SwapChain.h"
#include "command/allocator/ngDX12CommandAllocator.h"
#include "command/queue/ngDX12CommandQueue.h"
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

	NG_DECL void ResetAllDX12CommandAllocator()
	{
		CDX12Graphic* pDX12Graphic = GetDX12Graphic();

		if(pDX12Graphic == nullptr) return;

		CDX12CommandAllocatorManager& cmdAllocMngr = pDX12Graphic->GetCommandAllocatorMngr();

		for(u32 i = 0; i < cmdAllocMngr.GetCommandAllocatorMax(); i++)
		{
			CDX12CommandAllocator* pCmdAlloc = cmdAllocMngr.GetCommandAllocator(i);
			if(pCmdAlloc != nullptr) {
				pCmdAlloc->Reset();
			}
		}
	}

	NG_DECL void ExecuteAllDX12CommandList(eDX12CommandQueueType type)
	{
		CDX12Graphic* pDX12Graphic = GetDX12Graphic();

		if(pDX12Graphic == nullptr) return;

		CDX12CommandListManager& cmdListMngr = pDX12Graphic->GetCommandListMngr();

		CDX12CommandList* pCmdLists[ NG_DX12_COMMAND_LIST_MAX ] = {nullptr};
		u32 count = 0;
		for(u32 i = 0; i < cmdListMngr.GetCommandListMax(); i++)
		{
			CDX12CommandList* pCmdList = cmdListMngr.GetCommandList(i);
			if(pCmdList != nullptr) {
				pCmdLists[ count ] = pCmdList;
				count++;
			}
		}

		CDX12CommandQueue* pCmdQueue = GetDX12CommandQueue(type);
		pCmdQueue->ExecuteCommandLists(pCmdLists, count);
	}

}	// namespace ng
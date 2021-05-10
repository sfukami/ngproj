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
#include "command/list/ngDX12CommandList.h"
#include "command/queue/ngDX12CommandQueue.h"
#include "barrier/ngDX12ResourceBarrierTransition.h"
#include "../ngGraphicManager.h"

namespace ng
{
	namespace DX12Util
	{
		NG_DECL CDX12Graphic* GetGraphic()
		{
			if(!CGraphicManager::IsExistInstance()) return nullptr;

			IGraphic* pGraphic = CGraphicManager::GetInstance().GetGraphic();

			return PointerCast<CDX12Graphic*>(pGraphic);
		}

		NG_DECL CDX12Device* GetDevice()
		{
			CDX12Graphic* pDX12Graphic = GetGraphic();

			if(pDX12Graphic == nullptr) return nullptr;

			return &pDX12Graphic->GetDevice();
		}

		NG_DECL CDX12CommandAllocator* GetCommandAllocator(u32 index)
		{
			CDX12Graphic* pDX12Graphic = GetGraphic();

			if(pDX12Graphic == nullptr) return nullptr;

			return pDX12Graphic->GetCommandAllocatorMngr().GetCommandAllocator(index);
		}

		NG_DECL CDX12CommandList* GetCommandList(u32 index)
		{
			CDX12Graphic* pDX12Graphic = GetGraphic();

			if(pDX12Graphic == nullptr) return nullptr;

			return pDX12Graphic->GetCommandListMngr().GetCommandList(index);
		}

		NG_DECL CDX12CommandQueue* GetCommandQueue(eDX12CommandQueueType type)
		{
			CDX12Graphic* pDX12Graphic = GetGraphic();

			if(pDX12Graphic == nullptr) return nullptr;

			return pDX12Graphic->GetCommandQueueMngr().GetCommandQueue(type);
		}

		NG_DECL CDX12SwapChain* GetSwapChain()
		{
			CDX12Graphic* pDX12Graphic = GetGraphic();

			if(pDX12Graphic == nullptr) return nullptr;

			return &pDX12Graphic->GetSwapChain();
		}

		NG_DECL CDX12RenderTarget* GetRenderTarget(eDX12RenderTargetId id)
		{
			CDX12Graphic* pDX12Graphic = GetGraphic();

			if(pDX12Graphic == nullptr) return nullptr;

			return pDX12Graphic->GetRenderTargetMngr().GetRenderTarget(id);
		}

		NG_DECL CDX12DepthStencil* GetDepthStencil(eDX12DepthStencilId id)
		{
			CDX12Graphic* pDX12Graphic = GetGraphic();

			if(pDX12Graphic == nullptr) return nullptr;

			return pDX12Graphic->GetDepthStencilMngr().GetDepthStencil(id);
		}

		NG_DECL CDX12RenderTarget* GetRenderTargetOfCurrentBackBuffer()
		{
			ng::CDX12SwapChain* pSwapChain = ng::DX12Util::GetSwapChain();

			if(pSwapChain == nullptr) return nullptr;

			ng::u32 frameIndex = pSwapChain->GetCurrentBackBufferIndex();
			return ng::DX12Util::GetRenderTarget(static_cast<ng::eDX12RenderTargetId>(frameIndex));
		}

		NG_DECL void ResetAllCommandAllocator()
		{
			CDX12Graphic* pDX12Graphic = GetGraphic();

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

		NG_DECL void ExecuteAllCommandList(eDX12CommandQueueType type)
		{
			CDX12Graphic* pDX12Graphic = GetGraphic();

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

			CDX12CommandQueue* pCmdQueue = GetCommandQueue(type);
			pCmdQueue->ExecuteCommandLists(pCmdLists, count);
		}

		NG_DECL void SetRenderTarget(CDX12CommandList* pCmdList, CDX12RenderTarget* pRT, CDX12DepthStencil* pDS)
		{
			// リソースバリア設定
			{
				CDX12ResourceBarrierTransition barrier;
				pRT->GetResourceBarrierForSetRenderTarget(&barrier);
				pCmdList->ResourceBarrier(barrier);
			}

			// レンダーターゲット設定
			D3D12_CPU_DESCRIPTOR_HANDLE cpuDescriptorHandle = pDS->GetCPUDescriptorHandle();
			pCmdList->SetRenderTarget(
				pRT->GetCPUDescriptorHandle(),
				(pDS != nullptr) ? &cpuDescriptorHandle : nullptr
				);
		}

		NG_DECL void SetRenderTargetToPresent(CDX12CommandList* pCmdList, CDX12RenderTarget* pRT)
		{
			// リソースバリア設定
			ng::CDX12ResourceBarrierTransition barrier;
			pRT->GetResourceBarrierForPresent(&barrier);
			pCmdList->ResourceBarrier(barrier);
		}

		NG_DECL void ClearRenderTarget(CDX12CommandList* pCmdList, CDX12RenderTarget* pRT, const float rgba[4], CDX12DepthStencil* pDS)
		{
			pCmdList->ClearRenderTarget(pRT->GetCPUDescriptorHandle(), rgba);
			if(pDS != nullptr) {
				pCmdList->ClearDepthStencil(pDS->GetCPUDescriptorHandle());
			}
		}

	}	// namespace DX12Util
}	// namespace ng
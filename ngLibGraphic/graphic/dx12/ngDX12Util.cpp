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

			D3D12_CPU_DESCRIPTOR_HANDLE cpuDescriptorHandle = pDS->GetCPUDescriptorHandle();

			// レンダーターゲット設定
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

		NG_DECL size_type DXGIFormatToBitsPerPixel(DXGI_FORMAT format)
		{
			switch(format)
			{
			case DXGI_FORMAT_R32G32B32A32_TYPELESS:
			case DXGI_FORMAT_R32G32B32A32_FLOAT:
			case DXGI_FORMAT_R32G32B32A32_UINT:
			case DXGI_FORMAT_R32G32B32A32_SINT:
				return 128;
			case DXGI_FORMAT_R32G32B32_TYPELESS:
			case DXGI_FORMAT_R32G32B32_FLOAT:
			case DXGI_FORMAT_R32G32B32_UINT:
			case DXGI_FORMAT_R32G32B32_SINT:
				return 96;
			case DXGI_FORMAT_R16G16B16A16_TYPELESS:
			case DXGI_FORMAT_R16G16B16A16_FLOAT:
			case DXGI_FORMAT_R16G16B16A16_UNORM:
			case DXGI_FORMAT_R16G16B16A16_UINT:
			case DXGI_FORMAT_R16G16B16A16_SNORM:
			case DXGI_FORMAT_R16G16B16A16_SINT:
			case DXGI_FORMAT_R32G32_TYPELESS:
			case DXGI_FORMAT_R32G32_FLOAT:
			case DXGI_FORMAT_R32G32_UINT:
			case DXGI_FORMAT_R32G32_SINT:
			case DXGI_FORMAT_R32G8X24_TYPELESS:
			case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
			case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:
			case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:
			case DXGI_FORMAT_Y416:
			case DXGI_FORMAT_Y210:
			case DXGI_FORMAT_Y216:
				return 64;
			case DXGI_FORMAT_R10G10B10A2_TYPELESS:
			case DXGI_FORMAT_R10G10B10A2_UNORM:
			case DXGI_FORMAT_R10G10B10A2_UINT:
			case DXGI_FORMAT_R11G11B10_FLOAT:
			case DXGI_FORMAT_R8G8B8A8_TYPELESS:
			case DXGI_FORMAT_R8G8B8A8_UNORM:
			case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
			case DXGI_FORMAT_R8G8B8A8_UINT:
			case DXGI_FORMAT_R8G8B8A8_SNORM:
			case DXGI_FORMAT_R8G8B8A8_SINT:
			case DXGI_FORMAT_R16G16_TYPELESS:
			case DXGI_FORMAT_R16G16_FLOAT:
			case DXGI_FORMAT_R16G16_UNORM:
			case DXGI_FORMAT_R16G16_UINT:
			case DXGI_FORMAT_R16G16_SNORM:
			case DXGI_FORMAT_R16G16_SINT:
			case DXGI_FORMAT_R32_TYPELESS:
			case DXGI_FORMAT_D32_FLOAT:
			case DXGI_FORMAT_R32_FLOAT:
			case DXGI_FORMAT_R32_UINT:
			case DXGI_FORMAT_R32_SINT:
			case DXGI_FORMAT_R24G8_TYPELESS:
			case DXGI_FORMAT_D24_UNORM_S8_UINT:
			case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
			case DXGI_FORMAT_X24_TYPELESS_G8_UINT:
			case DXGI_FORMAT_R9G9B9E5_SHAREDEXP:
			case DXGI_FORMAT_R8G8_B8G8_UNORM:
			case DXGI_FORMAT_G8R8_G8B8_UNORM:
			case DXGI_FORMAT_B8G8R8A8_UNORM:
			case DXGI_FORMAT_B8G8R8X8_UNORM:
			case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM:
			case DXGI_FORMAT_B8G8R8A8_TYPELESS:
			case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
			case DXGI_FORMAT_B8G8R8X8_TYPELESS:
			case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
			case DXGI_FORMAT_AYUV:
			case DXGI_FORMAT_Y410:
			case DXGI_FORMAT_YUY2:
			//case XBOX_DXGI_FORMAT_R10G10B10_7E3_A2_FLOAT:
			//case XBOX_DXGI_FORMAT_R10G10B10_6E4_A2_FLOAT:
			//case XBOX_DXGI_FORMAT_R10G10B10_SNORM_A2_UNORM:
				return 32;
			case DXGI_FORMAT_P010:
			case DXGI_FORMAT_P016:
			//case XBOX_DXGI_FORMAT_D16_UNORM_S8_UINT:
			//case XBOX_DXGI_FORMAT_R16_UNORM_X8_TYPELESS:
			//case XBOX_DXGI_FORMAT_X16_TYPELESS_G8_UINT:
			//case WIN10_DXGI_FORMAT_V408:
				return 24;
			case DXGI_FORMAT_R8G8_TYPELESS:
			case DXGI_FORMAT_R8G8_UNORM:
			case DXGI_FORMAT_R8G8_UINT:
			case DXGI_FORMAT_R8G8_SNORM:
			case DXGI_FORMAT_R8G8_SINT:
			case DXGI_FORMAT_R16_TYPELESS:
			case DXGI_FORMAT_R16_FLOAT:
			case DXGI_FORMAT_D16_UNORM:
			case DXGI_FORMAT_R16_UNORM:
			case DXGI_FORMAT_R16_UINT:
			case DXGI_FORMAT_R16_SNORM:
			case DXGI_FORMAT_R16_SINT:
			case DXGI_FORMAT_B5G6R5_UNORM:
			case DXGI_FORMAT_B5G5R5A1_UNORM:
			case DXGI_FORMAT_A8P8:
			case DXGI_FORMAT_B4G4R4A4_UNORM:
			//case WIN10_DXGI_FORMAT_P208:
			//case WIN10_DXGI_FORMAT_V208:
				return 16;
			case DXGI_FORMAT_NV12:
			case DXGI_FORMAT_420_OPAQUE:
			case DXGI_FORMAT_NV11:
				return 12;
			case DXGI_FORMAT_R8_TYPELESS:
			case DXGI_FORMAT_R8_UNORM:
			case DXGI_FORMAT_R8_UINT:
			case DXGI_FORMAT_R8_SNORM:
			case DXGI_FORMAT_R8_SINT:
			case DXGI_FORMAT_A8_UNORM:
			case DXGI_FORMAT_AI44:
			case DXGI_FORMAT_IA44:
			case DXGI_FORMAT_P8:
			//case XBOX_DXGI_FORMAT_R4G4_UNORM:
				return 8;
			case DXGI_FORMAT_R1_UNORM:
				return 1;
			case DXGI_FORMAT_BC1_TYPELESS:
			case DXGI_FORMAT_BC1_UNORM:
			case DXGI_FORMAT_BC1_UNORM_SRGB:
			case DXGI_FORMAT_BC4_TYPELESS:
			case DXGI_FORMAT_BC4_UNORM:
			case DXGI_FORMAT_BC4_SNORM:
				return 4;
			case DXGI_FORMAT_BC2_TYPELESS:
			case DXGI_FORMAT_BC2_UNORM:
			case DXGI_FORMAT_BC2_UNORM_SRGB:
			case DXGI_FORMAT_BC3_TYPELESS:
			case DXGI_FORMAT_BC3_UNORM:
			case DXGI_FORMAT_BC3_UNORM_SRGB:
			case DXGI_FORMAT_BC5_TYPELESS:
			case DXGI_FORMAT_BC5_UNORM:
			case DXGI_FORMAT_BC5_SNORM:
			case DXGI_FORMAT_BC6H_TYPELESS:
			case DXGI_FORMAT_BC6H_UF16:
			case DXGI_FORMAT_BC6H_SF16:
			case DXGI_FORMAT_BC7_TYPELESS:
			case DXGI_FORMAT_BC7_UNORM:
			case DXGI_FORMAT_BC7_UNORM_SRGB:
				return 8;
			default:
				return 0;
			}
		}

	}	// namespace DX12Util
}	// namespace ng
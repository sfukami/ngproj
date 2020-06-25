/*!
* @file		ngDX12.h
* @brief	DX12 ヘッダ
* @date		2020-06-25
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_H__
#define __NG_GRAPHIC_DX12_H__

#include "ngDX12Util.h"
#include "device/ngDX12Device.h"
#include "command/allocator/ngDX12CommandAllocator.h"
#include "command/list/ngDX12CommandList.h"
#include "command/queue/ngDX12CommandQueue.h"
#include "command/queue/ngDX12CommandQueueType.h"
#include "swapchain/ngDX12SwapChain.h"
#include "target/render/ngDX12RenderTarget.h"
#include "target/render/ngDX12RenderTargetId.h"
#include "target/depth/ngDX12DepthStencil.h"
#include "target/depth/ngDX12DepthStencilId.h"
#include "barrier/ngDX12ResourceBarrierTransition.h"

#endif	// __NG_GRAPHIC_DX12_H__
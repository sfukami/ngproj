/*!
* @file		appGraphicPipelineClearBuffer.cpp
* @brief	グラフィックパイプライン バッファクリア
* @date		2020-08-24
* @author	s.fukami
*/

#include "ngLibGraphic/graphic/dx12/ngDX12Util.h"
#include "appGraphicPipelineClearBuffer.h"

namespace app
{
	CGraphicPipelineClearBuffer::CGraphicPipelineClearBuffer()
	{
	}
	CGraphicPipelineClearBuffer::~CGraphicPipelineClearBuffer()
	{
	}

	bool CGraphicPipelineClearBuffer::Initialize()
	{
		return true;
	}

	void CGraphicPipelineClearBuffer::Finalize()
	{

	}

	void CGraphicPipelineClearBuffer::Render()
	{
		ng::CDX12Graphic* pDX12Graphic = ng::GetDX12Graphic();
		
		/*
		ng::CDX12Graphic* pDX12Graphic = ng::GetDX12Graphic();
		NG_ASSERT(pDX12Graphic != nullptr);

		// コマンドアロケータリセット
		ng::CDX12CommandAllocatorManager& cmdAllocMngr = pDX12Graphic->GetCommandAllocatorMngr();
		ng::CDX12CommandAllocator* pCmdAlloc = cmdAllocMngr.GetCommandAllocator(0);
		NG_ASSERT(pCmdAlloc != nullptr);

		pCmdAlloc->Reset();

		// コマンドリストリセット
		ng::CDX12CommandListManager& cmdListMngr = pDX12Graphic->GetCommandListMngr();
		ng::CDX12CommandList* pCmdList = cmdListMngr.GetCommandList(0);

		ng::CDX12PipelineStateManager& pipelineStateMngr = pDX12Graphic->GetPipelineStateMngr();
		ng::CDX12PipelineState* pPipelineState = pipelineStateMngr.GetPipelineState(ePIPELINE_STATE_ID_TEST01);
		NG_ASSERT(pPipelineState != nullptr);

		pCmdList->Reset(*pCmdAlloc, *pPipelineState);

		// ルートシグネチャ設定
		ng::CDX12RootSignatureManager& rootSignMngr = pDX12Graphic->GetRootSignatureMngr();
		ng::CDX12RootSignature* pRootSign = rootSignMngr.GetRootSignature(eROOT_SIGNATURE_ID_BASE);
		NG_ASSERT(pRootSign != nullptr);
		pCmdList->SetRootSignature(*pRootSign);

		// ビューポート設定
		pCmdList->SetViewport(m_viewport);
		// シザー矩形設定
		pCmdList->SetScissorRect(m_scissorRect);

		// バックバッファをレンダリングターゲットとして使用
		ng::CDX12SwapChain& swapChain = pDX12Graphic->GetSwapChain();
		ng::u32 frameIndex = swapChain.GetCurrentBackBufferIndex();
		ng::CDX12RenderTargetManager& rtMngr = pDX12Graphic->GetRenderTargetMngr();
		ng::CDX12RenderTarget* pBackBufferRT = rtMngr.GetRenderTarget(static_cast<ng::eDX12RenderTargetId>(frameIndex));
		NG_ASSERT_NOT_NULL(pBackBufferRT);

		{
			ng::CDX12ResourceBarrierTransition barrier;
			pBackBufferRT->GetResourceBarrierForSetRenderTarget(&barrier);
			pCmdList->ResourceBarrier(barrier);
		}

		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = pBackBufferRT->GetCPUDescriptorHandle();
		pCmdList->SetRenderTarget(rtvHandle, nullptr);

		// バックバッファクリア
		{
			const float clearColor[] = {0.0f, 0.0f, 0.5f, 1.0f};
			pCmdList->ClearRenderTarget(rtvHandle, clearColor, nullptr, 0);
		}

		// TODO: 描画コマンドの機能としてまとめたい
		pCmdList->Interface()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		pCmdList->Interface()->IASetVertexBuffers(0, 1, &m_vb.GetVertexBufferView());
		pCmdList->Interface()->DrawInstanced(3, 1, 0, 0);

		// バックバッファを表示
		{
			ng::CDX12ResourceBarrierTransition barrier;
			pBackBufferRT->GetResourceBarrierForPresent(&barrier);
			pCmdList->ResourceBarrier(barrier);
		}

		pCmdList->Close();

		// コマンド実行
		ng::CDX12CommandQueueManager& cmdQueueMngr = pDX12Graphic->GetCommandQueueMngr();
		ng::CDX12CommandQueue* pCmdQueue = cmdQueueMngr.GetCommandQueue(ng::eDX12_COMMAND_QUEUE_TYPE_GRAPHIC);

		pCmdQueue->ExecuteCommandList(*pCmdList);

		swapChain.Present(1);

		pCmdQueue->WaitForFence();
		*/
	}

}	// namespace app
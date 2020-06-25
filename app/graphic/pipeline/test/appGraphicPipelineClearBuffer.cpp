/*!
* @file		appGraphicPipelineClearBuffer.cpp
* @brief	グラフィックパイプライン バッファクリア
* @date		2020-06-24
* @author	s.fukami
*/

#include "ngLibGraphic/graphic/dx12/ngDX12.h"
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
		const unsigned int clientWidth = 640;
		const unsigned int clientHeight = 480;

		m_viewport.Initialize(0.0f, 0.0f, (float)clientWidth, (float)clientHeight, 0.0f, 1.0f);
		m_scissor.Initialize(0, 0, (LONG)clientWidth, (LONG)clientHeight);

		return true;
	}

	void CGraphicPipelineClearBuffer::Finalize()
	{

	}

	void CGraphicPipelineClearBuffer::Execute()
	{
		// コマンドリストリセット
		ng::CDX12CommandList* pCmdList = ng::GetDX12CommandList(0);
		pCmdList->Reset();

		// ビューポート設定
		pCmdList->SetViewport(m_viewport);
		// シザー矩形設定
		pCmdList->SetScissorRect(m_scissor);

		// バックバッファをレンダリングターゲットとして使用
		ng::CDX12RenderTarget* pBackBufferRT = ng::GetDX12RenderTargetOfCurrentBackBuffer();
		{
			ng::CDX12ResourceBarrierTransition barrier;
			pBackBufferRT->GetResourceBarrierForSetRenderTarget(&barrier);
			pCmdList->ResourceBarrier(barrier);
		}

		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = pBackBufferRT->GetCPUDescriptorHandle();
		D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = ng::GetDX12DepthStencil(ng::eDX12DepthStencilId::ID_01)->GetCPUDescriptorHandle();
		pCmdList->SetRenderTarget(rtvHandle, &dsvHandle);

		// バックバッファクリア
		{
			const float clearColor[] = {0.0f, 0.0f, 0.5f, 1.0f};
			pCmdList->ClearRenderTarget(rtvHandle, clearColor);
			pCmdList->ClearDepthStencil(dsvHandle);
		}

		{
			ng::CDX12ResourceBarrierTransition barrier;
			pBackBufferRT->GetResourceBarrierForPresent(&barrier);
			pCmdList->ResourceBarrier(barrier);
		}

		// コマンドの記録を終了
		pCmdList->Close();
	}

}	// namespace app
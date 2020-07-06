/*!
* @file		appGraphicPipelineClearBuffer.cpp
* @brief	グラフィックパイプライン バッファクリア
* @date		2020-06-24
* @author	s.fukami
*/

#include "ngLibGraphic/graphic/dx12/ngDX12.h"
#include "appGraphicPipelineClearBuffer.h"
#include "../../appGraphicModule.h"

namespace app
{
	CGraphicPipelineClearBuffer::CGraphicPipelineClearBuffer()
	{
	}
	CGraphicPipelineClearBuffer::~CGraphicPipelineClearBuffer()
	{
	}

	bool CGraphicPipelineClearBuffer::_initialize()
	{
		const unsigned int clientWidth = 640;
		const unsigned int clientHeight = 480;

		m_viewport.Initialize(0.0f, 0.0f, (float)clientWidth, (float)clientHeight, 0.0f, 1.0f);
		m_scissor.Initialize(0, 0, (LONG)clientWidth, (LONG)clientHeight);

		return true;
	}

	void CGraphicPipelineClearBuffer::_finalize()
	{

	}

	void CGraphicPipelineClearBuffer::_execute()
	{
		// コマンドリストリセット
		ng::CDX12CommandList* pCmdList = _getDX12CommandList(eGraphicCommandListId::MAIN);
		pCmdList->Reset();

		// ビューポート設定
		pCmdList->SetViewport(m_viewport);
		// シザー矩形設定
		pCmdList->SetScissorRect(m_scissor);

		// バックバッファをレンダリングターゲットとして使用
		ng::CDX12RenderTarget* pRTBackBuffer = ng::DX12Util::GetRenderTargetOfCurrentBackBuffer();
		ng::CDX12DepthStencil* pDS = ng::DX12Util::GetDepthStencil(ng::eDX12DepthStencilId::ID_01);
		ng::DX12Util::SetRenderTarget(pCmdList, pRTBackBuffer, pDS);

		// バックバッファクリア
		const float clearColor[4] = {0.0f, 0.0f, 0.5f, 1.0f};
		ng::DX12Util::ClearRenderTarget(pCmdList, pRTBackBuffer, clearColor, pDS);

		ng::DX12Util::SetRenderTargetToPresent(pCmdList, pRTBackBuffer);

		// コマンドの記録を終了
		pCmdList->Close();
	}

}	// namespace app
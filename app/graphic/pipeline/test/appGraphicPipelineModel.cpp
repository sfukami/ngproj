/*!
* @file		appGraphicPipelineModel.cpp
* @brief	グラフィックパイプライン バッファクリア
* @date		2020-06-24
* @author	s.fukami
*/

#include "ngLibGraphic/graphic/ngGraphicManager.h"
#include "ngLibGraphic/graphic/dx12/ngDX12.h"
#include "appGraphicPipelineModel.h"

namespace app
{
	CGraphicPipelineModel::CGraphicPipelineModel()
	{
	}
	CGraphicPipelineModel::~CGraphicPipelineModel()
	{
	}

	bool CGraphicPipelineModel::_initialize()
	{
		const unsigned int clientWidth = 640;
		const unsigned int clientHeight = 480;

		m_viewport.Initialize(0.0f, 0.0f, (float)clientWidth, (float)clientHeight, 0.0f, 1.0f);
		m_scissor.Initialize(0, 0, (LONG)clientWidth, (LONG)clientHeight);

		return true;
	}

	void CGraphicPipelineModel::_finalize()
	{

	}

	void CGraphicPipelineModel::_execute()
	{
		// コマンドリストリセット
		ng::CDX12CommandList* pCmdList = ng::DX12Util::GetCommandList(0);
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

		// 描画コマンド実行
		ng::CGraphicManager::GetInstance().Render();

		ng::DX12Util::SetRenderTargetToPresent(pCmdList, pRTBackBuffer);

		// コマンドの記録を終了
		pCmdList->Close();
	}

}	// namespace app
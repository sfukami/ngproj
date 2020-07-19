/*!
* @file		appGraphicPipelineDefault.cpp
* @brief	グラフィックパイプライン デフォルト
* @date		2020-07-08
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "ngLibCore/math/ngMath.h"
#include "ngLibGraphic/graphic/ngGraphicManager.h"
#include "ngLibGraphic/graphic/dx12/ngDX12.h"
#include "appGraphicPipelineDefault.h"
#include "app/graphic/appGraphicUtil.h"
#include "app/graphic/render/appRenderParam.h"

namespace app
{
	CGraphicPipelineDefault::CGraphicPipelineDefault()
	{
	}
	CGraphicPipelineDefault::~CGraphicPipelineDefault()
	{
	}

	bool CGraphicPipelineDefault::_initialize()
	{
		const unsigned int clientWidth = 640;
		const unsigned int clientHeight = 480;

		// カメラ
		{
			m_camera.SetPos(ng::Vector3(0.f, 0.f, -3.f));
			m_camera.SetAtPos(ng::Vector3::ZERO);
			m_camera.SetUpVec(ng::Vector3::AXIS_Y);
			m_camera.CalcViewMatrix();
		}

		// プロジェクション
		{
			m_proj.SetWidth(clientWidth);
			m_proj.SetHeight(clientHeight);
			m_proj.SetNear(0.1f);
			m_proj.SetFar(100.f);
			m_proj.SetFOV(ng::DegreeToRadian(60.f));
			m_proj.CalcProjMatrix();
		}

		m_viewport.Initialize(0.0f, 0.0f, (float)clientWidth, (float)clientHeight, 0.0f, 1.0f);
		m_scissor.Initialize(0, 0, (LONG)clientWidth, (LONG)clientHeight);

		return true;
	}

	void CGraphicPipelineDefault::_finalize()
	{
	}

	void CGraphicPipelineDefault::_execute()
	{
		// コマンドリストリセット
		ng::CDX12CommandList* pCmdList = GraphicUtil::GetDX12CommandList(eGraphicCommandListId::MAIN);
		pCmdList->Reset();

		// ビューポート設定
		pCmdList->SetViewport(m_viewport);
		// シザー矩形設定
		pCmdList->SetScissorRect(m_scissor);

		// バックバッファをレンダリングターゲットとして使用
		ng::CDX12RenderTarget* pRTBackBuffer = ng::DX12Util::GetRenderTargetOfCurrentBackBuffer();
		ng::CDX12DepthStencil* pDS = ng::DX12Util::GetDepthStencil(ng::eDX12DepthStencilId::ID_01);
		ng::DX12Util::SetRenderTarget(pCmdList, pRTBackBuffer, pDS);

		// バックポリゴン描画
		const float clearColor[4] = {0.0f, 0.0f, 0.5f, 1.0f};
		ng::DX12Util::ClearRenderTarget(pCmdList, pRTBackBuffer, clearColor, pDS);

		// 描画コマンド実行
		{
			RenderParam param;
			param.cmdListId = eGraphicCommandListId::MAIN;
			ng::CGraphicManager::GetInstance().Render(&param);
		}

		ng::DX12Util::SetRenderTargetToPresent(pCmdList, pRTBackBuffer);

		// コマンドの記録を終了
		pCmdList->Close();
	}

}	// namespace app
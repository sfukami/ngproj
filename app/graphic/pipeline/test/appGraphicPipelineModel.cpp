/*!
* @file		appGraphicPipelineModel.cpp
* @brief	グラフィックパイプライン モデル描画
* @date		2020-06-24
* @author	s.fukami
*/

#include "ngLibCore/math/ngMath.h"
#include "ngLibCore/geometry/matrix/ngMatrix4x4.h"
#include "ngLibCore/geometry/matrix/ngMatrixOp.h"
#include "ngLibGraphic/graphic/dx12/ngDX12.h"
#include "appGraphicPipelineModel.h"
#include "app/graphic/render/appRenderParam.h"
#include "app/memory/appMemoryUtil.h"
#include "app/graphic/appGraphicUtil.h"

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

		ng::CDX12Device* pDX12Device = GraphicUtil::GetDX12Device();
		NG_ASSERT(pDX12Device != nullptr);

		// モデル生成
		if(!m_model.Create("../resource/model/alicia-solid.mdl", eResourceMemoryType::SCENE)) {
			NG_ERRLOG("GraphicPipelineModel", "モデルの生成に失敗しました.");
			return false;
		}

		// カメラ
		{
			float height = 1.0f;
			m_camera.SetPos(ng::Vector3(0.f, height, -1.5f));
			m_camera.SetAtPos(ng::Vector3(0.f, height, 0.f));
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

	void CGraphicPipelineModel::_finalize()
	{
		m_model.Destroy();
	}

	void CGraphicPipelineModel::_execute()
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

		// バックバッファクリア
		const float clearColor[4] = {0.0f, 0.0f, 0.5f, 1.0f};
		ng::DX12Util::ClearRenderTarget(pCmdList, pRTBackBuffer, clearColor, pDS);

		// モデル描画
		{
			RenderParam param;
			param.cmdListId = eGraphicCommandListId::MAIN;
			param.viewMat = m_camera.GetViewMatrix();
			param.projMat = m_proj.GetProjMatrix();
			param.CalcViewProjMatrix();
			param.CalcWorldViewProjMatrix();

			m_model.Render(param);
		}

		ng::DX12Util::SetRenderTargetToPresent(pCmdList, pRTBackBuffer);

		// コマンドの記録を終了
		pCmdList->Close();
	}

}	// namespace app
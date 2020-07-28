/*!
* @file		appGraphic.cpp
* @brief	グラフィック
* @date		2020-06-24
* @author	s.fukami
*/

#include "ngLibGraphic/graphic/ngGraphicManager.h"
#include "appGraphic.h"
#include "appGraphicConst.h"
#include "command/appGraphicCommandListId.h"
#include "pipeline/appGraphicPipeline.h"
#include "app/memory/appMemoryUtil.h"

namespace app
{
	CGraphic::CGraphic()
		: m_isInit(false)
		, m_pPipeline(nullptr)
	{
	}
	CGraphic::~CGraphic()
	{
	}

	bool CGraphic::Initialize(
		HWND hWnd,
		unsigned int clientWidth,
		unsigned int clientHeight,
		bool isFullScreen
		)
	{
		NG_ASSERT(!_isInit());

		// DX12グラフィック セットアップ
		{
			ng::CDX12Graphic::CreateParam param;
			param.hWnd = hWnd;
			param.clientWidth = clientWidth;
			param.clientHeight = clientHeight;
			param.isFullscreen = isFullScreen;
			param.commandListNum = static_cast<ng::u32>(eGraphicCommandListId::NUM);
			param.deviceParam.featureLevel = D3D_FEATURE_LEVEL_11_0;
			param.deviceParam.isUseWarpDevice = true;
			
			if(NG_FAILED(m_dx12Graphic.Create(param))) {
				NG_ERRLOG("Graphic", "DirectX12グラフィックの生成に失敗しました.");
				return false;
			}
		}

		// シングルトンインスタンス生成
		ng::CGraphicManager::CreateInstance();

		// グラフィック管理初期化
		{
			if(NG_FAILED(ng::CGraphicManager::GetInstance().Initialize(APP_GRAPHIC_RENDER_COMMAND_MAX))) {
				NG_ERRLOG("Graphic", "グラフィック管理の初期化に失敗しました.");
				return false;
			}
		}

		// グラフィック管理へ割り当て
		ng::CGraphicManager::GetInstance().AssignGraphic(&m_dx12Graphic);

		// ルートシグネチャ管理初期化
		if(!m_rootSignMngr.Initialize(
			APP_MEMALLOC_GRAPHIC,
			m_dx12Graphic.GetDevice()
			)) {
			NG_ERRLOG("Graphic", "ルートシグネチャ管理の初期化に失敗しました.");
			return false;
		}

		// シェーダーエフェクトファクトリ初期化
		if(!m_shEffFac.Initialize()) {
			NG_ERRLOG("Graphic", "シェーダーエフェクトファクトリの初期化に失敗しました.");
			return false;
		}

		m_isInit = true;

		return true;
	}

	void CGraphic::Finalize()
	{
		// シェーダーエフェクトファクトリ終了処理
		m_shEffFac.Finalize();
		
		// ルートシグネチャ管理 終了処理
		m_rootSignMngr.Finalize();

		// DX12グラフィック 破棄
		m_dx12Graphic.Destroy();

		// グラフィック管理から割り当て解除
		ng::CGraphicManager::GetInstance().UnassignGraphic();
		// グラフィック管理 終了処理
		ng::CGraphicManager::GetInstance().Finalize();

		// シングルトンインスタンス破棄
		ng::CGraphicManager::DestroyInstance();

		m_isInit = false;
	}

	void CGraphic::Render()
	{
		if(!_isInit()) return;
		if(!_isValidPipeline()) return;

		// パイプライン実行
		m_pPipeline->Execute();

		// 描画の後処理
		ng::CGraphicManager::GetInstance().CleanupRender();
	}

	void CGraphic::SetPipeline(CGraphicPipeline* pPipeline)
	{
		m_pPipeline = pPipeline;
	}

	ng::CDX12Graphic& CGraphic::GetDX12Graphic()
	{
		return m_dx12Graphic;
	}
	const ng::CDX12Graphic& CGraphic::GetDX12Graphic() const
	{
		return m_dx12Graphic;
	}

	bool CGraphic::_isInit() const
	{
		return m_isInit;
	}

	bool CGraphic::_isValidPipeline() const
	{
		return (m_pPipeline != nullptr && m_pPipeline->IsInit());
	}

}	// namespace app
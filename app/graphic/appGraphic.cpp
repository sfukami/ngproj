/*!
* @file		appGraphic.cpp
* @brief	グラフィック
* @date		2020-08-24
* @author	s.fukami
*/

#include "ngLibGraphic/graphic/ngGraphicManager.h"
#include "appGraphic.h"
#include "pipeline/appGraphicPipeline.h"

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

		// シングルトンインスタンス生成
		ng::CGraphicManager::CreateInstance();

		// DX12グラフィック セットアップ
		{
			ng::CDX12Graphic::CreateParam param;
			param.hWnd = hWnd;
			param.clientWidth = clientWidth;
			param.clientHeight = clientHeight;
			param.isFullscreen = isFullScreen;
			param.deviceParam.featureLevel = D3D_FEATURE_LEVEL_11_0;
			param.deviceParam.isUseWarpDevice = true;
			
			if(NG_FAILED(m_dx12Graphic.Create(param))) {
				NG_ERRLOG("Graphic", "DirectX12グラフィックの生成に失敗しました.");
				return false;
			}
		}

		// グラフィック管理へ割り当て
		ng::CGraphicManager::GetInstance().AssignGraphic(&m_dx12Graphic);

		m_isInit = true;

		return true;
	}

	void CGraphic::Finalize()
	{
		// DX12グラフィック 破棄
		m_dx12Graphic.Destroy();

		// グラフィック管理から割り当て解除
		ng::CGraphicManager::GetInstance().UnassignGraphic();

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
		
		// 描画
		ng::CGraphicManager::GetInstance().Render();
	}

	void CGraphic::SetPipeline(CGraphicPipeline* pPipeline)
	{
		m_pPipeline = pPipeline;
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
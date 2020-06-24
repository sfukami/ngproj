/*!
* @file		appGraphic.cpp
* @brief	グラフィック
* @date		2020-08-24
* @author	s.fukami
*/

#include "ngLibGraphic/graphic/ngGraphicManager.h"
#include "appGraphic.h"

namespace app
{
	CGraphic::CGraphic()
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
	}

	void CGraphic::Render()
	{
		ng::CGraphicManager::GetInstance().Render();
	}

}	// namespace app
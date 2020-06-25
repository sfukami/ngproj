/*!
* @file		appGraphic.cpp
* @brief	グラフィック
* @date		2020-08-24
* @author	s.fukami
*/

#include "ngLibGraphic/graphic/ngGraphicManager.h"
#include "ngLibGraphic/graphic/dx12/ngDX12.h"
#include "appGraphic.h"

namespace app
{
	CGraphic::CGraphic()
		: m_isInit(false)
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

		// グラフィックパイプライン初期化
		if(!m_pipeline.Initialize()) {
			return false;
		}

		m_isInit = true;

		return true;
	}

	void CGraphic::Finalize()
	{
		// グラフィックパイプライン終了処理
		m_pipeline.Finalize();

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

		// パイプライン実行
		_preprocessPipeline();
		_executePipeline();
		_postprocessPipeline();
		
		// 描画
		ng::CGraphicManager::GetInstance().Render();
	}

	void CGraphic::_executePipeline()
	{
		// test
		m_pipeline.Execute();
	}

	void CGraphic::_preprocessPipeline()
	{
		// 全コマンドアロケータリセット
		ng::ResetAllDX12CommandAllocator();
	}

	void CGraphic::_postprocessPipeline()
	{
		// 全コマンドリスト実行
		ng::ExecuteAllDX12CommandList(ng::eDX12CommandQueueType::GRAPHIC);

		// バックバッファを表示
		ng::CDX12SwapChain* pSwapChain = ng::GetDX12SwapChain();
		pSwapChain->Present(1);

		// 描画完了待ち
		ng::CDX12CommandQueue* pCmdQueue = ng::GetDX12CommandQueue(ng::eDX12CommandQueueType::GRAPHIC);
		pCmdQueue->WaitForFence();
	}

	bool CGraphic::_isInit() const
	{
		return m_isInit;
	}

}	// namespace app
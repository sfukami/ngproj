/*!
* @file		appGraphicPipeline.cpp
* @brief	グラフィックパイプライン 基底クラス
* @date		2020-06-24
* @author	s.fukami
*/

#include "ngLibGraphic/graphic/dx12/ngDX12.h"
#include "appGraphicPipeline.h"
#include "app/tool/gui/appToolGUIModule.h"

namespace app
{
	CGraphicPipeline::CGraphicPipeline()
		: m_isInit(false)
	{
	}
	CGraphicPipeline::~CGraphicPipeline()
	{
	}

	bool CGraphicPipeline::Initialize()
	{
		m_isInit = _initialize();

		return m_isInit;
	}

	void CGraphicPipeline::Finalize()
	{
		_finalize();

		m_isInit = false;
	}

	void CGraphicPipeline::Execute()
	{
		if(!IsInit()) return;

		_preprocessPipeline();
		_execute();
		CToolGUIModule::RenderToolGUI();
		_postprocessPipeline();
	}

	bool CGraphicPipeline::IsInit() const
	{
		return m_isInit;
	}

	bool CGraphicPipeline::_initialize()
	{
		return true;
	}

	void CGraphicPipeline::_finalize()
	{
	}
	
	void CGraphicPipeline::_execute()
	{
	}

	void CGraphicPipeline::_preprocessPipeline()
	{
		// 全コマンドアロケータリセット
		ng::DX12Util::ResetAllCommandAllocator();
	}

	void CGraphicPipeline::_postprocessPipeline()
	{
		// 全コマンドリスト実行
		ng::DX12Util::ExecuteAllCommandList(ng::eDX12CommandQueueType::GRAPHIC);

		// バックバッファを表示
		ng::CDX12SwapChain* pSwapChain = ng::DX12Util::GetSwapChain();
		pSwapChain->Present(1);

		// 描画完了待ち
		ng::CDX12CommandQueue* pCmdQueue = ng::DX12Util::GetCommandQueue(ng::eDX12CommandQueueType::GRAPHIC);
		pCmdQueue->WaitForFence();
	}

}	// namespace app
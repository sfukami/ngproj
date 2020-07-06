/*!
* @file		appToolGUI.cpp
* @brief	ツールGUI
* @date		2020-07-06
* @author	s.fukami
*/

#include "ngLibGraphic/graphic/dx12/ngDX12.h"
#include "appToolGUI.h"
#include "../../graphic/appGraphic.h"
#include "../../graphic/command/appGraphicCommandListId.h"

namespace app
{
	CToolGUI::CToolGUI()
		: m_isInit(false)
	{
	}

	CToolGUI::~CToolGUI()
	{
	}

	bool CToolGUI::Initialize(
		HWND hWnd,
		CGraphic& graphic
		)
	{
		// ImGui セットアップ
		ng::CDX12Graphic& dx12Graphic = graphic.GetDX12Graphic();
		if(NG_FAILED(m_imGui.Setup(
			hWnd,
			dx12Graphic.GetDevice(),
			dx12Graphic.GetSwapChain().GetBackBufferFormat(),
			1, true, true
			))) {
			NG_ERRLOG("ToolGUI", "ImGuiDX12の初期化に失敗しました.");
			return false;
		}

		m_isInit = true;

		return true;
	}

	void CToolGUI::Finalize()
	{
		// ImGui シャットダウン
		m_imGui.Shutdown();

		m_isInit = false;
	}
	
	void CToolGUI::Render()
	{
		if(!IsInit()) return;

		ng::CDX12CommandList* pCmdList = ng::DX12Util::GetCommandList(static_cast<ng::u32>(eGraphicCommandListId::IMGUI));

		if(pCmdList == nullptr) return;

		pCmdList->Reset();

		ng::CDX12RenderTarget* pRTBackBuffer = ng::DX12Util::GetRenderTargetOfCurrentBackBuffer();
		ng::CDX12DepthStencil* pDS = ng::DX12Util::GetDepthStencil(ng::eDX12DepthStencilId::ID_01);
		ng::DX12Util::SetRenderTarget(pCmdList, pRTBackBuffer, pDS);

		// ImGui 描画
		m_imGui.Render(*pCmdList);

		ng::DX12Util::SetRenderTargetToPresent(pCmdList, pRTBackBuffer);

		// コマンドの記録を終了
		pCmdList->Close();
	}

	void CToolGUI::BeginRender()
	{
		if(!IsInit()) return;

		// ImGui 描画前処理
		m_imGui.NewFrame();
	}

	void CToolGUI::EndRender()
	{
		if(!IsInit()) return;

		// ImGui 描画後処理
		m_imGui.EndFrame();
	}

	/*! 初期化済みか */
	bool CToolGUI::IsInit() const
	{
		return m_isInit;
	}

	LRESULT CToolGUI::WinProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return ng::CImGuiDX12::WinProcHandler(hWnd, msg, wParam, lParam);
	}

}	// namespace app
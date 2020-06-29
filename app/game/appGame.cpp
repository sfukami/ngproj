/*!
* @file		appGame.cpp
* @brief	ゲームメイン
* @date		2016-08-22
* @author	s.fukami
*/

#include <tchar.h>
#include "ngLibCore/system/ngCoreSystem.h"
#include "appGame.h"

// test
#include "ngLibCore/system/ngSysUtil.h"
#include "../graphic/pipeline/test/appGraphicPipelineClearBuffer.h"
#include "../graphic/pipeline/test/appGraphicPipelinePolygon.h"

namespace app
{
	/*! ウィンドウプロシージャ */
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	CGame::CGame()
		: m_pPipeline(nullptr)
	{
	}
	CGame::~CGame()
	{
	}

	bool CGame::Initialize(HINSTANCE hInst)
	{
		const unsigned int CLIENT_WIDTH = 640;
		const unsigned int CLIENT_HEIGHT = 480;

		// メモリリークチェック
		NG_CHECK_MEMLEAK();

		// シングルトンインスタンス生成
		ng::CCoreSystem::CreateInstance();

		// NGコアシステム セットアップ
		{
			ng::CCoreSystem::SetupParam param;
			param.sysMemInitParam.SetAllocSize(ng::eSystemMemoryType::GRAPHIC, NG_MB(1));

			if(NG_FAILED(ng::CCoreSystem::GetInstance().Setup(param))) {
				NG_ERRLOG("Game", "NGコアシステムのセットアップに失敗しました.");
				return false;
			}
		}

		// アプリケーションウィンドウ生成
		if( ! m_window.Create(
			CLIENT_WIDTH,
			CLIENT_HEIGHT,
			_T("gamemain"),
			_T("app"),
			WndProc
			)) {
			NG_ERRLOG("Game", "ウィンドウの生成に失敗しました.");
			return false;
		}
		m_window.Show();

		// 入力初期化
		if(!m_input.Initialize(
			m_window.GetHandle()
			)) {
			return false;
		}

		// グラフィック初期化
		if(!m_graphic.Initialize(
			m_window.GetHandle(),
			CLIENT_WIDTH,
			CLIENT_HEIGHT,
			false
			)) {
			return false;
		}

		// TODO: 仮にシステムアロケータを使用する
		m_pPipeline = NG_NEW(NG_SYSALLOC_GRAPHIC) CGraphicPipelinePolygon();
		if(m_pPipeline->Initialize()) {
			m_graphic.SetPipeline(m_pPipeline);
		} else {
			NG_ERRLOG("Game", "グラフィックパイプラインの初期化に失敗しました.");
			return false;
		}

		return true;
	}
	
	int CGame::MainLoop()
	{
		MSG msg = {0};

		while(true)
		{
			if(::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
				if( ! ::GetMessage(&msg, NULL, 0, 0)) {
					return (int)msg.wParam;
				}
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			} else {
				// 更新処理
				_update();
				// 描画処理
				_render();
			}
		}

		return (int)msg.wParam;
	}
	
	void CGame::Finalize()
	{
		if(m_pPipeline != nullptr) {
			NG_SAFE_DELETE(NG_SYSALLOC_GRAPHIC, m_pPipeline);
		}

		m_graphic.Finalize();
		m_input.Finalize();
		m_window.Destroy();

		// NGコアシステム シャットダウン
		ng::CCoreSystem::GetInstance().Shutdown();
		ng::CCoreSystem::DestroyInstance();
	}

	void CGame::_update()
	{
		m_input.Update();

		// test
		{
			// Keyboard
			if(CInput::CheckKeyboardInput(ng::eKeyCode::A, ng::eInputState::PRESSED)) {
				ng::DPrintf("key A pressed.\n");
			}
			if(CInput::CheckKeyboardInput(ng::eKeyCode::A, ng::eInputState::RELEASED)) {
				ng::DPrintf("key A released.\n");
			}
			if(CInput::CheckKeyboardInput(ng::eKeyCode::A, ng::eInputState::HELD)) {
				ng::DPrintf("key A held.\n");
			}
			// Mouse
			if(CInput::CheckMouseInput(ng::eMouseCode::LEFT, ng::eInputState::PRESSED)) {
				ng::DPrintf("button Left pressed.\n");
			}
			if(CInput::CheckMouseInput(ng::eMouseCode::LEFT, ng::eInputState::RELEASED)) {
				ng::DPrintf("button Left released.\n");
			}
			if(CInput::CheckMouseInput(ng::eMouseCode::LEFT, ng::eInputState::HELD)) {
				ng::DPrintf("button Left held.\n");
			}
		}
	}

	void CGame::_render()
	{
		m_graphic.Render();
	}

	/*! ウィンドウプロシージャ */
	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch(msg)
		{
		case WM_DESTROY:
			::PostQuitMessage(0);
			break;
		case WM_CHAR:
			switch(wParam)
			{
			case VK_ESCAPE:
				::PostQuitMessage(0);
				break;
			}
			break;
		default:
			break;
		}
		
		return ::DefWindowProc(hWnd, msg, wParam, lParam);
	}

}	// namespace app
/*!
* @file		appGame.cpp
* @brief	ゲームメイン
* @date		2016-08-22
* @author	s.fukami
*/

#include <tchar.h>
#include "ngLibCore/system/ngCoreSystem.h"
#include "ngLibApp/input/ngInputManager.h"
#include "appGame.h"

namespace app
{
	/*! ウィンドウプロシージャ */
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	CGame::CGame()
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
		{
			ng::CCoreSystem::CreateInstance();
			ng::CInputManager::CreateInstance();
		}

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

		// デバイス入力 セットアップ
		{
			// Directインプット生成
			if(NG_FAILED(m_input.Create())) {
				NG_ERRLOG("Game", "Directインプットの生成に失敗しました.");
				return false;
			}
			// DirectInputキーボードのセットアップ
			if(NG_FAILED(m_input.SetupKeyboard(
				m_window.GetHandle(),
				DISCL_NONEXCLUSIVE | DISCL_FOREGROUND | DISCL_NOWINKEY
				))) {
				NG_ERRLOG("Game", "DirectInputキーボードのセットアップに失敗しました.");
				return false;
			}
			// DirectInputマウスのセットアップ
			if(NG_FAILED(m_input.SetupMouse(
				m_window.GetHandle(),
				DISCL_NONEXCLUSIVE | DISCL_FOREGROUND
				))) {
				NG_ERRLOG("Game", "DirectInputマウスのセットアップに失敗しました.");
				return false;
			}
			
			ng::CInputManager::GetInstance().AssignInput(&m_input);
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
		m_graphic.Finalize();
		m_window.Destroy();

		// Directインプット 破棄
		m_input.Destroy();
		ng::CInputManager::GetInstance().UnassignInput();
		ng::CInputManager::DestroyInstance();

		// NGコアシステム シャットダウン
		ng::CCoreSystem::GetInstance().Shutdown();
		ng::CCoreSystem::DestroyInstance();
	}

	void CGame::_update()
	{
		ng::CInputManager::GetInstance().Update();

		// test
		{
			auto& inputMngr = ng::CInputManager::GetInstance();

			// Keyboard
			if(inputMngr.CheckKeyboardInput(ng::eKeyCode::A, ng::eInputState::PRESSED)) {
				ng::DPrintf("key A pressed.\n");
			}
			if(inputMngr.CheckKeyboardInput(ng::eKeyCode::A, ng::eInputState::RELEASED)) {
				ng::DPrintf("key A released.\n");
			}
			if(inputMngr.CheckKeyboardInput(ng::eKeyCode::A, ng::eInputState::HELD)) {
				ng::DPrintf("key A held.\n");
			}
			// Mouse
			if(inputMngr.CheckMouseInput(ng::eMouseCode::LEFT, ng::eInputState::PRESSED)) {
				ng::DPrintf("button Left pressed.\n");
			}
			if(inputMngr.CheckMouseInput(ng::eMouseCode::LEFT, ng::eInputState::RELEASED)) {
				ng::DPrintf("button Left released.\n");
			}
			if(inputMngr.CheckMouseInput(ng::eMouseCode::LEFT, ng::eInputState::HELD)) {
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
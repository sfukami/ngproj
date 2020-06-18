/*!
* @file		appGame.cpp
* @brief	ゲームメイン
* @date		2016-08-22
* @author	s.fukami
*/

#include <tchar.h>
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
		const int CLIENT_WIDTH = 640;
		const int CLIENT_HEIGHT = 480;

		if( ! m_window.Create(
			CLIENT_WIDTH,
			CLIENT_HEIGHT,
			_T("gamemain"),
			_T("app"),
			WndProc
			)) {
		//	NG_DPRINTF("ウィンドウ生成失敗\n");
			return false;
		}

		m_window.Show();

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
				{
					
				}
				// 描画処理
				{
					
				}
			}
		}

		return (int)msg.wParam;
	}
	
	void CGame::Finalize()
	{
		m_window.Destroy();
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

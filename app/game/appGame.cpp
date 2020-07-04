/*!
* @file		appGame.cpp
* @brief	ゲームメイン
* @date		2016-08-22
* @author	s.fukami
*/

#include <tchar.h>
#include "ngLibCore/system/ngCoreSystem.h"
#include "app/common/appCommon.h"
#include "appGame.h"
#include "../memory/appMemoryModule.h"
#include "../input/appInputModule.h"
#include "../graphic/appGraphicModule.h"
#include "../scene/appSceneModule.h"
#include "../job/appJobModule.h"

#include "../scene/appSceneId.h"
#include "../scene/root/appSceneRoot.h"

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

		// アプリケーションメモリ初期化
		if(!m_appMem.Initialize()) {
			NG_ERRLOG("Game", "アプリケーションメモリの初期化に失敗しました.");
			return false;
		}
		CMemoryModule::SetApplicationMemory(&m_appMem);

		// アプリケーションウィンドウ生成
		if(!m_window.Create(
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
			NG_ERRLOG("Game", "入力の初期化に失敗しました.");
			return false;
		}
		CInputModule::SetInput(&m_input);

		// グラフィック初期化
		if(!m_graphic.Initialize(
			m_window.GetHandle(),
			CLIENT_WIDTH,
			CLIENT_HEIGHT,
			false
		)) {
			NG_ERRLOG("Game", "グラフィックの初期化に失敗しました.");
			return false;
		}
		CGraphicModule::SetGraphic(&m_graphic);

		// シーン管理初期化
		if(!m_sceneMngr.Initialize(static_cast<unsigned int>(eSceneId::NUM), APP_MEMALLOC_APPLICATION)) {
			NG_ERRLOG("Game", "シーン管理の初期化に失敗しました.");
			return false;
		}
		CSceneModule::SetSceneManager(&m_sceneMngr);

		// ジョブ管理初期化
		if(!m_jobMngr.Initialize(32, APP_MEMALLOC_APPLICATION)) {
			NG_ERRLOG("Game", "ジョブ管理の初期化に失敗しました.");
			return false;
		}
		CJobModule::SetJobManager(&m_jobMngr);

		// ルートシーン登録
		{
			auto scenePtr = NG_MAKE_SHARED_PTR(IScene, APP_MEMALLOC_APPLICATION, CSceneRoot());
			m_sceneMngr.RegisterScene(static_cast<unsigned int>(eSceneId::GAME), scenePtr);
		}

		return true;
	}

	int CGame::MainLoop()
	{
		MSG msg = {0};

		while(true)
		{
			if(::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
				if(!::GetMessage(&msg, NULL, 0, 0)) {
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
		m_sceneMngr.Finalize();

		m_graphic.Finalize();
		m_input.Finalize();
		m_window.Destroy();

		// NGコアシステム シャットダウン
		ng::CCoreSystem::GetInstance().Shutdown();
		ng::CCoreSystem::DestroyInstance();
	}

	void CGame::_update()
	{
		const float deltaTime = 0.f;	// TODO:

		m_input.Update();
		m_sceneMngr.Update(deltaTime);
		m_jobMngr.ExecuteJob(eJobProcess::UPDATE);

		m_jobMngr.ExecuteJob(eJobProcess::LATE_UPDATE);
	}

	void CGame::_render()
	{
		m_sceneMngr.Render();
		m_graphic.Render();
		m_jobMngr.ExecuteJob(eJobProcess::END_OF_FRAME);
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
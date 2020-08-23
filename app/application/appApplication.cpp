/*!
* @file		appApplication.cpp
* @brief	アプリケーション
* @date		2016-08-22
* @author	s.fukami
*/

#include "ngLibCore/system/ngCoreSystem.h"
#include "app/common/appCommon.h"
#include "appApplication.h"
#include "appApplicationConst.h"
#include "../memory/appMemoryModule.h"
#include "../resource/appResourceModule.h"
#include "../input/appInputModule.h"
#include "../graphic/appGraphicModule.h"
#include "../scene/appSceneModule.h"
#include "../tool/gui/appToolGUIModule.h"
// Scene
#include "../scene/appSceneId.h"
#include "../scene/root/appSceneRoot.h"

namespace app
{
	/*! ウィンドウプロシージャ */
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	CApplication::CApplication()
	{
	}
	CApplication::~CApplication()
	{
	}

	bool CApplication::Initialize(HINSTANCE hInst)
	{
		const unsigned int clientWidth = APP_CLIENT_WIDTH_DEFAULT;
		const unsigned int clientHeight = APP_CLIENT_HEIGHT_DEFAULT;

		// メモリリークチェック
		NG_CHECK_MEMLEAK();

		// シングルトンインスタンス生成
		ng::CCoreSystem::CreateInstance();

		// NGコアシステム セットアップ
		{
			ng::CCoreSystem::SetupParam param;
			param.sysMemInitParam.SetAllocSize(ng::eSystemMemoryType::GRAPHIC, APP_GRAPHIC_MEMALLOC_SIZE);

			if(NG_FAILED(ng::CCoreSystem::GetInstance().Setup(param))) {
				NG_ERRLOG("Application", "NGコアシステムのセットアップに失敗しました.");
				return false;
			}
		}

		// アプリケーションメモリ初期化
		if(!m_appMem.Initialize()) {
			NG_ERRLOG("Application", "アプリケーションメモリの初期化に失敗しました.");
			return false;
		}
		CMemoryModule::SetApplicationMemory(&m_appMem);

		// リソースシステム初期化
		{
			ng::CWeakPtr<ng::IMemoryAllocator> allocPtr = m_appMem.GetAllocator(eMemoryAllocatorId::RESOURCE);

			if(!m_resSys.Initialize(*allocPtr, APP_RESOURCE_MANAGE_MAX)) {
				NG_ERRLOG("Application", "リソースシステムの初期化に失敗しました.");
				return false;
			}
		}
		CResourceModule::SetResourceSystem(&m_resSys);

		// アプリケーションウィンドウ生成
		if(!m_window.Create(
			clientWidth,
			clientHeight,
			_T("gamemain"),
			_T("app"),
			WndProc
		)) {
			NG_ERRLOG("Application", "ウィンドウの生成に失敗しました.");
			return false;
		}
		m_window.Show();

		// 入力初期化
		if(!m_input.Initialize(
			m_window.GetHandle()
		)) {
			NG_ERRLOG("Application", "入力の初期化に失敗しました.");
			return false;
		}
		CInputModule::SetInput(&m_input);

		// グラフィック初期化
		if(!m_graphic.Initialize(
			m_window.GetHandle(),
			clientWidth,
			clientHeight,
			false
		)) {
			NG_ERRLOG("Application", "グラフィックの初期化に失敗しました.");
			return false;
		}
		CGraphicModule::SetGraphic(&m_graphic);

		// シーン管理初期化
		if(!m_sceneMngr.Initialize(static_cast<unsigned int>(eSceneId::NUM), APP_MEMALLOC_APPLICATION)) {
			NG_ERRLOG("Application", "シーン管理の初期化に失敗しました.");
			return false;
		}
		CSceneModule::SetSceneManager(&m_sceneMngr);

		// ツールGUI初期化
		if(!m_toolGUI.Initialize(
			m_window.GetHandle(),
			m_graphic
			)) {
			NG_ERRLOG("Application", "ツールGUIの初期化に失敗しました.");
			return false;
		}
		CToolGUIModule::SetToolGUI(&m_toolGUI);

		// ルートシーン登録
		{
			auto scenePtr = NG_MAKE_SHARED_PTR_CTOR(IScene, APP_MEMALLOC_APPLICATION, CSceneRoot());
			m_sceneMngr.RegisterScene(static_cast<unsigned int>(eSceneId::GAME), scenePtr);
		}

		return true;
	}

	int CApplication::MainLoop()
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

	void CApplication::Finalize()
	{
		m_sceneMngr.Finalize();

		m_toolGUI.Finalize();

		m_graphic.Finalize();
		m_input.Finalize();
		m_window.Destroy();

		m_resSys.Finalize();
		m_appMem.Finalize();

		// NGコアシステム シャットダウン
		ng::CCoreSystem::GetInstance().Shutdown();
		ng::CCoreSystem::DestroyInstance();
	}

	void CApplication::_update()
	{
		const float deltaTime = 0.f;	// TODO:

		m_appMem.ClearWorkMemory();

		m_input.Update();
		m_sceneMngr.Update(deltaTime);
	}

	void CApplication::_render()
	{
		m_toolGUI.BeginRender();
		
		m_sceneMngr.Render();
		
		m_graphic.Render();
		m_toolGUI.EndRender();

		m_sceneMngr.ExecuteChangeScene();
	}

	/*! ウィンドウプロシージャ */
	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if(CToolGUI::WinProcHandler(hWnd, msg, wParam, lParam)) {
			return true;
		}

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
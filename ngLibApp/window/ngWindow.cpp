/*!
* @file		ngWindow.cpp
* @brief	アプリケーションウィンドウ
* @date		2015-04-18
* @author	s.fukami
*/

#include <tchar.h>
#include "ngLibApp/common/ngCommon.h"
#include "ngWindow.h"

namespace ng
{
	CWindow::CWindow()
		: m_hWnd(NULL)
		, m_clientWidth(0)
		, m_clientHeight(0)
	{
		m_className[0] = '\0';
		m_windowName[0] = '\0';
	}

	CWindow::~CWindow()
	{
	}

	bool CWindow::Create(
		unsigned int clientWidht,
		unsigned int clientHeight,
		LPCTSTR className,
		LPCTSTR windowName,
		WNDPROC pWndProc
		)
	{
		// 多重生成
		NG_ASSERT( ! m_hWnd, "ウィンドウ多重生成");
		if(m_hWnd) {
			return false;
		}

		// 各メンバ設定
		m_clientWidth = clientWidht;
		m_clientHeight = clientHeight;
		::_tcscpy_s(m_className, className);
		::_tcscpy_s(m_windowName, windowName);
		
		// ウィンドウクラス設定
		WNDCLASSEX windowClass = {0};
		HINSTANCE hInstance = (HINSTANCE)::GetModuleHandle(0);

		windowClass.cbSize			= sizeof(WNDCLASSEX);
		windowClass.style			= CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc		= pWndProc;
		windowClass.cbClsExtra		= 0;
		windowClass.cbWndExtra		= 0;
		windowClass.hInstance		= hInstance;
		windowClass.hIcon			= ::LoadIcon(hInstance, IDI_APPLICATION);
		windowClass.hCursor			= ::LoadCursor(NULL, IDC_ARROW);
		windowClass.hbrBackground	= CreateSolidBrush(RGB(0,0,255));	//(HBRUSH)::GetStockObject(BLACK_BRUSH);
		windowClass.lpszMenuName	= NULL;
		windowClass.lpszClassName	= m_className;
		windowClass.hIconSm			= ::LoadIcon(NULL, IDI_APPLICATION/*IDI_ASTERISK*/);

		// ウィンドウクラス登録
		if( ! ::RegisterClassEx(&windowClass)) {
			NG_DPRINTF("ウィンドウクラスの登録に失敗\n");
			return false;
		}

		// クライアント領域を確保するための必要なウィンドウサイズを算出
		RECT rc = { 0, 0, (LONG)clientWidht, (LONG)clientHeight};
		::AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

		// ウィンドウの生成
		m_hWnd = ::CreateWindow(
			m_className
			, m_windowName
			, WS_OVERLAPPEDWINDOW
			, 0
			, 0
			, rc.right - rc.left
			, rc.bottom - rc.top
			, NULL
			, NULL
			, hInstance
			, this
			);

		if( ! m_hWnd) {
			NG_DPRINTF("ウィンドウの作成に失敗\n");
			return false;
		}

		return true;
	}

	void CWindow::Show()
	{
		NG_ASSERT(m_hWnd, "ウィンドウが生成されていない");
		if( ! (m_hWnd)) {
			return;
		}

		::ShowWindow(m_hWnd, SW_SHOW);
		::UpdateWindow(m_hWnd);
	}

	void CWindow::UnregisterClass()
	{
		HINSTANCE hInstance = (HINSTANCE)::GetModuleHandle(0);

		if(::UnregisterClass(m_className, hInstance)) {
			ng::DPrintf("ウィンドウクラスの登録を解除しました。 className:%s\n", m_className);
		}
	}

	void CWindow::Destroy()
	{
		if(::DestroyWindow(m_hWnd)) {
			ng::DPrintf("ウィンドウを破棄しました。 windowName:%s\n", m_windowName);
		}
	}

}	// namespace ng

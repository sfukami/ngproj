/*!
* @file		ngConsole.cpp
* @brief	コンソール
* @date		2018-10-15
* @author	s.fukami
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "ngLibCore/common/ngCommon.h"
#include "ngConsole.h"

namespace ng
{
	CConsole CConsole::m_instance;

	CConsole::CConsole()
		: m_isBoot(false)
	{
	}

	CConsole::~CConsole()
	{
		Shutdown();
	}

	bool CConsole::Boot(bool isCloseMenu)
	{
		if(IsBoot()) {
			Shutdown();
		} else {
			::FreeConsole();
		}

		bool ret = ::AllocConsole();
		if(!ret) {
			NG_DPRINT_LASTERRMSG();
			NG_DMSGBOX_LASTERRMSG();
			return ret;
		}

		m_isBoot = ret;

		if(!isCloseMenu) {
			HWND hWnd = ::GetConsoleWindow();
			if(hWnd != nullptr) {
				HMENU hMenu = ::GetSystemMenu(hWnd, FALSE);
				if(hMenu != nullptr) {
					::DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
				}
			}
		}

		// 標準入出力をコンソールに設定
	//	m_stdIn.ReOpen ("CONIN$",  "r", stdin);
		m_stdOut.ReOpen("CONOUT$", "w", stdout);
	//	m_stdErr.ReOpen("CONOUT$", "w", stderr);

		return ret;
	}

	bool CConsole::Shutdown()
	{
		if(!IsBoot()) {
			return false;
		}

		m_isBoot = false;

		m_stdIn.Close();
		m_stdOut.Close();
		m_stdErr.Close();

		return ::FreeConsole();
	}

	void CConsole::Pause()
	{
		if(IsBoot()) {
			::system("pause");
		}
	}

	CConsole* CConsole::_createInstance()
	{
		return &m_instance;
	}

	void CConsole::_destroyInstance(CConsole* pInst)
	{
		// 空定義
	}

}	// namespace ng
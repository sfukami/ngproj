/*!
* @file		ngConsoleMacro.cpp
* @brief	コンソールマクロ
* @date		2018-10-15
* @author	s.fukami
*/

#include "ngConsoleMacro.h"
#include "ngLibCore/io/console/ngConsole.h"

namespace ng
{
	bool _BootConsole(bool isCloseMenu)
	{
		CConsole::CreateInstance();
		return CConsole::GetInstance().Boot(isCloseMenu);
	}

	bool _ShutdownConsole()
	{
		bool ret = CConsole::GetInstance().Shutdown();
		CConsole::DestroyInstance();
		return ret;
	}

	void _PauseConsole()
	{
		CConsole::GetInstance().Pause();
	}

}	// namespace ng

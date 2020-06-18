/*!
* @file		ngConsoleMacro.h
* @brief	コンソールマクロ
* @date		2018-10-15
* @author	s.fukami
*/

#ifndef __NG_CORE_CONSOLE_MACRO_H__
#define __NG_CORE_CONSOLE_MACRO_H__

/*!
* @brief					コンソール起動
* @param isCloseMenu		閉じるボタン有効か
* @return					成否
*/
#define NG_CONSOLE_BOOT(_isCloseMenu)	ng::_BootConsole(_isCloseMenu)

/*!
* @brief					コンソール終了
* @return					成否
*/
#define NG_CONSOLE_SHUTDOWN()	ng::_ShutdownConsole()

/*!
* @brief					コンソール一時停止
*/
#define NG_CONSOLE_PAUSE()		ng::_PauseConsole()

namespace ng
{
	bool _BootConsole(bool isCloseMenu);
	bool _ShutdownConsole();
	void _PauseConsole();

}	// namespace ng

#endif	// __NG_CORE_CONSOLE_MACRO_H__

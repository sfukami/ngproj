/*!
* @file		ngMsgBoxMacro.cpp
* @brief	メッセージボックスマクロ
* @date		2018-10-19
* @author	s.fukami
*/

#include "ngMsgBox.h"
#include "ngMsgBoxMacro.h"

namespace ng
{
	int _MsgBoxA(LPCSTR message, LPCSTR caption, UINT style)
	{
		return MsgBoxA(message, caption, style);
	}
	int _MsgBoxW(LPCWSTR message, LPCWSTR caption, UINT style)
	{
		return MsgBoxW(message, caption, style);
	}

}	// namespace ng

/*!
* @file		ngMsgBox.cpp
* @brief	メッセージボックス
* @date		2018-10-19
* @author	s.fukami
*/

#include <Windows.h>
#include "ngMsgBox.h"

namespace ng
{
	NG_DECL int MsgBoxA(LPCSTR message, LPCSTR caption, UINT style)
	{
		return ::MessageBoxA(nullptr, message, caption, style);
	}
	NG_DECL int MsgBoxW(LPCWSTR message, LPCWSTR caption, UINT style)
	{
		return ::MessageBoxW(nullptr, message, caption, style);
	}

}	// namespace ng

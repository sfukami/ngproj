/*!
* @file		ngDebug.cpp
* @brief	デバッグ機能
* @date		2016-08-22
* @author	s.fukami
*/

#include <stdio.h>
#include <Windows.h>
#include "ngDebug.h"

namespace ng
{
	NG_DECL void SetBreakPoint()
	{
		__debugbreak();
	}

	NG_DECL void SetHardwareBreakPoint(DWORD address)
	{
		// 参考:http://www.lancarse.co.jp/blog/?p=1913

		CONTEXT ctx{};

		ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;
		ctx.Dr0 = address;
		ctx.Dr7 |= 0x00000001;	// 有効
		ctx.Dr7 |= 0x00010000;	// 書き込み時
		ctx.Dr7 |= 0x00080000;	// 8バイト

		::SetThreadContext(::GetCurrentThread(), &ctx);
	}

	NG_DECL void ClearHardwareBreakPoint()
	{
		CONTEXT ctx{};
		::SetThreadContext(::GetCurrentThread(), &ctx);
	}

}	// namespace ng

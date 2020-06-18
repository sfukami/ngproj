/*!
* @file		ngStdIO.cpp
* @brief	標準入出力
* @date		2016-08-22
* @author	s.fukami
*/

#include <stdarg.h>
#include <stdio.h>
#include "ngStdIO.h"

// Printf用バッファサイズ
#define NG_PRINTF_BUFFER_SIZE	( 65536 )

namespace ng
{

NG_DECL void Printf(const char* format, ...)
{
	va_list args;

	va_start(args, format);
	VPrintf(format, args);
	va_end(args);
}
NG_DECL void Printf(const wchar_t* format, ...)
{
	va_list args;

	va_start(args, format);
	VPrintf(format, args);
	va_end(args);
}

NG_DECL void VPrintf(const char* format, va_list args)
{
	// コンソールへ出力
	::vprintf(format, args);
}
NG_DECL void VPrintf(const wchar_t* format, va_list args)
{
	// コンソールへ出力
	::vwprintf(format, args);
}

NG_DECL void DPrintf(const char* format, ...)
{
	va_list args;

	va_start(args, format);
	DVPrintf(format, args);
	va_end(args);
}
NG_DECL void DPrintf(const wchar_t* format, ...)
{
	va_list args;

	va_start(args, format);
	DVPrintf(format, args);
	va_end(args);
}

NG_DECL void DVPrintf(const char* format, va_list args)
{
	// デバッガへ出力
	static char buffer[NG_PRINTF_BUFFER_SIZE + 1] = { '\0' };
	::vsprintf_s(buffer, _countof(buffer), format, args);
	::OutputDebugStringA(buffer);

	// コンソールへ出力
	::vprintf(format, args);
}
NG_DECL void DVPrintf(const wchar_t* format, va_list args)
{
	// デバッガへ出力
	static wchar_t buffer[NG_PRINTF_BUFFER_SIZE + 1] = { '\0' };
	::vswprintf_s(buffer, _countof(buffer), format, args);
	::OutputDebugStringW(buffer);

	// コンソールへ出力
	::vwprintf(format, args);
}

}	// namespace ng
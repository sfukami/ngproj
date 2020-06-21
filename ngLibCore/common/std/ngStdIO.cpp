/*!
* @file		ngStdIO.cpp
* @brief	標準入出力
* @date		2016-08-22
* @author	s.fukami
*/

#include <stdarg.h>
#include <stdio.h>
#include "ngStdIO.h"
#include "ngLibCore/io/stream/ngOutputStream.h"

// Printf用バッファサイズ
#define NG_PRINTF_BUFFER_SIZE	( 65536 )

namespace ng
{

static IOutputStream* g_pPrintOutputStream = nullptr;		//! 文字列出力の出力ストリーム
static IOutputStream* g_pDebugPrintOutputStream = nullptr;	//! 文字列出力（デバッグ用）の出力ストリーム

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

	// 外部設定のストリームへ出力
	if(g_pPrintOutputStream != nullptr)
	{
		static char buffer[NG_PRINTF_BUFFER_SIZE + 1] = { '\0' };
		::vsprintf_s(buffer, _countof(buffer), format, args);

		g_pPrintOutputStream->Write(buffer);
	}
}
NG_DECL void VPrintf(const wchar_t* format, va_list args)
{
	// コンソールへ出力
	::vwprintf(format, args);

	// 外部設定のストリームへ出力
	if(g_pPrintOutputStream != nullptr)
	{
		static wchar_t buffer[NG_PRINTF_BUFFER_SIZE + 1] = { L'\0' };
		::vswprintf_s(buffer, _countof(buffer), format, args);

		g_pPrintOutputStream->Write(buffer);
	}
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

	// 外部設定のストリームへ出力
	if(g_pDebugPrintOutputStream != nullptr) {
		g_pDebugPrintOutputStream->Write(buffer);
	}
}
NG_DECL void DVPrintf(const wchar_t* format, va_list args)
{
	// デバッガへ出力
	static wchar_t buffer[NG_PRINTF_BUFFER_SIZE + 1] = { L'\0' };
	::vswprintf_s(buffer, _countof(buffer), format, args);
	::OutputDebugStringW(buffer);

	// コンソールへ出力
	::vwprintf(format, args);

	// 外部設定のストリームへ出力
	if(g_pDebugPrintOutputStream != nullptr) {
		g_pDebugPrintOutputStream->Write(buffer);
	}
}

NG_DECL void SetPrintOutputStream(IOutputStream* pStream)
{
	g_pPrintOutputStream = pStream;
}

NG_DECL void SetDebugPrintOutputStream(IOutputStream* pStream)
{
	g_pDebugPrintOutputStream = pStream;
}

}	// namespace ng
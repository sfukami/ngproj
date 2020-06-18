/*!
* @file		ngError.cpp
* @brief	エラー関連関数
* @date		2018-10-18
* @author	s.fukami
*/

#include "ngError.h"

namespace ng
{
/*!
* @brief					Win32API エラーコード詳細取得
* @param pBuf				格納先
* @param bufSize			格納先のサイズ
* @return					関数が成功すると、バッファに格納された TCHAR 単位の文字数が返ります。終端の NULL 文字は、この数に含まれません。
* @note						参考:https://msdn.microsoft.com/ja-jp/library/cc428939.aspx
*/
NG_DECL DWORD GetLastErrMsgA(LPSTR pBuf, DWORD bufSize)
{
	return ::FormatMessageA(
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		::GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		pBuf,
		bufSize,
		NULL
		);
}
NG_DECL DWORD GetLastErrMsgW(LPWSTR pBuf, DWORD bufSize)
{
	return ::FormatMessageW(
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		::GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		pBuf,
		bufSize,
		NULL
		);
}

}	// namespace ng

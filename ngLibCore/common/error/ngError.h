/*!
* @file		ngError.h
* @brief	エラー関連関数
* @date		2018-10-18
* @author	s.fukami
*/

#ifndef __NG_CORE_ERROR_H__
#define __NG_CORE_ERROR_H__

#include <Windows.h>

namespace ng
{

/*!
* @brief					Win32API エラーコード詳細取得
* @param pBuf				格納先
* @param bufSize			格納先のサイズ
* @return					関数が成功すると、バッファに格納された TCHAR 単位の文字数が返ります。終端の NULL 文字は、この数に含まれません。
*/
NG_DECL DWORD GetLastErrMsgA(LPSTR pBuf, DWORD bufSize);
NG_DECL DWORD GetLastErrMsgW(LPWSTR pBuf, DWORD bufSize);

#ifdef __cplusplus
// for C++
NG_INLINE NG_DECL DWORD GetLastErrMsg(LPTSTR pBuf, DWORD bufSize)
{
#ifdef UNICODE
	return GetLastErrMsgW(pBuf, bufSize);
#else
	return GetLastErrMsgA(pBuf, bufSize);
#endif	// UNICODE
}
#else
// for C
	#ifdef UNICODE
		#define GetLastErrMsg	GetLastErrMsgW
	#else
		#define GetLastErrMsg	GetLastErrMsgA
	#endif	// UNICODE
#endif	// __cplusplus

}	// namespace ng

#endif	// __NG_CORE_ERROR_H__

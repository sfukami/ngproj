/*!
* @file		ngStdIO.h
* @brief	標準入出力
* @date		2016-08-22
* @author	s.fukami
*/

#ifndef __NG_CORE_STD_IO_H__
#define __NG_CORE_STD_IO_H__

namespace ng
{
	class IOutputStream;
}

namespace ng
{

/*!
* @brief					文字列出力
* @param format				書式
* @param ...				可変長引数
*/
NG_DECL void Printf(const char* format, ...);
NG_DECL void Printf(const wchar_t* format, ...);

/*!
* @brief					文字列出力
* @param format				書式
* @param args				可変長引数
*/
NG_DECL void VPrintf(const char* format, va_list args);
NG_DECL void VPrintf(const wchar_t* format, va_list args);

/*!
* @brief					文字列出力（デバッグ用）
* @param format				書式
* @param ...				可変長引数
*/
NG_DECL void DPrintf(const char* format, ...);
NG_DECL void DPrintf(const wchar_t* format, ...);

/*!
* @brief					文字列出力（デバッグ用）
* @param format				書式
* @param args				可変長引数
*/
NG_DECL void DVPrintf(const char* format, va_list args);
NG_DECL void DVPrintf(const wchar_t* format, va_list args);

/*!
* @brief					文字列出力の出力ストリームを設定
* @param pStream			出力ストリーム
*/
NG_DECL void SetPrintOutputStream(IOutputStream* pStream);

/*!
* @brief					文字列出力（デバッグ用）の出力ストリームを設定
* @param pStream			出力ストリーム
*/
NG_DECL void SetDebugPrintOutputStream(IOutputStream* pStream);

}	// namespace ng

#endif	// __NG_CORE_STD_IO_H__
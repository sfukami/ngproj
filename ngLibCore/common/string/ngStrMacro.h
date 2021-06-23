/*!
* @file		ngStrMacro.h
* @brief	文字列処理マクロ定義
* @date		2016-08-22
* @author	s.fukami
*/

#ifndef __NG_CORE_STR_MACRO_H__
#define __NG_CORE_STR_MACRO_H__

#include "ngStrUtil.h"

/*!
* @brief					文字列クリア
*/
#define NG_STRCLR(_str)		(ng::ClearString(_str))

/*!
* @brief					文字列長さ取得
*/
#define NG_STRLEN(_str)		(ng::StringLength(_str))

/*!
* @brief					文字列比較
*/
#define NG_STRCMP(_s1, _s2)				(ng::CompareString(_s1, _s2))
#define NG_STRCMP_OP(_s1, _op, _s2)		(NG_STRCMP(_s1, _s2) _op 0)

/*!
* @brief					文字列比較（文字数指定）
*/
#define NG_STRNCMP(_s1, _s2, _n)			(::CompareString(_s1, _s2, _n))
#define NG_STRNCMP_OP(_s1, _op, _s2, _n)	(::NG_STRNCMP(_s1, _s2, _n) _op 0)

/*!
* @brief					文字列コピー
*/
#define NG_STRCPY(_dst, _src)			(ng::CopyString(_dst, _src))
#define NG_STRNCPY(_dst, _src, _n)		(ng::CopyString(_dst, _src, _n))
#define NG_STRNCPY_R(_dst, _elem, _src, _n)	(ng::CopyStringFromRight(_dst, _elem, _src, _n))
#define NG_STRNCPY_R_TOARR(_dst, _src, _n)	(ng::CopyStringFromRight(_dst, _src, _n))

/*!
* @brief					文字列連結
*/
#define NG_STRCAT(_dst, _src)		(ng::ConcatenateString(_dst, _src))

/*!
* @brief					書式付き 文字列結合
*/
#define NG_SPRINTF(_str, _format, ...)		(ng::FormatString(_str, _format, __VA_ARGS__))

#endif	// __NG_CORE_STR_MACRO_H__

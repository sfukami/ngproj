/*!
* @file		ngStrUtil.h
* @brief	文字列処理ユーティリティ
* @date		2016-08-22
* @author	s.fukami
*/

#ifndef __NG_CORE_STR_UTIL_H__
#define __NG_CORE_STR_UTIL_H__

namespace ng
{
	/*!
	* @brief					文字列クリア
	*/
	NG_DECL void ClearString(char* str);

	/*!
	* @brief					文字列長さ取得
	*/
	NG_DECL int StringLength(const char* str);

	/*!
	* @brief					文字列比較
	*/
	NG_DECL int CompareString(const char* lh, const char* rh);
	NG_DECL int CompareString(const char* lh, const char* rh, int len);

	/*!
	* @brief					文字列コピー
	*/
	NG_DECL char* CopyString(char* dst, const char* src);
	NG_DECL char* CopyString(char* dst, const char* src, int len);
	NG_DECL char* CopyStringFromRight(char* dst, int elem, const char* src, int len);
	template <int N>
	NG_INLINE char* CopyStringFromRight(char (&dst)[N], const char* src, int len);

	/*!
	* @brief					文字列連結
	*/
	NG_DECL char* ConcatenateString(char* dst, const char* src);

	/*!
	* @brief					書式付き 文字列結合
	*/
	NG_DECL int FormatString(char* str, const char* format, ...);
	
}	// namespace ng

namespace ng
{
	/*!
	* @brief					文字列コピー
	*/
	template <int N>
	NG_INLINE char* CopyStringFromRight(char (&dst)[N], const char* src, int len)
	{
		return CopyStringFromRight(dst, N, src, len);
	}

}	// namespace ng

#endif	// __NG_CORE_STR_UTIL_H__

/*!
* @file		ngStrUtil.cpp
* @brief	文字列処理ユーティリティ
* @date		2016-08-22
* @author	s.fukami
*/

#include <stdio.h>
#include <string.h>
#include "ngStrUtil.h"

#pragma warning(disable:4996)

namespace ng
{
	NG_DECL void ClearString(char* str)
	{
		str[0] = '\0';
	}

	NG_DECL int StringLength(const char* str)
	{
		return (int)::strlen(str);
	}

	NG_DECL int CompareString(const char* lh, const char* rh)
	{
		return ::strcmp(lh, rh);
	}
	NG_DECL int CompareString(const char* lh, const char* rh, int len)
	{
		return ::strncmp(lh, rh, len);
	}

	NG_DECL char* CopyString(char* dst, const char* src)
	{
		return ::strcpy(dst, src);
	}
	NG_DECL char* CopyString(char* dst, const char* src, int len)
	{
		return ::strncpy(dst, src, len);
	}
	NG_DECL char* CopyStringFromRight(char* dst, int elem, const char* src, int len)
	{
		int offset = (len+1) - (elem-1);
		if(offset > 0) {
			return CopyString(dst, src + offset, (len+1) - offset);
		}

		return CopyString(dst, src, len);
	}

	NG_DECL char* ConcatenateString(char* dst, const char* src)
	{
		return ::strcat(dst, src);
	}
	NG_DECL int FormatString(char* str, const char* format, ...)
	{
		va_list args;

		va_start(args, format);
		int ret = ::vsprintf(str, format, args);
		va_end(args);

		return ret;
	}

	// TODO: wchar_t版も強化したい
	NG_DECL wchar_t* ConcatString(wchar_t* dst, const wchar_t* src)
	{
		return ::wcscat(dst, src);
	}

}	// namespace ng

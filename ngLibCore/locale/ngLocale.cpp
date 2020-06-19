/*!
* @file		ngLocale.cpp
* @brief	ロケール関連
* @date		2018-10-19
* @author	s.fukami
*/

#include <locale.h>
#include "ngLocale.h"

namespace ng
{

NG_DECL char* SetLocale(int category, const char* locale)
{
	return ::setlocale(category, locale);
}

NG_DECL char* SetLocaleDefault(int category)
{
	return SetLocale(category, SetLocale(category, ""));
}

}	// namespace ng
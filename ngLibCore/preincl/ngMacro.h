/*!
* @file		ngDefine.h
* @brief	共通マクロ
* @date		2016-08-22
* @author	s.fukami
*/

#ifndef __NG_CORE_MACRO_H__
#define __NG_CORE_MACRO_H__

#include "ngDefine.h"

/*!
* @brief					コンパイラバージョンチェック
*/
#define NG_CHECK_CPLUSPLUS_COMPILER_SUPPORT(_version) \
	(NG_CPLUSPLUS_COMPILER_VERSION >= NG_CPLUSPLUS_COMPILER_VERSION_##_version)

#endif	// __NG_CORE_MACRO_H__
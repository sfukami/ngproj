/*!
* @file		ngEnv.h
* @brief	環境設定
* @date		2017-07-31
* @author	s.fukami
*/

#ifndef __NG_CORE_ENV_H__
#define __NG_CORE_ENV_H__

#include "ngBuild.h"

/*!
* ISO C++ コンパイラ バージョン
* @note						定義済みマクロ __cplusplus は既定では常に 199711L
*							https://docs.microsoft.com/ja-jp/cpp/build/reference/zc-cplusplus?view=vs-2017
*							指定する場合は ngConf.h で定義する
*/
#if !defined(NG_BUILD_CPLUSPLUS_ISO_VERSION)
	#if defined(__cplusplus)
		#if (__cplusplus >= 201703L)
			#define NG_CPLUSPLUS_ISO_17		//!< C++17
		#elif (__cplusplus >= 201402L)
			#define NG_CPLUSPLUS_ISO_14		//!< C++14
		#elif (__cplusplus >= 201103L)
			#define NG_CPLUSPLUS_ISO_11		//!< C++11
		#elif (__cplusplus >= 199711L)
			#define NG_CPLUSPLUS_ISO_03		//!< C++98/03
		#else
			// not C++
		#endif
	#endif	// __cplusplus
#endif	// NG_CONF_CPLUSPLUS_ISO_VERSION

#endif	// __NG_CORE_ENV_H__
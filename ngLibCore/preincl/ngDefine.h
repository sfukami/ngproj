/*!
* @file		ngDefine.h
* @brief	共通定義
* @date		2016-08-22
* @author	s.fukami
*/

#ifndef __NG_CORE_DEFINE_H__
#define __NG_CORE_DEFINE_H__

#include "ngBuild.h"

/*!
* ISO C++ コンパイラ バージョン
* @note						定義済みマクロ __cplusplus は既定では常に 199711L
*							https://docs.microsoft.com/ja-jp/cpp/build/reference/zc-cplusplus?view=vs-2017
*/
#if defined(NG_BUILD_CPLUSPLUS_ISO_VERSION_SPECIFIED)
	// 直指定
	//#define NG_CPLUSPLUS_ISO_20	// C++20
	#define NG_CPLUSPLUS_ISO_17		// C++17
	//#define NG_CPLUSPLUS_ISO_14	// C++14
	//#define NG_CPLUSPLUS_ISO_11	// C++11
	//#define NG_CPLUSPLUS_ISO_03	// C++98/03
#else
	#if defined(__cplusplus)
		#if (__cplusplus > 201703L)
			#define NG_CPLUSPLUS_ISO_17		//!< C++20
		#elif (__cplusplus >= 201703L)
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
#endif	// NG_BUILD_CPLUSPLUS_ISO_VERSION

#define NG_CPLUSPLUS_COMPILER_VERSION_20	(20)
#define NG_CPLUSPLUS_COMPILER_VERSION_17	(17)
#define NG_CPLUSPLUS_COMPILER_VERSION_14	(14)
#define NG_CPLUSPLUS_COMPILER_VERSION_11	(11)
#define NG_CPLUSPLUS_COMPILER_VERSION_03	(3)

#if defined(NG_CPLUSPLUS_ISO_20)
	#define NG_CPLUSPLUS_COMPILER_VERSION	NG_CPLUSPLUS_COMPILER_VERSION_20
#elif defined(NG_CPLUSPLUS_ISO_17)
	#define NG_CPLUSPLUS_COMPILER_VERSION	NG_CPLUSPLUS_COMPILER_VERSION_17
#elif defined(NG_CPLUSPLUS_ISO_14)
	#define NG_CPLUSPLUS_COMPILER_VERSION	NG_CPLUSPLUS_COMPILER_VERSION_14
#elif defined(NG_CPLUSPLUS_ISO_11)
	#define NG_CPLUSPLUS_COMPILER_VERSION	NG_CPLUSPLUS_COMPILER_VERSION_11
#elif defined(NG_CPLUSPLUS_ISO_03)
	#define NG_CPLUSPLUS_COMPILER_VERSION	NG_CPLUSPLUS_COMPILER_VERSION_03
#else
	#define NG_CPLUSPLUS_COMPILER_VERSION	(0)
#endif

/*!
* DLLエクスポート設定
*/
#ifdef NG_BUILD_MAKE_DLL
	#define NG_DECL		__declspec(dllexport)
#else
	#define NG_DECL
#endif

/*!
* インライン
*/
#define NG_INLINE	inline

/*!
* nullptr定義
*/
#ifndef nullptr
	#if ( _MSC_VER <= 1500 )	// Visual Studio 2008以前
		#define nullptr		( NULL )
	#endif
#endif

//! NG エラーコード
#define NG_ERRCODE		HRESULT

//! サイズ指定なし
#define NG_UNSPECIFIED_SIZE		(0)

#endif	// __NG_CORE_DEFINE_H__
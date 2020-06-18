/*!
* @file		ngDefine.h
* @brief	共通定義
* @date		2016-08-22
* @author	s.fukami
*/

#ifndef __NG_CORE_DEFINE_H__
#define __NG_CORE_DEFINE_H__

#include "ngBuild.h"

//! C++規格
#if defined(NG_BUILD_CPLUSPLUS_ISO_VERSION)
	#define NG_CPLUSPLUS_ISO_17		// C++17
	//#define NG_CPLUSPLUS_ISO_14	// C++14
	//#define NG_CPLUSPLUS_ISO_11	// C++11
	//#define NG_CPLUSPLUS_ISO_03	// C++98/03
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

#endif	// __NG_CORE_DEFINE_H__

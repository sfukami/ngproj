/*!
* @file		ngSysUtil.h
* @brief	システムユーティリティ
* @date		2018-02-23
* @author	s.fukami
*/

#ifndef __NG_CORE_SYS_UTIL_H__
#define __NG_CORE_SYS_UTIL_H__

#include "ngLibCore/system/ngCoreSystem.h"

/*!
* @brief					システムメモリアロケータ取得
*/
#define NG_GET_SYSALLOC(_type)	(*ng::CCoreSystem::GetInstance().GetSysMemAlloc(_type))
//! メインシステム
#define NG_SYSALLOC_MAINSYS		(NG_GET_SYSALLOC(ng::eSystemMemoryType::MAINSYS))
//! グラフィック
#define NG_SYSALLOC_GRAPHIC		(NG_GET_SYSALLOC(ng::eSystemMemoryType::GRAPHIC))

#endif	// __NG_CORE_SYS_UTIL_H__
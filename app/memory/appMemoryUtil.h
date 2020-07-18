/*!
* @file		appMemoryUtil.h
* @brief	メモリ ユーティリティ
* @date		2020-07-03
* @author	s.fukami
*/

#ifndef __APP_MEMORY_UTIL_H__
#define __APP_MEMORY_UTIL_H__

#include "appMemoryModule.h"

/*!
* @brief					アプリケーション メモリアロケータ取得
*/
#define APP_GET_MEMALLOC(_id)	(*app::CMemoryModule::GetAllocator(_id))
//! アプリケーション
#define APP_MEMALLOC_APPLICATION	(APP_GET_MEMALLOC(app::eMemoryAllocatorId::APPLICATION))
//! ワーク
#define APP_MEMALLOC_WORK			(APP_GET_MEMALLOC(app::eMemoryAllocatorId::WORK))
//! ゲームアクター
#define APP_MEMALLOC_GAME_ACTOR		(APP_GET_MEMALLOC(app::eMemoryAllocatorId::APPLICATION))
//! ゲームジョブ
#define APP_MEMALLOC_GAME_JOB		(APP_GET_MEMALLOC(app::eMemoryAllocatorId::WORK))

#endif	// __APP_MEMORY_UTIL_H__
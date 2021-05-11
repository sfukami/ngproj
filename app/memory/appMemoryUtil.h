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
#define APP_GET_MEMALLOC(_id)	(*app::CMemoryModule::GetAllocator(app::eMemoryAllocatorId::##_id))

#endif	// __APP_MEMORY_UTIL_H__
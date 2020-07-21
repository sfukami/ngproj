/*!
* @file		appApplicationMemorySize.h
* @brief	アプリケーションメモリサイズ
* @date		2020-07-21
* @author	s.fukami
*/

#ifndef __APP_APPLICATION_MEMORY_SIZE_H__
#define __APP_APPLICATION_MEMORY_SIZE_H__

#include "appMemoryAllocatorId.h"

namespace app
{
	/*!
	* @brief					各メモリアロケータの割り当てサイズを取得
	*/
	unsigned int GetApplicationMemorySize(eMemoryAllocatorId id);

	/*!
	* @brief					各メモリアロケータの割り当てサイズ合計値を取得
	*/
	unsigned int GetApplicationMemorySizeTotal();

}	// namespace app

#endif	// __APP_APPLICATION_MEMORY_SIZE_H__
/*!
* @file		appResourceMemorySize.h
* @brief	リソースメモリサイズ
* @date		2020-07-21
* @author	s.fukami
*/

#ifndef __APP_RESOURCE_MEMORY_SIZE_H__
#define __APP_RESOURCE_MEMORY_SIZE_H__

#include "appResourceMemoryType.h"

namespace app
{
	/*!
	* @brief					各リソースメモリの割り当てサイズを取得
	*/
	unsigned int GetResourceMemorySize(eResourceMemoryType type);

	/*!
	* @brief					各リソースメモリの割り当てサイズ合計値を取得
	*/
	unsigned int GetResourceMemorySizeTotal();

}	// namespace app

#endif	// __APP_RESOURCE_MEMORY_SIZE_H__
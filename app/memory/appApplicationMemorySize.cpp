/*!
* @file		appApplicationMemorySize.cpp
* @brief	アプリケーションメモリサイズ
* @date		2020-07-21
* @author	s.fukami
*/

#include "appApplicationMemorySize.h"

namespace app
{
	const unsigned int s_appMemSizeTbl[ ng::UnderlyingCast(eMemoryAllocatorId::NUM) ] =
	{
		NG_MB(1),	// APPLICATION
		NG_MB(1),	// WORK
		NG_MB(10),	// RESOURCE
		NG_MB(10),	// TEMP
	};

	unsigned int GetApplicationMemorySize(eMemoryAllocatorId id)
	{
		NG_ASSERT(id < eMemoryAllocatorId::NUM);

		return s_appMemSizeTbl[ ng::UnderlyingCast(id) ];
	}

	unsigned int GetApplicationMemorySizeTotal()
	{
		unsigned int total = 0;

		for(auto id : eMemoryAllocatorId())
		{
			total += GetApplicationMemorySize(id);
		}
		
		return total;
	}

}	// namespace app

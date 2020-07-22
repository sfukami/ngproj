/*!
* @file		appResourceMemorySize.h
* @brief	リソースメモリサイズ
* @date		2020-07-21
* @author	s.fukami
*/

#include "appResourceMemoryType.h"

namespace app
{
	const unsigned int s_resMemSizeTbl[ ng::UnderlyingCast(eResourceMemoryType::NUM) ] =
	{
		NG_KB(1),	// MANAGE
		NG_MB(1),	// FIXED
		NG_MB(1),	// SCENE
		NG_MB(1),	// TEMP
	};

	unsigned int GetResourceMemorySize(eResourceMemoryType type)
	{
		NG_ASSERT(type < eResourceMemoryType::NUM);

		return s_resMemSizeTbl[ ng::UnderlyingCast(type) ];
	}

	unsigned int GetResourceMemorySizeTotal()
	{
		unsigned int total = 0;

		for(auto type : eResourceMemoryType())
		{
			total += GetResourceMemorySize(type);
		}
		
		return total;
	}

}	// namespace app
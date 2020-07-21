/*!
* @file		appMemoryAllocatorId.h
* @brief	アプリケーション メモリアロケータID
* @date		2020-07-02
* @author	s.fukami
*/

#ifndef __APP_MEMORY_ALLOCATOR_ID_H__
#define __APP_MEMORY_ALLOCATOR_ID_H__

namespace app
{
	/*!
	* @brief					アプリケーション メモリアロケータID
	*/
	enum class eMemoryAllocatorId : unsigned int
	{
		APPLICATION,	//!< アプリケーション
		WORK,			//!< ワーク

		NUM,
		BEGIN	= 0,
		END		= NUM-1,
	};
	NG_ENUM_RANGE_BASED_FOR_FUNC(eMemoryAllocatorId, BEGIN, END);

}	// namespace ng

#endif	// __APP_MEMORY_ALLOCATOR_ID_H__
/*!
* @file		appResourceMemoryType.h
* @brief	リソースメモリタイプ
* @date		2020-07-21
* @author	s.fukami
*/

#ifndef __APP_RESOURCE_MEMORY_TYPE_H__
#define __APP_RESOURCE_MEMORY_TYPE_H__

namespace app
{
	/*!
	* @brief					リソースメモリタイプ
	*/
	enum class eResourceMemoryType : unsigned int
	{
		MANAGE,		//!< 管理用
		FIXED,		//!< 固定。常駐用
		SCENE,		//!< シーン用
		TEMP,		//!< 一時利用

		NUM,
		BEGIN	= 0,
		END		= NUM-1,
	};
	NG_ENUM_RANGE_BASED_FOR_FUNC(eResourceMemoryType, BEGIN, END);

}	// namespace app

#endif	// __APP_RESOURCE_MEMORY_TYPE_H__

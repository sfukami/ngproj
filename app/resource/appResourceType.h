/*!
* @file		appResourceType.h
* @brief	リソースタイプ
* @date		2021-06-21
* @author	s.fukami
*/

#ifndef __APP_RESOURCE_TYPE_H__
#define __APP_RESOURCE_TYPE_H__

namespace app
{
	/*!
	* @brief					リソースタイプ
	*/
	enum class eResourceType : int
	{
		TEXTURE,	//!< テクスチャ
		SHADER,		//!< シェーダー
		MODEL,		//!< モデル

		NUM,
		BEGIN	= 0,
		END		= NUM - 1,
	};
	NG_ENUM_RANGE_BASED_FOR_FUNC(eResourceType, BEGIN, END);

}	// namespace app

#endif	// __APP_RESOURCE_TYPE_H__
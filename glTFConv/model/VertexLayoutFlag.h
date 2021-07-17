/*!
* @file		VertexLayoutFlag.h
* @brief	頂点レイアウトフラグ
* @date		2021-06-25
* @author	s.fukami
*/

#ifndef __GLTFCONV_VERTEX_LAYOUT_FLAG_H__
#define __GLTFCONV_VERTEX_LAYOUT_FLAG_H__

namespace glTFConv
{
	/*!
	* @brief					頂点レイアウトフラグ
	*/
	enum class eVertexLayoutFlag : ng::u32
	{
		POSITION	= NG_BIT(0),	//!< 頂点
		NORMAL		= NG_BIT(1),	//!< 法線
		TANGENT		= NG_BIT(2),	//!< 接線
		UV0			= NG_BIT(3),	//!< UV座標1
		UV1			= NG_BIT(4),	//!< UV座標2
		JOINT		= NG_BIT(5),	//!< ジョイント
		WEIGHT		= NG_BIT(6),	//!< ウェイト
	};
	NG_ENUM_BITFLAG_OP(eVertexLayoutFlag);

}	// namespace glTFConv

#endif	// __GLTFCONV_VERTEX_LAYOUT_FLAG_H__
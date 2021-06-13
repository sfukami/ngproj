/*!
* @file		ModelFormat.cpp
* @brief	中間モデル形式
* @date		2021-06-08
* @author	s.fukami
*/

#include "ModelFormat.h"

namespace glTFConv
{
	ModelFormat::Vertex::Vertex()
	{
	}

	ModelFormat::Vertex::Vertex(const ng::Vector3& _position, const ng::Vector3& _normal, const ng::Vector2& _uv)
		: position(_position), normal(_normal), uv(_uv)
	{
	}
	
	ModelFormat::Primitive::Primitive()
		: materialIndex(0U)
	{
	}
	
}	// namespace glTFConv
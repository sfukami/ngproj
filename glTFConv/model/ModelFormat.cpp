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
		NG_ZERO_MEMORY(jointIndices, sizeof(jointIndices));
		NG_ZERO_MEMORY(weights, sizeof(weights));
	}

	ModelFormat::Vertex::Vertex(const ng::Vector3& _position, const ng::Vector3& _normal, const ng::Vector2& _uv, ng::u16* _pJointIndices, ng::f32* _pWeights)
		: position(_position), normal(_normal), uv(_uv)
	{
		NG_MEMCPY(jointIndices, _pJointIndices, sizeof(jointIndices));
		NG_MEMCPY(weights, _pWeights, sizeof(weights));
	}
	
	ModelFormat::Primitive::Primitive()
		: materialIndex(0U)
	{
	}
	
}	// namespace glTFConv
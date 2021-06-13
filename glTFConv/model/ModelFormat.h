/*!
* @file		ModelFormat.h
* @brief	中間モデル形式
* @date		2021-06-08
* @author	s.fukami
*/

#ifndef __GLTFCONV_MODEL_FORMAT_H__
#define __GLTFCONV_MODEL_FORMAT_H__

#include <string>
#include <vector>
#include "ngLibCore/geometry/ngGeometry.h"

namespace glTFConv
{
	//! 中間モデル形式
	struct ModelFormat
	{
		//! 頂点
		struct Vertex
		{
			Vertex();
			Vertex(const ng::Vector3& _position, const ng::Vector3& _normal, const ng::Vector2& _uv);

			ng::Vector3 position;	//!< 座標
			ng::Vector3 normal;		//!< 法線
			ng::Vector2 uv;			//!< UV
		};

		//! プリミティブ
		struct Primitive
		{
			Primitive();
			
			std::vector<ng::u32> indices;	//!< インデックス
			ng::u32 materialIndex;	//!< マテリアルのインデックス
		};

		//! メッシュ
		struct Mesh
		{
			std::string name;	//!< 名称
			std::vector<Vertex> vertices;	//!< 頂点
			std::vector<Primitive> primitives;	//!< プリミティブ
		};

		std::vector<Mesh> meshes;	//!< メッシュ
	};

}	// namespace glTFConv

#endif	// __GLTFCONV_MODEL_FORMAT_H__
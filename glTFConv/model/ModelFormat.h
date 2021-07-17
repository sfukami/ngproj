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
			Vertex(const ng::Vector3& _position, const ng::Vector3& _normal, const ng::Vector2& _uv, ng::u16* _pJointIndices, ng::f32* _pWeights);

			ng::Vector3 position;	//!< 座標
			ng::Vector3 normal;		//!< 法線
			ng::Vector2 uv;			//!< UV
			ng::u16 jointIndices[4];	//!< ジョイントのインデックス
			ng::f32 weights[4];		//!< ウェイト
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

		//! テクスチャ
		struct Texture
		{
			std::string name;	//!< 名称
			std::vector<char> data;	//!< 画像データ
		};

		//! マテリアル
		struct Material
		{
			Texture diffuseMap;	//!< ディフューズマップ
		};

		std::vector<Mesh> meshes;	//!< メッシュ
		std::vector<Material> materials;	//!< マテリアル
	};

}	// namespace glTFConv

#endif	// __GLTFCONV_MODEL_FORMAT_H__
/*!
* @file		BinaryFormat.h
* @brief	モデルバイナリ形式
* @date		2021-06-11
* @author	s.fukami
*/

#ifndef __GLTFCONV_BINARY_FORMAT_H__
#define __GLTFCONV_BINARY_FORMAT_H__

#include "ngLibCore/geometry/ngGeometry.h"

namespace glTFConv
{
	//! モデルバイナリ形式
	struct BinaryFormat
	{
		struct MeshHeader;
		struct VertexHeader;
		struct IndexHeader;

		//! モデルヘッダ
		struct ModelHeader
		{
			ModelHeader();
			MeshHeader* GetMeshHeader();
			const MeshHeader* GetMeshHeader() const;

			char signature[4];	//!< シグネチャ
			std::uint32_t meshCount;	//!< メッシュ数
		};

		//! メッシュヘッダ
		struct MeshHeader
		{
			VertexHeader* GetVertexHeader();
			const VertexHeader* GetVertexHeader() const;
			IndexHeader* GetIndexHeader();
			const IndexHeader* GetIndexHeader() const;

			char name[256];	//!< 名称
			std::uint32_t indicesCount;	//!< インデックスバッファ数
		};

		//! 頂点
		struct Vertex
		{
			ng::Vector3 position;	//!< 座標
			ng::Vector3 normal;		//!< 法線
			ng::Vector2 uv;			//!< UV
		};

		//! 頂点ヘッダ
		struct VertexHeader
		{
			Vertex* GetVertexData();
			const Vertex* GetVertexData() const;

			std::uint32_t count;	//!< 頂点数
			std::uint32_t stride;	//!< 1頂点のサイズ（バイト）
			std::uint32_t size;		//!< 総サイズ（バイト）
		};

		//!< インデックスヘッダ
		struct IndexHeader
		{
			ng::u32* GetIndexData();
			const ng::u32* GetIndexData() const;
			IndexHeader* GetNextIndexHeader();
			const IndexHeader* GetNextIndexHeader() const;

			std::uint32_t count;	//!< インデックス数
			std::uint32_t size;		//!< 総サイズ（バイト）
			std::uint32_t materialIndex;	//!< マテリアルのインデックス
		};

		ModelHeader modelHeader;	//!< モデルヘッダ
	};

}	// namespace glTFConv

#endif	// __GLTFCONV_BINARY_FORMAT_H__
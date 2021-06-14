/*!
* @file		BinaryFormat.h
* @brief	モデルバイナリ形式
* @date		2021-06-11
* @author	s.fukami
*/

#ifndef __GLTFCONV_BINARY_FORMAT_H__
#define __GLTFCONV_BINARY_FORMAT_H__

#include "ngLibCore/geometry/ngGeometry.h"

#define GLTFCONV_BINARY_FORMAT_MODEL_SIGNATURE	("mdl")

namespace glTFConv
{
	//! モデルバイナリ形式
	struct BinaryFormat
	{
		struct MeshHeader;
		struct VertexHeader;
		struct IndexHeader;
		struct MaterialHeader;

		//! モデルヘッダ
		struct ModelHeader
		{
			ModelHeader();
			MeshHeader* GetMeshHeader();
			const MeshHeader* GetMeshHeader() const;

			bool CheckSignature() const;

			char signature[4];	//!< シグネチャ
			std::uint32_t meshCount;	//!< メッシュ数
			std::uint32_t materialCount;	//!< マテリアル数
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

		//! インデックスヘッダ
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

		//! テクスチャ
		struct TextureHeader
		{
			char* GetTextureData();
			const char* GetTextureData() const;
			TextureHeader* GetNextTextureHeader();
			const TextureHeader* GetNextTextureHeader() const;

			char name[256];		//!< 名称
			std::uint32_t size;		//!< 総サイズ（バイト）
		};

		//! マテリアルヘッダ
		struct MaterialHeader
		{
			TextureHeader* GetTextureHeader();
			const TextureHeader* GetTextureHeader() const;

			std::uint32_t textureCount;	//!< テクスチャ数
		};

		ModelHeader modelHeader;	//!< モデルヘッダ
	};

	inline BinaryFormat::MeshHeader* BinaryFormat::ModelHeader::GetMeshHeader()
	{
		return ng::PointerOffset<MeshHeader*>(this, sizeof(*this));
	}
	inline const BinaryFormat::MeshHeader* BinaryFormat::ModelHeader::GetMeshHeader() const
	{
		return const_cast<ModelHeader*>(this)->GetMeshHeader();
	}

	inline bool BinaryFormat::ModelHeader::CheckSignature() const
	{
		return NG_STRCMP_OP(signature, ==, GLTFCONV_BINARY_FORMAT_MODEL_SIGNATURE);
	}

	inline BinaryFormat::VertexHeader* BinaryFormat::MeshHeader::GetVertexHeader()
	{
		return ng::PointerOffset<VertexHeader*>(this, sizeof(*this));
	}
	inline const BinaryFormat::VertexHeader* BinaryFormat::MeshHeader::GetVertexHeader() const
	{
		return const_cast<MeshHeader*>(this)->GetVertexHeader();
	}

	inline BinaryFormat::IndexHeader* BinaryFormat::MeshHeader::GetIndexHeader()
	{
		const VertexHeader* pVertexHeader = GetVertexHeader();

		return ng::PointerOffset<IndexHeader*>(pVertexHeader->GetVertexData(), pVertexHeader->size);
	}
	inline const BinaryFormat::IndexHeader* BinaryFormat::MeshHeader::GetIndexHeader() const
	{
		return const_cast<MeshHeader*>(this)->GetIndexHeader();
	}

	inline BinaryFormat::Vertex* BinaryFormat::VertexHeader::GetVertexData()
	{
		return ng::PointerOffset<Vertex*>(this, sizeof(*this));
	}
	inline const BinaryFormat::Vertex* BinaryFormat::VertexHeader::GetVertexData() const
	{
		return const_cast<VertexHeader*>(this)->GetVertexData();
	}

	inline ng::u32* BinaryFormat::IndexHeader::GetIndexData()
	{
		return ng::PointerOffset<ng::u32*>(this, sizeof(*this));
	}
	inline const ng::u32* BinaryFormat::IndexHeader::GetIndexData() const
	{
		return const_cast<IndexHeader*>(this)->GetIndexData();
	}

	inline BinaryFormat::IndexHeader* BinaryFormat::IndexHeader::GetNextIndexHeader()
	{
		return ng::PointerOffset<IndexHeader*>(GetIndexData(), size);
	}
	inline const BinaryFormat::IndexHeader* BinaryFormat::IndexHeader::GetNextIndexHeader() const
	{
		return const_cast<IndexHeader*>(this)->GetNextIndexHeader();
	}

	inline char* BinaryFormat::TextureHeader::GetTextureData()
	{
		return ng::PointerOffset<char*>(this, sizeof(*this));
	}
	inline const char* BinaryFormat::TextureHeader::GetTextureData() const
	{
		return const_cast<TextureHeader*>(this)->GetTextureData();
	}

	inline BinaryFormat::TextureHeader* BinaryFormat::TextureHeader::GetNextTextureHeader()
	{
		return ng::PointerOffset<TextureHeader*>(GetTextureData(), size);
	}
	inline const BinaryFormat::TextureHeader* BinaryFormat::TextureHeader::GetNextTextureHeader() const
	{
		return const_cast<TextureHeader*>(this)->GetNextTextureHeader();
	}

	inline BinaryFormat::TextureHeader* BinaryFormat::MaterialHeader::GetTextureHeader()
	{
		return ng::PointerOffset<TextureHeader*>(this, sizeof(*this));
	}
	inline const BinaryFormat::TextureHeader* BinaryFormat::MaterialHeader::GetTextureHeader() const
	{
		return const_cast<MaterialHeader*>(this)->GetTextureHeader();
	}

}	// namespace glTFConv

#endif	// __GLTFCONV_BINARY_FORMAT_H__
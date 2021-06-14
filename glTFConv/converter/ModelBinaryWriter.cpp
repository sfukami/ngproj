/*!
* @file		ModelBinaryWriter.cpp
* @brief	中間モデル形式 バイナリ出力
* @date		2021-06-11
* @author	s.fukami
*/

#include "ngLibCore/io/file/ngFile.h"
#include "ModelBinaryWriter.h"

namespace glTFConv
{
	CModelBinaryWriter::CModelBinaryWriter()
	{
	}

	CModelBinaryWriter::~CModelBinaryWriter()
	{
	}

	bool CModelBinaryWriter::Write(const char* pFilePath, const ModelFormat& modelFormat) const
	{
		// 出力するバイナリの総サイズを算出
		size_t binarySize = 0;
		{
			size_t meshCount = 0, vertexCount = 0, primitiveCount = 0, indexCount = 0, materialCount = 0, textureTotalSize = 0;
			meshCount = modelFormat.meshes.size();
			for(const auto& mesh : modelFormat.meshes)
			{
				vertexCount += mesh.vertices.size();
				primitiveCount += mesh.primitives.size();
				for(const auto& primitive : mesh.primitives)
				{
					indexCount += primitive.indices.size();
				}
			}
			materialCount = modelFormat.materials.size();
			for(const auto& material : modelFormat.materials)
			{
				textureTotalSize += material.diffuseMap.data.size();
			}

			binarySize += sizeof(BinaryFormat::ModelHeader);
			binarySize += meshCount * sizeof(BinaryFormat::MeshHeader);
			binarySize += meshCount * sizeof(BinaryFormat::VertexHeader);
			binarySize += vertexCount * sizeof(BinaryFormat::Vertex);
			binarySize += primitiveCount * sizeof(BinaryFormat::IndexHeader);
			binarySize += indexCount * sizeof(ng::u32);
			binarySize += materialCount * sizeof(BinaryFormat::MaterialHeader);
			binarySize += materialCount * sizeof(BinaryFormat::TextureHeader);
			binarySize += textureTotalSize;
		}

		char* pBinary = new char[binarySize];

		BinaryFormat* pBinaryFormat = new(pBinary) BinaryFormat;
		pBinaryFormat->modelHeader.meshCount = static_cast<std::uint32_t>(modelFormat.meshes.size());

		// メッシュ情報書き込み
		BinaryFormat::MeshHeader* pMeshHeader = pBinaryFormat->modelHeader.GetMeshHeader();
		for(const auto& mesh : modelFormat.meshes)
		{
			size_t writeSize = _writeMeshInfo(pMeshHeader, mesh);
			pMeshHeader = ng::PointerOffset<BinaryFormat::MeshHeader*>(pMeshHeader, writeSize);
		}

		// マテリアル情報書き込み
		BinaryFormat::MaterialHeader* pMaterialHeader = ng::PointerCast<BinaryFormat::MaterialHeader*>(pMeshHeader);
		for(const auto& material : modelFormat.materials)
		{
			size_t writeSize = _writeMaterialInfo(pMaterialHeader, material);
			pMaterialHeader = ng::PointerOffset<BinaryFormat::MaterialHeader*>(pMaterialHeader, writeSize);
		}

		// ファイル出力
		bool result = false;
		ng::CFile outputFile;
		NG_ERRCODE err = outputFile.Open(pFilePath, "wb");
		if(NG_SUCCEEDED(err)) {
			ng::size_type writeNum = outputFile.Write(pBinary, binarySize);
			if(writeNum > 0) {
				result = true;
			}
			else {
				NG_ERRLOG("CModelBinaryWriter", "出力先ファイルの書き込みに失敗しました.");
			}
		} else {
			NG_ERRLOG_C("CModelBinaryWriter", err, "出力先ファイルのオープンに失敗しました.");
		}

		delete[] pBinary;

		return result;
	}

	size_t CModelBinaryWriter::_writeMeshInfo(BinaryFormat::MeshHeader* pMeshHeader, const ModelFormat::Mesh& mesh) const
	{
		size_t totalSize = sizeof(BinaryFormat::MeshHeader);

		NG_STRCPY(pMeshHeader->name, mesh.name.c_str());
		pMeshHeader->indicesCount = static_cast<std::uint32_t>(mesh.primitives.size());

		BinaryFormat::VertexHeader* pVertexHeader = pMeshHeader->GetVertexHeader();
		pVertexHeader->count = static_cast<std::uint32_t>(mesh.vertices.size());
		pVertexHeader->size = pVertexHeader->count * sizeof(BinaryFormat::Vertex);
		pVertexHeader->stride = sizeof(BinaryFormat::Vertex);
		BinaryFormat::Vertex* pVertexData = pVertexHeader->GetVertexData();
		NG_MEMCPY(pVertexData, &mesh.vertices[0], pVertexHeader->size);
		totalSize += sizeof(BinaryFormat::VertexHeader) + pVertexHeader->size;

		BinaryFormat::IndexHeader* pIndexHeader = pMeshHeader->GetIndexHeader();
		for(const auto& primitive : mesh.primitives)
		{
			totalSize += _writePrimitiveInfo(pIndexHeader, primitive);
			pIndexHeader = pIndexHeader->GetNextIndexHeader();
		}
		
		return totalSize;
	}

	size_t CModelBinaryWriter::_writePrimitiveInfo(BinaryFormat::IndexHeader* pIndexHeader, const ModelFormat::Primitive& primitive) const
	{
		pIndexHeader->count = static_cast<std::uint32_t>(primitive.indices.size());
		pIndexHeader->size = pIndexHeader->count * sizeof(ng::u32);
		pIndexHeader->materialIndex = primitive.materialIndex;

		ng::u32* pIndexData = pIndexHeader->GetIndexData();
		NG_MEMCPY(pIndexData, &primitive.indices[0], pIndexHeader->size);

		return sizeof(BinaryFormat::IndexHeader) + pIndexHeader->size;
	}

	size_t CModelBinaryWriter::_writeMaterialInfo(BinaryFormat::MaterialHeader* pMaterialHeader, const ModelFormat::Material& material) const
	{
		size_t totalSize = sizeof(BinaryFormat::MaterialHeader);

		pMaterialHeader->textureCount = 1U;

		BinaryFormat::TextureHeader* pTextureHeader = pMaterialHeader->GetTextureHeader();
		totalSize += _writeTextureInfo(pTextureHeader, material.diffuseMap);

		return totalSize;
	}

	size_t CModelBinaryWriter::_writeTextureInfo(BinaryFormat::TextureHeader* pTextureHeader, const ModelFormat::Texture& texture) const
	{
		NG_STRCPY(pTextureHeader->name, texture.name.c_str());
		pTextureHeader->size = static_cast<std::uint32_t>(texture.data.size());

		char* pTextureData = pTextureHeader->GetTextureData();
		NG_MEMCPY(pTextureData, &texture.data[0], pTextureHeader->size);

		return sizeof(BinaryFormat::TextureHeader) + pTextureHeader->size;
	}

}	// namespace glTFConv
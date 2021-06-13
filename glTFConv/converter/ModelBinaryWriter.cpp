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
		size_t binarySize = 0;
		{
			size_t meshCount = 0, vertexCount = 0, primitiveCount = 0, indexCount = 0;
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

			binarySize += sizeof(BinaryFormat::ModelHeader);
			binarySize += meshCount * sizeof(BinaryFormat::MeshHeader);
			binarySize += meshCount * sizeof(BinaryFormat::VertexHeader);
			binarySize += vertexCount * sizeof(BinaryFormat::Vertex);
			binarySize += primitiveCount * sizeof(BinaryFormat::IndexHeader);
			binarySize += indexCount * sizeof(ng::u32);
		}

		ng::CFile outputFile;
		NG_ERRCODE err = outputFile.Open(pFilePath, "wb");
		if(NG_FAILED(err)) {
			NG_ERRLOG_C("CModelBinaryWriter", err, "出力先ファイルのオープンに失敗しました.");
			return false;
		}

		char* pBinary = new char[binarySize];

		BinaryFormat* pBinaryFormat = new(pBinary) BinaryFormat;
		pBinaryFormat->modelHeader.meshCount = static_cast<std::uint32_t>(modelFormat.meshes.size());

		BinaryFormat::MeshHeader* pMeshHeader = pBinaryFormat->modelHeader.GetMeshHeader();
		for(const auto& mesh : modelFormat.meshes)
		{
			size_t writeSize = _writeMeshInfo(pMeshHeader, mesh);
			pMeshHeader = ng::PointerOffset<BinaryFormat::MeshHeader*>(pMeshHeader, writeSize);
		}

		ng::size_type writeNum = outputFile.Write(pBinary, binarySize);
		delete[] pBinary;
		if(writeNum < 1) {
			NG_ERRLOG("CModelBinaryWriter", "出力先ファイルの書き込みに失敗しました.");
			return false;
		}

		return true;
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

}	// namespace glTFConv
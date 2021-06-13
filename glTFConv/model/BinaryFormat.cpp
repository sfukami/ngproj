/*!
* @file		BinaryFormat.cpp
* @brief	モデルバイナリ形式
* @date		2021-06-11
* @author	s.fukami
*/

#include "BinaryFormat.h"

namespace glTFConv
{
	BinaryFormat::ModelHeader::ModelHeader()
		: signature("mdl")
	{
	}

	BinaryFormat::MeshHeader* BinaryFormat::ModelHeader::GetMeshHeader()
	{
		return ng::PointerOffset<MeshHeader*>(this, sizeof(*this));
	}
	const BinaryFormat::MeshHeader* BinaryFormat::ModelHeader::GetMeshHeader() const
	{
		return const_cast<BinaryFormat::ModelHeader*>(this)->GetMeshHeader();
	}

	BinaryFormat::VertexHeader* BinaryFormat::MeshHeader::GetVertexHeader()
	{
		return ng::PointerOffset<VertexHeader*>(this, sizeof(*this));
	}
	const BinaryFormat::VertexHeader* BinaryFormat::MeshHeader::GetVertexHeader() const
	{
		return const_cast<BinaryFormat::MeshHeader*>(this)->GetVertexHeader();
	}

	BinaryFormat::IndexHeader* BinaryFormat::MeshHeader::GetIndexHeader()
	{
		const VertexHeader* pVertexHeader = GetVertexHeader();

		return ng::PointerOffset<IndexHeader*>(pVertexHeader->GetVertexData(), pVertexHeader->size);
	}
	const BinaryFormat::IndexHeader* BinaryFormat::MeshHeader::GetIndexHeader() const
	{
		return const_cast<BinaryFormat::MeshHeader*>(this)->GetIndexHeader();
	}

	BinaryFormat::Vertex* BinaryFormat::VertexHeader::GetVertexData()
	{
		return ng::PointerOffset<Vertex*>(this, sizeof(*this));
	}
	const BinaryFormat::Vertex* BinaryFormat::VertexHeader::GetVertexData() const
	{
		return const_cast<BinaryFormat::VertexHeader*>(this)->GetVertexData();
	}

	ng::u32* BinaryFormat::IndexHeader::GetIndexData()
	{
		return ng::PointerOffset<ng::u32*>(this, sizeof(*this));
	}
	const ng::u32* BinaryFormat::IndexHeader::GetIndexData() const
	{
		return const_cast<BinaryFormat::IndexHeader*>(this)->GetIndexData();
	}

	BinaryFormat::IndexHeader* BinaryFormat::IndexHeader::GetNextIndexHeader()
	{
		return ng::PointerOffset<IndexHeader*>(GetIndexData(), size);
	}
	const BinaryFormat::IndexHeader* BinaryFormat::IndexHeader::GetNextIndexHeader() const
	{
		return const_cast<BinaryFormat::IndexHeader*>(this)->GetNextIndexHeader();
	}

}	// namespace glTFConv
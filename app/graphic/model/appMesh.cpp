/*!
* @file		appMesh.cpp
* @brief	メッシュ
* @date		2021-06-13
* @author	s.fukami
*/

#include "appMesh.h"
#include "app/graphic/appGraphicUtil.h"
#include "glTFConv/model/BinaryFormat.h"

namespace app
{
	CMesh::CMesh()
	{
	}
	CMesh::~CMesh()
	{
	}

	bool CMesh::Create(const void* pVertices, ng::u32 verticesSize, const ng::u32* pIndices, ng::u32 indicesSize)
	{
		ng::CDX12Device* pDX12Device = GraphicUtil::GetDX12Device();

		// DX12ポリゴン生成
		NG_ERRCODE err = m_polygon.Create(
			*pDX12Device,
			pVertices,
			verticesSize,
			sizeof(glTFConv::BinaryFormat::Vertex),
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
			pIndices,
			indicesSize
			);
		if(NG_FAILED(err)) {
			NG_ERRLOG_C("Mesh", err, "DX12ポリゴンの生成に失敗しました.");
			return false;
		}

		return true;
	}

	void CMesh::Destroy()
	{
		m_polygon.Destroy();
	}

	void CMesh::Render(
		ng::CDX12CommandList& commandList
		) const
	{
		m_polygon.Render(commandList);
	}

}	// namespace app
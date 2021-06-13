/*!
* @file		appModel.cpp
* @brief	モデル
* @date		2021-06-13
* @author	s.fukami
*/

#include "appModel.h"
#include "appMesh.h"
#include "app/memory/appMemoryUtil.h"
#include "glTFConv/model/BinaryFormat.h"

namespace app
{
	CModel::CModel()
	{
	}
	CModel::~CModel()
	{
		Destroy();
	}

	bool CModel::Build(const void* pBinary, ng::size_type size, const void* pBuildParam)
	{
		using Format = glTFConv::BinaryFormat;
		const Format* pBinaryFormat = ng::PointerCast<const Format*>(pBinary);
		const Format::ModelHeader& modelHeader = pBinaryFormat->modelHeader;
		if(!modelHeader.CheckSignature()) {
			NG_ERRLOG("Model", "モデルのシグネチャチェックに失敗しました.");
			return false;
		}

		const Format::MeshHeader* pMeshHeader = modelHeader.GetMeshHeader();
		for(ng::u32 i = 0; i < modelHeader.meshCount; i++)
		{
			// 頂点
			const Format::VertexHeader* pVertexHeader = pMeshHeader->GetVertexHeader();
			const Format::Vertex* pVertexData = pVertexHeader->GetVertexData();

			const Format::IndexHeader* pIndexHeader = pMeshHeader->GetIndexHeader();
			for(ng::u32 j = 0; j < pMeshHeader->indicesCount; j++)
			{
				// インデックス
				const ng::u32* pIndexData = pIndexHeader->GetIndexData();

				// メッシュ生成
				CMesh* pMesh = _createMesh(pVertexData, pVertexHeader->size, pIndexData, pIndexHeader->size);
				if(pMesh == nullptr) {
					return false;
				}
				m_meshList.PushBack(*pMesh);

				pIndexHeader = pIndexHeader->GetNextIndexHeader();
			}

			pMeshHeader = ng::PointerCast<const Format::MeshHeader*>(pIndexHeader);
		}

		return true;
	}

	void CModel::Destroy()
	{
		// 全てのメッシュを削除
		for(MeshList::NodeType* pNode = m_meshList.Begin(); pNode != m_meshList.End();)
		{
			MeshList::NodeType* pNext = pNode->GetNext();
			CMesh* pMesh = &pNode->GetElem();
			m_meshList.Erase(pNode);

			// メッシュ破棄
			_deleteMesh(pMesh);

			pNode = pNext;
		}
	}

	void CModel::Render(
		ng::CDX12CommandList& commandList
		) const
	{
		// 全てのメッシュを描画
		for(const MeshList::NodeType* pNode = m_meshList.Begin(); pNode != m_meshList.End(); pNode = pNode->GetNext())
		{
			pNode->GetElem().Render(commandList);
		}
	}

	CMesh* CModel::_createMesh(const void* pVertices, ng::u32 verticesSize, const ng::u32* pIndices, ng::u32 indicesSize)
	{
		CMesh* pMesh = NG_NEW(APP_GET_MEMALLOC(RESOURCE)) CMesh;
		if(!pMesh->Create(pVertices, verticesSize, pIndices, indicesSize)) {
			NG_ERRLOG("Model", "メッシュの生成に失敗しました.");
			_deleteMesh(pMesh);
			return nullptr;
		}

		return pMesh;
	}

	void CModel::_deleteMesh(CMesh* pMesh)
	{
		pMesh->Destroy();
		NG_DELETE(APP_GET_MEMALLOC(RESOURCE), pMesh);
	}

}	// namespace app
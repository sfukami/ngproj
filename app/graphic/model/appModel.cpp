/*!
* @file		appModel.cpp
* @brief	モデル
* @date		2021-06-13
* @author	s.fukami
*/

#include "appModel.h"
#include "appMesh.h"
#include "../material/appMaterial.h"
#include "../material/appMaterialFormat.h"
#include "../material/appMaterialBuilder.h"
#include "../material/appMaterialUtil.h"
#include "../shader/effect/appShaderEffect.h"
#include "app/resource/appResourceType.h"
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

		// 生成するメッシュの総数を算出し、メッシュの配列を初期化
		{
			ng::u32 createNum = 0;
			const Format::MeshHeader* pMeshHeader = modelHeader.GetMeshHeader();
			for(ng::u32 i = 0; i < modelHeader.meshCount; i++)
			{
				createNum += pMeshHeader->indicesCount;
				pMeshHeader = pMeshHeader->GetNextMeshHeader();
			}

			m_meshArr.Initialize(APP_GET_MEMALLOC(RESOURCE), createNum);
		}
		// 生成するマテリアルの総数を算出し、マテリアルの配列を初期化
		{
			ng::u32 createNum = modelHeader.materialCount;
			m_matArr.Initialize(APP_GET_MEMALLOC(RESOURCE), createNum);
		}

		{
			// メッシュ生成
			int createCount = 0;
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
					CMesh* pMesh = _createMesh(
						pVertexData, pVertexHeader->size, pIndexData, pIndexHeader->size, pIndexHeader->materialIndex
						);
					if(pMesh == nullptr) {
						return false;
					}
					m_meshArr[ createCount++ ] = pMesh;

					pIndexHeader = pIndexHeader->GetNextIndexHeader();
				}

				pMeshHeader = ng::PointerCast<const Format::MeshHeader*>(pIndexHeader);
			}

			// マテリアル生成
			createCount = 0;
			MaterialFormat format;
			_getMaterialFormat(&format);
			const Format::MaterialHeader* pMaterialHeader = ng::PointerCast<const Format::MaterialHeader*>(pMeshHeader);
			for(ng::u32 i = 0; i < modelHeader.materialCount; i++)
			{
				const Format::TextureHeader* pTextureHeader = pMaterialHeader->GetTextureHeader();
				for(ng::u32 j = 0; j < pMaterialHeader->textureCount; j++)
				{
					format.diffuseMap.SetName(pTextureHeader->name);
					format.diffuseMap.pBinary = pTextureHeader->GetTextureData();
					format.diffuseMap.size = pTextureHeader->size;

					pTextureHeader = pTextureHeader->GetNextTextureHeader();
				}

				CMaterial* pMaterial = _createMaterial(format);
				if(pMaterial == nullptr) {
					return false;
				}
				m_matArr[ createCount++ ] = pMaterial;
				
				pMaterialHeader = ng::PointerCast<const Format::MaterialHeader*>(pTextureHeader);
			}
		}

		return true;
	}

	void CModel::Destroy()
	{
		// 全てのメッシュを削除
		for(ng::u32 i = 0; i < m_meshArr.Size(); i++)
		{
			_deleteMesh(m_meshArr[i]);
		}
		// 全てのマテリアルを削除
		for(ng::u32 i = 0; i < m_matArr.Size(); i++)
		{
			_deleteMaterial(m_matArr[i]);
		}
		m_meshArr.Finalize();
		m_matArr.Finalize();
	}

	CModel::MeshArray& CModel::GetMeshArray()
	{
		return m_meshArr;
	}
	const CModel::MeshArray& CModel::GetMeshArray() const
	{
		return m_meshArr;
	}

	CModel::MaterialArray& CModel::GetMaterialArray()
	{
		return m_matArr;
	}
	const CModel::MaterialArray& CModel::GetMaterialArray() const
	{
		return m_matArr;
	}

	int CModel::GetResourceType() const
	{
		return ng::UnderlyingCast(eResourceType::MODEL);
	}

	CMesh* CModel::_createMesh(
		const void* pVertices, ng::u32 verticesSize, const ng::u32* pIndices, ng::u32 indicesSize, ng::u32 materialIndex
		)
	{
		CMesh* pMesh = NG_NEW(APP_GET_MEMALLOC(RESOURCE)) CMesh;
		if(!pMesh->Create(pVertices, verticesSize, pIndices, indicesSize, materialIndex)) {
			NG_ERRLOG("Model", "メッシュの生成に失敗しました.");
			_deleteMesh(pMesh);
			return nullptr;
		}

		return pMesh;
	}

	void CModel::_deleteMesh(CMesh*& pMesh)
	{
		if(pMesh) {
			pMesh->Destroy();
			NG_SAFE_DELETE(APP_GET_MEMALLOC(RESOURCE), pMesh);
		}
	}

	CMaterial* CModel::_createMaterial(const MaterialFormat& format)
	{
		CMaterial* pMaterial = NG_NEW(APP_GET_MEMALLOC(RESOURCE)) CMaterial;

		CMaterialBuilder builder;
		if(!builder.Build(format, pMaterial)) {
			NG_ERRLOG("Model", "マテリアルの生成に失敗しました.");
			_deleteMaterial(pMaterial);
			return nullptr;
		}

		return pMaterial;
	}

	void CModel::_deleteMaterial(CMaterial*& pMaterial)
	{
		if(pMaterial) {
			pMaterial->Destroy();
			NG_SAFE_DELETE(APP_GET_MEMALLOC(RESOURCE), pMaterial);
		}
	}

	void CModel::_getMaterialFormat(MaterialFormat* pDst)
	{
		MaterialUtil::GetMaterialFormatModel(pDst);
	}

}	// namespace app
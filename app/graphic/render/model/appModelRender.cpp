/*!
* @file		appModelRender.cpp
* @brief	モデル描画
* @date		2021-06-21
* @author	s.fukami
*/

#include "appModelRender.h"
#include "app/graphic/model/appMesh.h"
#include "app/graphic/material/appMaterial.h"
#include "app/graphic/shader/effect/appShaderEffect.h"
#include "app/graphic/shader/effect/appShaderParam.h"
#include "app/resource/appResourceModule.h"
#include "../appRenderParam.h"
#include "../../appGraphicUtil.h"

namespace app
{
	CModelRender::CModelRender()
	{
	}
	CModelRender::~CModelRender()
	{
		Destroy();
	}

	bool CModelRender::Create(const char* modelFilePath, eResourceMemoryType resMemType)
	{
		bool result = CResourceModule::LoadResourceFromFile<CModel>(modelFilePath, resMemType, m_handle);
		return result;
	}

	void CModelRender::Destroy()
	{
		m_handle.Release();
	}

	bool CModelRender::IsEnable() const
	{
		return m_handle.IsValid();
	}

	void CModelRender::_render(const RenderParam& param)
	{
		ng::CWeakPtr<CModel> modelPtr = m_handle.GetResource();

		CModel::MeshArray& meshArr = modelPtr->GetMeshArray();
		CModel::MaterialArray& matArr = modelPtr->GetMaterialArray();
		for(ng::u32 i = 0; i < meshArr.Size(); i++)
		{
			const CMesh* pMesh = meshArr[i];
			if(pMesh) {
				_renderMesh(param, *pMesh, matArr[ pMesh->GetMaterialIndex() ]);
			}
		}
	}

	void CModelRender::_renderMesh(const RenderParam& param, const CMesh& mesh, CMaterial* pMaterial)
	{
		ng::CDX12CommandList* pCmdList = GraphicUtil::GetDX12CommandList(param.cmdListId);
		NG_ASSERT_NOT_NULL(pCmdList);

		// 各設定・リソースをコマンドリストへ設定
		if(pMaterial) {
			pMaterial->BindPipelineState(*pCmdList);
			pMaterial->BindRootSignature(*pCmdList);

			auto shdEffPtr = pMaterial->GetShaderEffect();
			if(shdEffPtr) {
				ShaderParam shdPrm;
				ng::MatrixOp::Transpose(shdPrm.wvpMat, param.wvpMat);

				shdEffPtr->SetParameter(shdPrm);
				shdEffPtr->UpdateConstantBuffer();
				shdEffPtr->BindResource(*pCmdList);
			}
			
			pMaterial->BindResource(*pCmdList);
		}

		// メッシュ描画
		mesh.Render(*pCmdList);
	}

}	// namespace app
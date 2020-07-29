/*!
* @file		appMaterial.cpp
* @brief	マテリアル
* @date		2020-07-22
* @author	s.fukami
*/

#include "ngLibGraphic/graphic/dx12/pipeline/ngDX12PipelineStateDesc.h"
#include "ngLibGraphic/graphic/dx12/polygon/ngDX12VertexLayout.h"
#include "appMaterial.h"
#include "appMaterialFormat.h"
#include "app/resource/appResourceModule.h"
#include "../appGraphicModule.h"

namespace app
{
	CMaterial::CMaterial()
	{
	}
	CMaterial::~CMaterial()
	{
		Destroy();
	}
	
	bool CMaterial::Build(const MaterialData& data)
	{
		bool result = true;

		// ディフューズマップ読み込み
		result &= _loadResource(data.diffuseMap.filePath, nullptr, m_diffuseMap);

		// 頂点シェーダー読み込み
		result &= _loadShaderResource(data.vertexShader, m_vertexShader);
		// ピクセルシェーダー読み込み
		result &= _loadShaderResource(data.pixelShader, m_pixelShader);

		// DX12ルートシグネチャ取得
		if(!CGraphicModule::GetRootSignature(data.rootSignName, m_rootSign)) {
			NG_ERRLOG("Material", "DX12ルートシグネチャの取得に失敗しました. name:%s", data.rootSignName);
			result = false;
		}
		// DX12パイプラインステート取得
		if(!CGraphicModule::GetPipelineState(data.plStateName, m_plState)) {
			ng::CDX12PipelineStateDesc stateDesc;
			stateDesc.Initialize();

			// ルートシグネチャ
			if(m_rootSign != nullptr) stateDesc.SetRootSignature(*m_rootSign);
			// 各シェーダー
			if(m_vertexShader.IsValid()) stateDesc.SetVertexShader(m_vertexShader.GetResource()->GetDX12Shader());
			if(m_pixelShader.IsValid()) stateDesc.SetPixelShader(m_pixelShader.GetResource()->GetDX12Shader());

			// 頂点レイアウト
			const ng::DX12VertexLayout& layout = ng::DX12GetVertexLayout(data.vertexLayout);
			stateDesc.InputLayout = {layout.descs, layout.descNum};

			// 取得に失敗した場合は新規作成し追加
			if(CGraphicModule::CreateAndAddPipelineState(data.plStateName, stateDesc)) {
				if(!CGraphicModule::GetPipelineState(data.plStateName, m_plState)) {
					NG_ERRLOG("Material", "DX12パイプラインステートの取得に失敗しました. name:%s", data.plStateName);
					result = false;
				}
			}
			else {
				NG_ERRLOG("Material", "DX12パイプラインステートの生成に失敗しました. name:%s", data.plStateName);
				result = false;
			}
		}
		// シェーダーエフェクト生成
		if(!CGraphicModule::CreateShaderEffect(data.shEffName, m_shEff)) {
			NG_ERRLOG("Material", "シェーダーエフェクトの生成に失敗しました. name:%s", data.shEffName);
			result = false;
		}

		return result;
	}

	void CMaterial::Destroy()
	{
		m_diffuseMap.Release();
		m_vertexShader.Release();
		m_pixelShader.Release();
	}

	bool CMaterial::_loadResource(const char* filePath, const void* pBuildParam, ng::IResourceHandle& handle)
	{
		if(!CResourceModule::LoadResource(
			filePath,
			eResourceMemoryType::FIXED,
			pBuildParam,
			handle
			)) {
			NG_ERRLOG("Material", "リソースの読み込みに失敗しました. filePath:%s", filePath);
			return false;
		}

		return true;
	}

	bool CMaterial::_loadShaderResource(const ShaderData& shaderData, ng::IResourceHandle& handle)
	{
		CShader::BuildParam buildParam(shaderData.entryPoint, shaderData.target);
		return _loadResource(shaderData.filePath, &buildParam, handle);
	}

}	// namespace app
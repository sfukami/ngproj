﻿/*!
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
		result &= _findRootSignature(data.rootSignatureName);
		// DX12パイプラインステート取得
		result &= _findPipelineState(data.pipelineStateName, data.vertexLayout);
		// シェーダーエフェクト生成
		result &= _createShaderEffect(data.shaderEffectName);

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

	bool CMaterial::_findRootSignature(const char* name)
	{
		if(!CGraphicModule::GetRootSignature(name, m_rootSignature)) {
			NG_ERRLOG("Material", "DX12ルートシグネチャの取得に失敗しました. name:%s", name);
			return false;
		}

		return true;
	}

	bool CMaterial::_findPipelineState(const char* name, ng::eVertexLayout vertexLayout)
	{
		// DX12パイプラインステート取得
		if(!CGraphicModule::GetPipelineState(name, m_pipelineState)) {
			ng::CDX12PipelineStateDesc stateDesc;
			stateDesc.Initialize();

			// ルートシグネチャ
			if(m_rootSignature != nullptr) stateDesc.SetRootSignature(*m_rootSignature);
			// 各シェーダー
			if(m_vertexShader.IsValid()) stateDesc.SetVertexShader(m_vertexShader.GetResource()->GetDX12Shader());
			if(m_pixelShader.IsValid()) stateDesc.SetPixelShader(m_pixelShader.GetResource()->GetDX12Shader());

			// 頂点レイアウト
			{
				const ng::DX12VertexLayout& layout = ng::DX12GetVertexLayout(vertexLayout);
				stateDesc.InputLayout = {layout.descs, layout.descNum};
			}

			// DX12パイプラインステートを生成&追加
			if(CGraphicModule::CreateAndAddPipelineState(name, stateDesc)) {
				if(!CGraphicModule::GetPipelineState(name, m_pipelineState)) {
					NG_ERRLOG("Material", "DX12パイプラインステートの取得に失敗しました. name:%s", name);
					return false;
				}
			}
			else {
				NG_ERRLOG("Material", "DX12パイプラインステートの生成に失敗しました. name:%s", name);
				return false;
			}
		}

		return true;
	}

	bool CMaterial::_createShaderEffect(const char* name)
	{
		if(!CGraphicModule::CreateShaderEffect(name, m_shaderEffect)) {
			NG_ERRLOG("Material", "シェーダーエフェクトの生成に失敗しました. name:%s", name);
			return false;
		}

		return true;
	}

}	// namespace app
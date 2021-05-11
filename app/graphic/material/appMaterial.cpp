/*!
* @file		appMaterial.cpp
* @brief	マテリアル
* @date		2020-07-22
* @author	s.fukami
*/

#include "ngLibGraphic/graphic/dx12/ngDX12Util.h"
#include "ngLibGraphic/graphic/dx12/command/list/ngDX12CommandList.h"
#include "ngLibGraphic/graphic/dx12/pipeline/ngDX12PipelineStateDesc.h"
#include "ngLibGraphic/graphic/dx12/polygon/ngDX12VertexLayout.h"
#include "appMaterial.h"
#include "appMaterialData.h"
#include "../shader/effect/appShaderEffect.h"
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
	
	bool CMaterial::Create(const CMaterialData& data)
	{
		bool result = true;

		const MaterialFormat& matFormat = data.GetFormat();

		// ディフューズマップ読み込み
		result &= _loadResource(matFormat.diffuseMap.filePath, nullptr, m_diffuseMap);

		// 頂点シェーダー読み込み
		result &= _loadShaderResource(matFormat.vertexShader, m_vertexShader);
		// ピクセルシェーダー読み込み
		result &= _loadShaderResource(matFormat.pixelShader, m_pixelShader);

		// DX12ルートシグネチャ取得
		result &= _findRootSignature(matFormat.rootSignatureName);
		// DX12パイプラインステート生成
		result &= _createPipelineState(matFormat.pipelineStateName, matFormat.vertexLayout);

		// シェーダーエフェクト生成
		NG_STRCPY(m_shaderEffectName, matFormat.shaderEffectName);
		result &= _createShaderEffect(m_shaderEffectName);

		return result;
	}

	void CMaterial::Destroy()
	{
		m_diffuseMap.Release();
		m_vertexShader.Release();
		m_pixelShader.Release();
	}

	void CMaterial::CopyMaterial(CMaterial& dst) const
	{
		dst.m_diffuseMap = m_diffuseMap;
		dst.m_vertexShader = m_vertexShader;
		dst.m_pixelShader = m_pixelShader;
		dst.m_rootSignature = m_rootSignature;
		dst.m_pipelineState = m_pipelineState;

		if(NG_STRLEN(m_shaderEffectName) > 0) {
			NG_STRCPY(dst.m_shaderEffectName, m_shaderEffectName);
			dst._createShaderEffect(m_shaderEffectName);
		}
	}

	void CMaterial::SetRootSignature(ng::CDX12CommandList& commandList)
	{
		if(m_rootSignature) {
			commandList.SetRootSignature(*m_rootSignature);
		}
	}

	void CMaterial::SetPipelineState(ng::CDX12CommandList& commandList)
	{
		if(m_pipelineState) {
			commandList.SetPipelineState(*m_pipelineState);
		}
	}

	ng::CWeakPtr<CTexture> CMaterial::GetDiffuseMap() const
	{
		if(!m_diffuseMap.IsValid()) {
			return ng::CWeakPtr<CTexture>();
		}

		return m_diffuseMap.GetResource();
	}

	ng::CWeakPtr<CShaderEffect> CMaterial::GetShaderEffect() const
	{
		return m_shaderEffect;
	}

	ng::CWeakPtr<ng::CDX12RootSignature> CMaterial::GetRootSignature() const
	{
		return m_rootSignature;
	}

	ng::CWeakPtr<ng::CDX12PipelineState> CMaterial::GetPipelineState() const
	{
		return m_pipelineState;
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

	bool CMaterial::_loadShaderResource(const ShaderFormat& shaderFormat, ng::IResourceHandle& handle)
	{
		CShader::BuildParam buildParam(shaderFormat.entryPoint, shaderFormat.target);
		return _loadResource(shaderFormat.filePath, &buildParam, handle);
	}

	bool CMaterial::_findRootSignature(const char* name)
	{
		if(!CGraphicModule::GetRootSignature(name, m_rootSignature)) {
			NG_ERRLOG("Material", "DX12ルートシグネチャの取得に失敗しました. name:%s", name);
			return false;
		}

		return true;
	}

	bool CMaterial::_createPipelineState(const char* name, ng::eVertexLayout vertexLayout)
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
		// シェーダーエフェクトのオブジェクトを生成
		if(!CGraphicModule::CreateShaderEffect(name, m_shaderEffect)) {
			NG_ERRLOG("Material", "シェーダーエフェクトの生成に失敗しました. name:%s", name);
			return false;
		}

		// シェーダーエフェクトを生成
		ng::CDX12Device* pDX12Device = ng::DX12Util::GetDevice();
		NG_ASSERT_NOT_NULL(pDX12Device);

		if(!m_shaderEffect->Create(*pDX12Device, *this)) {
			NG_ERRLOG("Material", "シェーダーエフェクトの生成に失敗しました. name:%s", name);
			return false;
		}

		return true;
	}

}	// namespace app
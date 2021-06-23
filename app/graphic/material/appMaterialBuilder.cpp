/*!
* @file		appMaterialBuilder.cpp
* @brief	マテリアルビルダー
* @date		2021-06-14
* @author	s.fukami
*/

#include "ngLibGraphic/graphic/dx12/ngDX12Util.h"
#include "ngLibGraphic/graphic/dx12/pipeline/ngDX12PipelineStateDesc.h"
#include "appMaterial.h"
#include "appMaterialFormat.h"
#include "appMaterialBuilder.h"
#include "app/graphic//shader/effect/appShaderEffect.h"
#include "app/graphic/appGraphicModule.h"

namespace app
{
	CMaterialBuilder::CMaterialBuilder()
	{
	}
	CMaterialBuilder::~CMaterialBuilder()
	{
	}

	bool CMaterialBuilder::Build(const MaterialFormat& format, CMaterial* pDst) const
	{
		ng::CResourceHandle<CTexture> diffuseMap;
		ng::CResourceHandle<CShader> vertexShader;
		ng::CResourceHandle<CShader> pixelShader;
		ng::CWeakPtr<ng::CDX12RootSignature> rootSignature;

		// ディフューズマップ読み込み
		if(!_loadTextureResource(format.name, format.diffuseMap, diffuseMap)) return false;
		// 頂点シェーダー読み込み
		if(!_loadShaderResource(format.name, format.vertexShader, vertexShader)) return false;
		// ピクセルシェーダー読み込み
		if(!_loadShaderResource(format.name, format.pixelShader, pixelShader)) return false;
		// DX12ルートシグネチャ取得
		if(!_findRootSignature(format.rootSignatureName, rootSignature)) return false;

		// DX12パイプラインステート生成
		ng::CWeakPtr<ng::CDX12PipelineState> pipelineState;
		{
			ng::CDX12PipelineStateDesc stateDesc;
			stateDesc.Initialize();
			// ルートシグネチャ
			if(rootSignature) stateDesc.SetRootSignature(*rootSignature);
			// 各シェーダー
			if(vertexShader.IsValid()) stateDesc.SetVertexShader(vertexShader.GetResource()->GetDX12Shader());
			if(pixelShader.IsValid()) stateDesc.SetPixelShader(pixelShader.GetResource()->GetDX12Shader());
			// 頂点レイアウト
			{
				const ng::DX12VertexLayout& layout = ng::DX12GetVertexLayout(format.vertexLayout);
				stateDesc.InputLayout = {layout.descs, layout.descNum};
			}
			if(!_createPipelineState(format.pipelineStateName, stateDesc, pipelineState)) return false;
		}

		pDst->SetDiffuseMap(diffuseMap);
		pDst->SetVertexShader(vertexShader);
		pDst->SetPixelShader(pixelShader);
		pDst->SetRootSignature(rootSignature);
		pDst->SetPipelineState(pipelineState);

		// シェーダーエフェクト生成
		ng::CSharedPtr<CShaderEffect> shaderEffect;
		if(!_createShaderEffect(format.shaderEffectName, shaderEffect)) return false;
		pDst->SetShaderEffect(shaderEffect);

		// マテリアル生成
		ng::CDX12Device* pDX12Device = ng::DX12Util::GetDevice();
		NG_ASSERT_NOT_NULL(pDX12Device);
		if(!pDst->Create(*pDX12Device)) return false;

		return true;
	}

	bool CMaterialBuilder::_loadTextureResource(const char* matName, const TextureFormat& format, ng::IResourceHandle& handle) const
	{
		bool result = false;

		if(format.IsValidBinary()) {
			result = CResourceModule::LoadResourceFromMemory<CTexture>(
				format.pBinary, format.size, matName, format.name, format.resMemType, nullptr, handle
				);
		}
		else if(format.IsValidFilePath()) {
			result = CResourceModule::LoadResourceFromFile<CTexture>(
				format.filePath, format.resMemType, handle
				);
		}
		else {
			// テクスチャ無しと見なす
			return true;
		}

		if(!result) {
			NG_ERRLOG("MaterialBuilder", "テクスチャリソースの読み込みに失敗しました. name:%s", format.name);
		}

		return result;
	}

	bool CMaterialBuilder::_loadShaderResource(const char* matName, const ShaderFormat& format, ng::IResourceHandle& handle) const
	{
		bool result = true;
		CShader::BuildParam buildParam(format.entryPoint, format.target);

		if(format.IsValidBinary()) {
			result = CResourceModule::LoadResourceFromMemory<CShader>(
				format.pBinary, format.size, matName, format.entryPoint, format.resMemType, &buildParam, handle
				);
		}
		else if(format.IsValidFilePath()) {
			result = CResourceModule::LoadResourceFromFile<CShader>(
				format.filePath, format.entryPoint, format.resMemType, &buildParam, handle
				);
		}
		else {
			return false;
		}

		if(!result) {
			NG_ERRLOG("MaterialBuilder", "シェーダーリソースの読み込みに失敗しました. filePath:%s, entryPoint:%s", format.filePath, format.entryPoint);
		}

		return result;
	}

	bool CMaterialBuilder::_findRootSignature(const char* name, ng::CWeakPtr<ng::CDX12RootSignature>& dstPtr) const
	{
		if(!CGraphicModule::GetRootSignature(name, dstPtr)) {
			NG_ERRLOG("MaterialBuilder", "DX12ルートシグネチャの取得に失敗しました. name:%s", name);
			return false;
		}

		return true;
	}

	bool CMaterialBuilder::_createPipelineState(
		const char* name, const ng::CDX12PipelineStateDesc& desc, ng::CWeakPtr<ng::CDX12PipelineState>& dstPtr
		) const
	{
		// DX12パイプラインステート取得
		if(!CGraphicModule::GetPipelineState(name, dstPtr)) {
			// DX12パイプラインステートを生成&追加
			if(CGraphicModule::CreateAndAddPipelineState(name, desc)) {
				if(!CGraphicModule::GetPipelineState(name, dstPtr)) {
					NG_ERRLOG("MaterialBuilder", "DX12パイプラインステートの取得に失敗しました. name:%s", name);
					return false;
				}
			}
			else {
				NG_ERRLOG("MaterialBuilder", "DX12パイプラインステートの生成に失敗しました. name:%s", name);
				return false;
			}
		}

		return true;
	}

	bool CMaterialBuilder::_createShaderEffect(const char* name, ng::CSharedPtr<CShaderEffect>& dstPtr) const
	{
		// シェーダーエフェクトのオブジェクトを生成
		if(!CGraphicModule::CreateShaderEffect(name, dstPtr)) {
			NG_ERRLOG("MaterialBuilder", "シェーダーエフェクトオブジェクトの生成に失敗しました. name:%s", name);
			return false;
		}

		// シェーダーエフェクトを生成
		ng::CDX12Device* pDX12Device = ng::DX12Util::GetDevice();
		NG_ASSERT_NOT_NULL(pDX12Device);

		if(!dstPtr->Create(*pDX12Device)) {
			NG_ERRLOG("MaterialBuilder", "シェーダーエフェクトの生成に失敗しました. name:%s", name);
			return false;
		}

		return true;
	}

}	// namespace app
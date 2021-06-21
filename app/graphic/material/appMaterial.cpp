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
#include "../shader/effect/appShaderEffect.h"
#include "../appGraphicModule.h"
#include "app/resource/appResourceModule.h"

namespace app
{
	CMaterial::CMaterial()
	{
	}
	CMaterial::~CMaterial()
	{
		Destroy();
	}

	bool CMaterial::Create(ng::CDX12Device& device)
	{
		NG_ERRCODE err = NG_ERRCODE_DEFAULT;

		// DX12ディスクリプタヒープ生成
		if(NG_FAILED(err = m_descHeap.Create(
			device,
			D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
			1,
			D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE
			))) {
			NG_ERRLOG_C("Material", err, "DX12ディスクリプタヒープの生成に失敗しました.");
			return false;
		}

		// 各テクスチャのリソースビュー生成
		if(m_diffuseMap.IsValid()) {
			m_diffuseMap.GetResource()->GetTexture().CreateResourceView(
				device,
				m_descHeap, 0
				);
		}

		return true;
	}
	
	void CMaterial::Destroy()
	{
		m_descHeap.Destroy();
		m_diffuseMap.Release();
		m_vertexShader.Release();
		m_pixelShader.Release();
	}
	
	void CMaterial::BindRootSignature(ng::CDX12CommandList& commandList)
	{
		if(m_rootSignature) {
			commandList.SetRootSignature(*m_rootSignature);
		}
	}

	void CMaterial::BindPipelineState(ng::CDX12CommandList& commandList)
	{
		if(m_pipelineState) {
			commandList.SetPipelineState(*m_pipelineState);
		}
	}

	void CMaterial::BindResource(ng::CDX12CommandList& commandList)
	{
		if(m_descHeap.IsValid()) {
			// ディスクリプタヒープ設定
			commandList.SetDescriptorHeap(m_descHeap);
			// テクスチャのディスクリプタテーブルを設定
			commandList.SetGraphicsRootDescriptorTable(1, m_descHeap.GetGPUDescriptorHandle(0));
		}
	}

	ng::CWeakPtr<CTexture> CMaterial::GetDiffuseMap() const
	{
		if(!m_diffuseMap.IsValid()) {
			return ng::CWeakPtr<CTexture>();
		}

		return m_diffuseMap.GetResource();
	}

	ng::CWeakPtr<ng::CDX12RootSignature> CMaterial::GetRootSignature() const
	{
		return m_rootSignature;
	}

	ng::CWeakPtr<ng::CDX12PipelineState> CMaterial::GetPipelineState() const
	{
		return m_pipelineState;
	}

	ng::CWeakPtr<CShaderEffect> CMaterial::GetShaderEffect() const
	{
		return m_shaderEffect;
	}

	void CMaterial::SetDiffuseMap(const ng::CResourceHandle<CTexture>& handle)
	{
		m_diffuseMap = handle;
	}
	void CMaterial::SetVertexShader(const ng::CResourceHandle<CShader>& handle)
	{
		m_vertexShader = handle;
	}
	void CMaterial::SetPixelShader(const ng::CResourceHandle<CShader>& handle)
	{
		m_pixelShader = handle;
	}
	void CMaterial::SetRootSignature(const ng::CWeakPtr<ng::CDX12RootSignature>& ptr)
	{
		m_rootSignature = ptr;
	}
	void CMaterial::SetPipelineState(const ng::CWeakPtr<ng::CDX12PipelineState>& ptr)
	{
		m_pipelineState = ptr;
	}
	void CMaterial::SetShaderEffect(const ng::CSharedPtr<CShaderEffect>& ptr)
	{
		m_shaderEffect = ptr;
	}

}	// namespace app
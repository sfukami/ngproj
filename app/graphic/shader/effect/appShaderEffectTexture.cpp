/*!
* @file		appShaderEffectTexture.cpp
* @brief	シェーダーエフェクト テクスチャ描画
* @date		2020-07-28
* @author	s.fukami
*/

#include "ngLibGraphic/graphic/dx12/command/list/ngDX12CommandList.h"
#include "appShaderEffectTexture.h"
#include "app/graphic/material/appMaterial.h"

namespace app
{
	CShaderEffectTexture::CShaderEffectTexture()
	{
	}
	CShaderEffectTexture::~CShaderEffectTexture()
	{
		Destroy();
	}

	NG_ERRCODE CShaderEffectTexture::Create(
		ng::CDX12Device& device,
		CMaterial& material
		)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// DX12ディスクリプタヒープ生成
		if(NG_FAILED(ret = m_descHeap.Create(
			device,
			D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
			2,
			D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE
			))) {
			NG_ERRLOG_C("ShaderEffectTexture", ret, "DX12ディスクリプタヒープの生成に失敗しました.");
			return ret;
		}

		// DX12コンスタントバッファ生成
		if(NG_FAILED(ret = m_cb.Create(
			device,
			nullptr, sizeof(ShaderParam)
			))) {
			NG_ERRLOG_C("ShaderEffectTexture", ret, "DX12コンスタントバッファの生成に失敗しました.");
			return ret;
		}

		// コンスタントバッファのリソースビュー生成
		m_cb.CreateResourceView(
			device, m_descHeap, 0
			);

		// ディフューズマップのリソースビューを生成
		{
			ng::CWeakPtr<CTexture> diffuseMap;
			if(material.GetDiffuseMap(diffuseMap)) {
				diffuseMap->GetTexture().CreateResourceView(
					device,
					m_descHeap, 1
					);
			}
		}

		return ret;
	}

	void CShaderEffectTexture::Destroy()
	{
		m_cb.Destroy();
		m_descHeap.Destroy();
	}

	void CShaderEffectTexture::UpdateConstantBuffer()
	{
		m_cb.CopyData(&m_shPrm, sizeof(ShaderParam));
	}

	void CShaderEffectTexture::BindResource(ng::CDX12CommandList& commandList)
	{
		// ディスクリプタヒープ設定
		commandList.SetDescriptorHeap(m_descHeap);
		// コンスタントバッファのディスクリプタテーブルを設定
		commandList.SetGraphicsRootDescriptorTable(0, m_descHeap.GetGPUDescriptorHandle(0));
		// テクスチャのディスクリプタテーブルを設定
		commandList.SetGraphicsRootDescriptorTable(1, m_descHeap.GetGPUDescriptorHandle(1));
	}

	void CShaderEffectTexture::SetWVPMatrix(const ng::Matrix4& mat)
	{
		m_shPrm.matWVP = mat;
	}

}	// namespace app
﻿/*!
* @file		appShaderEffectSprite.h
* @brief	シェーダーエフェクト スプライト描画
* @date		2020-07-28
* @author	s.fukami
*/

#include "ngLibGraphic/graphic/dx12/command/list/ngDX12CommandList.h"
#include "appShaderEffectSprite.h"
#include "app/graphic/material/appMaterial.h"

namespace app
{
	CShaderEffectSprite::CShaderEffectSprite()
	{
	}
	CShaderEffectSprite::~CShaderEffectSprite()
	{
		Destroy();
	}

	bool CShaderEffectSprite::Create(
		ng::CDX12Device& device,
		CMaterial& material
		)
	{
		NG_ERRCODE err = NG_ERRCODE_DEFAULT;

		// DX12ディスクリプタヒープ生成
		if(NG_FAILED(err = m_descHeap.Create(
			device,
			D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
			2,
			D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE
			))) {
			NG_ERRLOG_C("ShaderEffectSprite", err, "DX12ディスクリプタヒープの生成に失敗しました.");
			return false;
		}

		// DX12コンスタントバッファ生成
		if(NG_FAILED(err = m_cb.Create(
			device,
			nullptr, sizeof(ShaderParam)
			))) {
			NG_ERRLOG_C("ShaderEffectSprite", err, "DX12コンスタントバッファの生成に失敗しました.");
			return false;
		}

		// コンスタントバッファのリソースビュー生成
		m_cb.CreateResourceView(
			device, m_descHeap, 0
			);

		// ディフューズマップのリソースビューを生成
		{
			ng::CWeakPtr<CTexture> diffuseMap = material.GetDiffuseMap();
			if(diffuseMap) {
				diffuseMap->GetTexture().CreateResourceView(
					device,
					m_descHeap, 1
					);
			}
		}

		return true;
	}

	void CShaderEffectSprite::Destroy()
	{
		m_cb.Destroy();
		m_descHeap.Destroy();
	}

	void CShaderEffectSprite::SetShaderParam(const ShaderParam& param)
	{
		m_shPrm = param;
	}

	void CShaderEffectSprite::UpdateConstantBuffer()
	{
		m_cb.CopyData(&m_shPrm, sizeof(ShaderParam));
	}

	void CShaderEffectSprite::BindResource(ng::CDX12CommandList& commandList)
	{
		// ディスクリプタヒープ設定
		commandList.SetDescriptorHeap(m_descHeap);
		// コンスタントバッファのディスクリプタテーブルを設定
		commandList.SetGraphicsRootDescriptorTable(0, m_descHeap.GetGPUDescriptorHandle(0));
		// テクスチャのディスクリプタテーブルを設定
		commandList.SetGraphicsRootDescriptorTable(1, m_descHeap.GetGPUDescriptorHandle(1));
	}

}	// namespace app
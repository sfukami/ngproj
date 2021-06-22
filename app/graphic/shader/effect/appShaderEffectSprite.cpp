/*!
* @file		appShaderEffectSprite.h
* @brief	シェーダーエフェクト スプライト描画
* @date		2020-07-28
* @author	s.fukami
*/

#include "ngLibGraphic/graphic/dx12/command/list/ngDX12CommandList.h"
#include "appShaderEffectSprite.h"

namespace app
{
	CShaderEffectSprite::CShaderEffectSprite()
	{
	}
	CShaderEffectSprite::~CShaderEffectSprite()
	{
		Destroy();
	}

	bool CShaderEffectSprite::Create(ng::CDX12Device& device)
	{
		NG_ERRCODE err = NG_ERRCODE_DEFAULT;

		// DX12ディスクリプタヒープ生成
		if(NG_FAILED(err = m_descHeap.Create(
			device,
			D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
			1,
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

		return true;
	}

	void CShaderEffectSprite::Destroy()
	{
		m_cb.Destroy();
		m_descHeap.Destroy();
	}

	void CShaderEffectSprite::SetParameter(const ShaderParam& param)
	{
		NG_MEMCPY(&m_param, &param, sizeof(param));
	}

	void CShaderEffectSprite::UpdateConstantBuffer()
	{
		m_cb.CopyData(&m_param, sizeof(ShaderParam));
	}

	void CShaderEffectSprite::BindResource(ng::CDX12CommandList& commandList)
	{
		if(m_descHeap.IsValid()) {
			// ディスクリプタヒープ設定
			commandList.SetDescriptorHeap(m_descHeap);
			// コンスタントバッファのディスクリプタテーブルを設定
			commandList.SetGraphicsRootDescriptorTable(0, m_descHeap.GetGPUDescriptorHandle(0));
		}
	}

}	// namespace app
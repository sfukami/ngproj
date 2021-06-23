/*!
* @file		appShaderEffectSpriteColor.cpp
* @brief	シェーダーエフェクト スプライト描画
* @date		2020-07-28
* @author	s.fukami
*/

#include "ngLibCore/color/ngColorCode.h"
#include "ngLibGraphic/graphic/dx12/command/list/ngDX12CommandList.h"
#include "appShaderEffectSpriteColor.h"

namespace app
{
	CShaderEffectSpriteColor::Param::Param()
		: color(ng::eColorCode::WHITE)
	{
	}

	CShaderEffectSpriteColor::CShaderEffectSpriteColor()
	{
	}
	CShaderEffectSpriteColor::~CShaderEffectSpriteColor()
	{
		Destroy();
	}

	bool CShaderEffectSpriteColor::Create(ng::CDX12Device& device)
	{
		NG_ERRCODE err = NG_ERRCODE_DEFAULT;

		// DX12ディスクリプタヒープ生成
		if(NG_FAILED(err = m_descHeap.Create(
			device,
			D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
			1,
			D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE
			))) {
			NG_ERRLOG_C("ShaderEffectSpriteColor", err, "DX12ディスクリプタヒープの生成に失敗しました.");
			return false;
		}

		// DX12コンスタントバッファ生成
		if(NG_FAILED(err = m_cb.Create(
			device,
			nullptr, sizeof(Param)
			))) {
			NG_ERRLOG_C("ShaderEffectSpriteColor", err, "DX12コンスタントバッファの生成に失敗しました.");
			return false;
		}

		// コンスタントバッファのリソースビュー生成
		m_cb.CreateResourceView(
			device, m_descHeap, 0
			);

		return true;
	}

	void CShaderEffectSpriteColor::Destroy()
	{
		m_cb.Destroy();
		m_descHeap.Destroy();
	}

	void CShaderEffectSpriteColor::SetParameter(const ShaderParam& param)
	{
		m_param.basicParam = param;
	}

	void CShaderEffectSpriteColor::SetColor(const ng::Color& color)
	{
		m_param.color = color;
	}

	void CShaderEffectSpriteColor::UpdateConstantBuffer()
	{
		m_cb.CopyData(&m_param, sizeof(Param));
	}

	void CShaderEffectSpriteColor::BindResource(ng::CDX12CommandList& commandList)
	{
		if(m_descHeap.IsValid()) {
			// ディスクリプタヒープ設定
			commandList.SetDescriptorHeap(m_descHeap);
			// コンスタントバッファのディスクリプタテーブルを設定
			commandList.SetGraphicsRootDescriptorTable(0, m_descHeap.GetGPUDescriptorHandle(0));
		}
	}

	const char* CShaderEffectSpriteColor::GetName()
	{
		return "sprite_color";
	}

}	// namespace app
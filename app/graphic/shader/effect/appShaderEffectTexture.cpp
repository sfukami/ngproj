/*!
* @file		appShaderEffectTexture.cpp
* @brief	シェーダーエフェクト テクスチャ描画
* @date		2020-07-28
* @author	s.fukami
*/

#include "appShaderEffectTexture.h"

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
		ng::CDX12DescriptorHeap& descHeap
		)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// コンスタントバッファ生成
		if(NG_FAILED(ret = m_cb.Create(
			device,
			nullptr, sizeof(ShaderParam)
			))) {
			return ret;
		}

		// リソースビュー生成
		m_cb.CreateResourceView(
			device, descHeap, 0
			);

		return ret;
	}

	void CShaderEffectTexture::Destroy()
	{
		m_cb.Destroy();
	}

	void CShaderEffectTexture::UpdateConstantBuffer()
	{
		m_cb.CopyData(&m_shPrm, sizeof(ShaderParam));
	}

	void CShaderEffectTexture::SetWVPMatrix(const ng::Matrix4& mat)
	{
		m_shPrm.matWVP = mat;
	}

}	// namespace app
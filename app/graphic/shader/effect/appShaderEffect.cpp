/*!
* @file		appShaderEffect.cpp
* @brief	シェーダーエフェクト 基底クラス
* @date		2020-07-28
* @author	s.fukami
*/

#include "appShaderEffect.h"

namespace app
{
	CShaderEffect::ShaderParam::ShaderParam()
	{
		ng::MatrixOp::Identity(wvpMat);
	}

	CShaderEffect::CShaderEffect()
	{
	}
	CShaderEffect::~CShaderEffect()
	{
	}

	bool CShaderEffect::Create(
		ng::CDX12Device& device,
		CMaterial& material
		)
	{
		return true;
	}

	void CShaderEffect::SetShaderParam(const ShaderParam& param)
	{
	}

	void CShaderEffect::UpdateConstantBuffer()
	{
	}

	void CShaderEffect::BindResource(ng::CDX12CommandList& commandList)
	{
	}

}	// namespace app
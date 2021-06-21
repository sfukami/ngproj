/*!
* @file		appShaderEffect.cpp
* @brief	シェーダーエフェクト 基底クラス
* @date		2020-07-28
* @author	s.fukami
*/

#include "appShaderEffect.h"

namespace app
{
	CShaderEffect::CShaderEffect()
	{
	}
	CShaderEffect::~CShaderEffect()
	{
	}

	bool CShaderEffect::Create(ng::CDX12Device& device)
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
﻿/*!
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

	void CShaderEffect::UpdateConstantBuffer()
	{
	}

	void CShaderEffect::BindResource(ng::CDX12CommandList& commandList)
	{
	}

}	// namespace app
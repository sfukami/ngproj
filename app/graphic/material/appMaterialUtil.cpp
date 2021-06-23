/*!
* @file		appMaterialUtil.cpp
* @brief	マテリアル ユーティリティ
* @date		2021-06-22
* @author	s.fukami
*/

#include "appMaterialUtil.h"
#include "appMaterialFormat.h"

namespace app
{
namespace MaterialUtil
{
	void GetMaterialFormatSprite(MaterialFormat* pDst)
	{
		NG_ASSERT_NOT_NULL(pDst);

		pDst->SetMaterialName("sprite");
		pDst->SetRootSignatureName("sprite");
		pDst->SetPipelineStateName("sprite");
		pDst->SetShaderEffectName("sprite");
		pDst->vertexLayout = ng::eVertexLayout::SPRITE;
		// vs
		pDst->vertexShader.SetFilePath("../resource/shader/sprite_vs.hlsl");
		pDst->vertexShader.SetEntryPoint("VSMain");
		pDst->vertexShader.SetTarget("vs_5_0");
		// ps
		pDst->pixelShader.SetFilePath("../resource/shader/sprite_ps.hlsl");
		pDst->pixelShader.SetEntryPoint("PSMain");
		pDst->pixelShader.SetTarget("ps_5_0");
	}

	void GetMaterialFormatModel(MaterialFormat* pDst)
	{
		NG_ASSERT_NOT_NULL(pDst);

		pDst->SetMaterialName("model");
		pDst->SetRootSignatureName("model");
		pDst->SetPipelineStateName("model");
		pDst->SetShaderEffectName("model");
		pDst->vertexLayout = ng::eVertexLayout::SKELETAL;
		// vs
		pDst->vertexShader.SetFilePath("../resource/shader/model_test.hlsl");
		pDst->vertexShader.SetEntryPoint("VSMain");
		pDst->vertexShader.SetTarget("vs_5_0");
		// ps
		pDst->pixelShader.SetFilePath("../resource/shader/model_test.hlsl");
		pDst->pixelShader.SetEntryPoint("PSMain");
		pDst->pixelShader.SetTarget("ps_5_0");
	}

}	// namespace MaterialUtil
}	// namespace app
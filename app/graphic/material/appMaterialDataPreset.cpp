/*!
* @file		appMaterialDataPreset.cpp
* @brief	マテリアルデータのプリセット
* @date		2021-05-11
* @author	s.fukami
*/

#include "ngLibGraphic/graphic/dx12/polygon/ngDX12VertexLayout.h"
#include "appMaterialDataPreset.h"
#include "appMaterialData.h"

namespace app
{
	//! 各マテリアルデータ
	static CMaterialData s_matDataSprite;

	bool _CheckInit(const CMaterialData& matData)
	{
		return (NG_STRLEN(matData.GetFormat().name) != 0);
	}

	const CMaterialData& GetMaterialDataPresetSprite()
	{
		CMaterialData& matData = s_matDataSprite;
		if(!_CheckInit(matData)) {
			matData.SetMaterialName("test");
			matData.SetRootSignatureName("sprite");
			matData.SetPipelineStateName("sprite");
			matData.SetShaderEffectName("sprite");
			matData.SetVertexLayout(ng::eVertexLayout::SPRITE);
			// diffuse
			matData.SetDiffuseMapFilePath("../resource/texture/test.bmp");
			// vs
			matData.SetVSFilePath("../resource/shader/sprite_vs.hlsl");
			matData.SetVSEntryPoint("VSMain");
			matData.SetVSTarget("vs_5_0");
			// ps
			matData.SetPSFilePath("../resource/shader/sprite_ps.hlsl");
			matData.SetPSEntryPoint("PSMain");
			matData.SetPSTarget("ps_5_0");
		}
		
		return s_matDataSprite;
	}

}	// namespace app
/*!
* @file		appSpriteRender.cpp
* @brief	スプライト描画
* @date		2020-07-19
* @author	s.fukami
*/

#include "appSpriteRender.h"
#include "app/graphic/material/appMaterialFormat.h"
#include "app/graphic/material/appMaterialBuilder.h"
#include "app/graphic/shader/effect/appShaderEffect.h"
#include "app/graphic/shader/effect/appShaderParam.h"
#include "../appRenderParam.h"
#include "../../appGraphicUtil.h"

namespace app
{
	CSpriteRender::CSpriteRender()
	{
	}
	CSpriteRender::~CSpriteRender()
	{
		Destroy();
	}

	bool CSpriteRender::Create(
		ng::u32 width
		, ng::u32 height
		, const char* imageFilePath
		, eResourceMemoryType resMemType
		)
	{
		ng::CDX12Device* pDX12Device = GraphicUtil::GetDX12Device();
		NG_ASSERT_NOT_NULL(pDX12Device);

		// DX12ポリゴン 矩形生成
		{
			NG_ERRCODE err = m_square.Create(*pDX12Device, (float)width, (float)height, true);
			if(NG_FAILED(err)) {
				NG_ERRLOG_C("Sprite", err, "DX12ポリゴン矩形の生成に失敗しました.");
				return false;
			}
		}

		// マテリアル生成
		{
			MaterialFormat format;
			_getMaterialFormat(&format);

			format.diffuseMap.SetFilePath(imageFilePath);
			format.diffuseMap.resMemType = resMemType;

			CMaterialBuilder builder;
			if(!builder.Build(format, &m_material)) {
				NG_ERRLOG("SpriteRender", "マテリアルの生成に失敗しました.");
				return false;
			}
		}

		return true;
	}

	void CSpriteRender::Destroy()
	{
		m_square.Destroy();
		m_material.Destroy();
	}

	bool CSpriteRender::IsEnable() const
	{
		return m_square.IsValid();
	}

	void CSpriteRender::_render(const RenderParam& param)
	{
		ng::CDX12CommandList* pCmdList = GraphicUtil::GetDX12CommandList(param.cmdListId);
		NG_ASSERT_NOT_NULL(pCmdList);

		// 各設定・リソースをコマンドリストへ設定
		m_material.BindRootSignature(*pCmdList);
		m_material.BindPipelineState(*pCmdList);

		auto shaderEffect = m_material.GetShaderEffect();
		if(shaderEffect) {
			ShaderParam shdPrm;
			ng::MatrixOp::Transpose(shdPrm.wvpMat, param.wvpMat);

			shaderEffect->SetShaderParam(shdPrm);
			shaderEffect->UpdateConstantBuffer();
			shaderEffect->BindResource(*pCmdList);
		}

		m_material.BindResource(*pCmdList);

		// 矩形描画
		m_square.Render(*pCmdList);
	}

	void CSpriteRender::_getMaterialFormat(MaterialFormat* pDst)
	{
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

}	// namespace app
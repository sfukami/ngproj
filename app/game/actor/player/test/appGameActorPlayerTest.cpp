/*!
* @file		appGameActorPlayerTest.cpp
* @brief	ゲームアクター プレイヤー テスト
* @date		2020-07-19
* @author	s.fukami
*/

#include "appGameActorPlayerTest.h"
#include "app/graphic/render/material/appMaterial.h"
#include "app/graphic/render/material/appMaterialFormat.h"

namespace app
{
	CGameActorPlayerTest::CGameActorPlayerTest()
	{
	}
	CGameActorPlayerTest::~CGameActorPlayerTest()
	{
	}

	bool CGameActorPlayerTest::Create()
	{
		// スプライト生成
		{
			CMaterial material;

			// マテリアル構築
			{
				MaterialData matData;

				matData.diffuseMap.SetFilePath("../resource/texture/test.bmp");
				{
					ShaderData& vs = matData.vertexShader;
					vs.SetFilePath("../resource/shader/texture_vs.hlsl");
					vs.SetEntryPoint("VSMain");
					vs.SetTarget("vs_5_0");
				}
				{
					ShaderData& ps = matData.pixelShader;
					ps.SetFilePath("../resource/shader/texture_ps.hlsl");
					ps.SetEntryPoint("PSMain");
					ps.SetTarget("ps_5_0");
				}

				if(!material.Build(matData)) {
					NG_ERRLOG("GameActorPlayerTest", "マテリアルの構築に失敗しました.");
					return false;
				}
			}

			// スプライト生成
			if(!m_sprite.Create(1, 1, &material)) {
				return false;
			}
		}

		return true;
	}
	
	void CGameActorPlayerTest::Destroy()
	{
		m_sprite.Destroy();
	}

	void CGameActorPlayerTest::_update(float deltaTime)
	{

	}

	void CGameActorPlayerTest::_render()
	{
		m_sprite.RegisterRender();
	}

}	// namespace app
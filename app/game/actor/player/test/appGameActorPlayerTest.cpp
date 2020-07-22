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
				const char* pFilePath = "../resource/texture/test.bmp";
				NG_STRCPY(matData.diffuseMap.filePath, pFilePath);

				if(!material.Build(matData)) {
					NG_ERRLOG("GameActorPlayerTest", "マテリアルの構築に失敗しました.");
					return false;
				}
			}

			if(!m_sprite.Create(
				1, 1, &material
				)) {
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
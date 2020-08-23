/*!
* @file		appGameActorPlayerTest.cpp
* @brief	ゲームアクター プレイヤー テスト
* @date		2020-07-19
* @author	s.fukami
*/

#include "appGameActorPlayerTest.h"
#include "app/graphic/material/appMaterial.h"
#include "app/graphic/material/appMaterialFormat.h"
//test
#include "ngLibGraphic/graphic/dx12/polygon/ngDX12VertexLayout.h"
#include "app/resource/appResourceModule.h"

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
			ng::CResourceHandle<CMaterial> handle;
			if(!CResourceModule::LoadResource("../resource/material/test.mat", eResourceMemoryType::FIXED, handle)) {
				return false;
			}

			// スプライト生成
			if(!m_sprite.Create(1, 1, &*handle.GetResource())) {
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
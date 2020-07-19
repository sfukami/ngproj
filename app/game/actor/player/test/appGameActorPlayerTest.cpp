/*!
* @file		appGameActorPlayerTest.cpp
* @brief	ゲームアクター プレイヤー テスト
* @date		2020-07-19
* @author	s.fukami
*/

#include "appGameActorPlayerTest.h"

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
		if(!m_sprite.Create(1, 1)) {
			return false;
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
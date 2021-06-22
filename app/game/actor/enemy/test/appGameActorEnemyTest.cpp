/*!
* @file		appGameActorEnemyTest.cpp
* @brief	ゲームアクター 敵 テスト
* @date		2020-08-28
* @author	s.fukami
*/

#include "appGameActorEnemyTest.h"
#include "app/resource/appResourceModule.h"
#include "app/input/appInputModule.h"

namespace app
{
	CGameActorEnemyTest::CGameActorEnemyTest()
		: m_stateMachine(this, State::DEFAULT)
	{
	}
	CGameActorEnemyTest::~CGameActorEnemyTest()
	{
	}

	bool CGameActorEnemyTest::Create()
	{
		// スプライト生成
		if(!m_sprite.Create(
			1, 1
			, "../resource/texture/test.bmp"
			, eResourceMemoryType::SCENE
			)) {
			return false;
		}

		// 親トランスフォーム設定
		CTransform& transform = m_sprite.GetTransform();
		transform.SetParent(&GetTransform());

		// ステート
		m_stateMachine.SetState(State::DEFAULT, &CGameActorEnemyTest::_state_default);

		return true;
	}
	
	void CGameActorEnemyTest::Destroy()
	{
		m_sprite.Destroy();
	}

	void CGameActorEnemyTest::_update(float deltaTime)
	{
		m_stateMachine.Execute(deltaTime);
	}

	void CGameActorEnemyTest::_render()
	{
		m_sprite.RegisterRender();
	}

	void CGameActorEnemyTest::_state_default(float deltaTime)
	{
	}

}	// namespace app
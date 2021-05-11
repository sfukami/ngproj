/*!
* @file		appGameActorPlayerBulletTest.cpp
* @brief	ゲームアクター プレイヤーの弾 テスト
* @date		2020-08-26
* @author	s.fukami
*/

#include "appGameActorPlayerBulletTest.h"
#include "app/resource/appResourceModule.h"

namespace app
{
	CGameActorPlayerBulletTest::CGameActorPlayerBulletTest()
		: m_stateMachine(this, State::DEFAULT)
	{
	}
	CGameActorPlayerBulletTest::~CGameActorPlayerBulletTest()
	{
	}

	bool CGameActorPlayerBulletTest::Create()
	{
		// スプライト生成
		if(!m_sprite.Create(1, 1)) {
			return false;
		}

		// 親トランスフォーム設定
		CTransform& transform = m_sprite.GetTransform();
		transform.SetParent(&GetTransform());

		// スケーリング
		ng::Vector3 scale = transform.GetScale();
		scale.x = scale.y = 0.5f;
		transform.SetScale(scale);

		// ステート
		m_stateMachine.SetState(State::DEFAULT, &CGameActorPlayerBulletTest::_state_default);

		return true;
	}
	
	void CGameActorPlayerBulletTest::Destroy()
	{
		m_sprite.Destroy();
	}

	bool CGameActorPlayerBulletTest::CheckDelete() const
	{
		//test
		const ng::Vector3 position = GetTransform().GetPosition();
		if(position.y > 1.5f) {
			return true;
		}

		return false;
	}

	void CGameActorPlayerBulletTest::_update(float deltaTime)
	{
		m_stateMachine.Execute(deltaTime);
	}

	void CGameActorPlayerBulletTest::_render()
	{
		m_sprite.RegisterRender();
	}

	void CGameActorPlayerBulletTest::_state_default(float deltaTime)
	{
		CTransform& transform = GetTransform();

		// 移動
		{
			ng::Vector3 position = transform.GetPosition();

			position.y += 0.1f;

			transform.SetPosition(position);
		}
		// 回転
		{
			ng::Quaternion rotation = transform.GetRotation();

			ng::Vector3 angle;
			ng::QuaternionOp::ToEulerAngle(angle, rotation);

			angle.z -= 1.f;

			ng::QuaternionOp::FromEulerAngle(rotation, angle);
			transform.SetRotation(rotation);
		}
	}

}	// namespace app
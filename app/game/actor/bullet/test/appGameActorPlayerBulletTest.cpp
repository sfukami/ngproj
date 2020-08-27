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
		{
			ng::CResourceHandle<CMaterial> handle;
			if(!CResourceModule::LoadResource("../resource/material/test.mat", eResourceMemoryType::FIXED, handle)) {
				return false;
			}

			// スプライト生成
			if(!m_sprite.Create(1, 1, &*handle.GetResource())) {
				return false;
			}

			// 親トランスフォーム設定
			CTransform& transform = m_sprite.GetTransform();
			transform.SetParent(&m_transform);
		}

		// ステート
		{
			m_stateMachine.SetState(State::DEFAULT, &CGameActorPlayerBulletTest::_state_default);
		}

		return true;
	}
	
	void CGameActorPlayerBulletTest::Destroy()
	{
		m_sprite.Destroy();
	}

	bool CGameActorPlayerBulletTest::CheckDelete() const
	{
		//test
		const ng::Vector3 position = m_transform.GetPosition();
		if(position.y > 1.5f) {
			return true;
		}

		return false;
	}

	/*! トランスフォーム取得 */
	CTransform& CGameActorPlayerBulletTest::GetTransform()
	{
		return m_transform;
	}
	const CTransform& CGameActorPlayerBulletTest::GetTransform() const
	{
		return m_transform;
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
		// プレイヤー
		// 移動
		{
			ng::Vector3 position = m_transform.GetPosition();

			position.y += 0.1f;

			m_transform.SetPosition(position);
		}
		// 回転
		{
			ng::Quaternion rotation = m_transform.GetRotation();

			ng::Vector3 angle;
			ng::QuaternionOp::ToEulerAngle(angle, rotation);

			angle.z -= 1.f;

			ng::QuaternionOp::FromEulerAngle(rotation, angle);
			m_transform.SetRotation(rotation);
		}
	}

}	// namespace app
﻿/*!
* @file		appGameActorPlayerTest.cpp
* @brief	ゲームアクター プレイヤー テスト
* @date		2020-07-19
* @author	s.fukami
*/

#include "appGameActorPlayerTest.h"
#include "app/resource/appResourceModule.h"
#include "app/input/appInputModule.h"
#include "app/game/actor/bullet/test/appGameActorPlayerBulletTest.h"
#include "app/game/actor/appGameActorMacro.h"

namespace app
{
	CGameActorPlayerTest::CGameActorPlayerTest()
		: m_stateMachine(this, State::DEFAULT)
	{
	}
	CGameActorPlayerTest::~CGameActorPlayerTest()
	{
	}

	bool CGameActorPlayerTest::Create()
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
		m_stateMachine.SetState(State::DEFAULT, &CGameActorPlayerTest::_state_default);

		return true;
	}
	
	void CGameActorPlayerTest::Destroy()
	{
		m_sprite.Destroy();
	}

	void CGameActorPlayerTest::_update(float deltaTime)
	{
		m_stateMachine.Execute(deltaTime);

		// スプライト
		{
			CTransform& transform = m_sprite.GetTransform();

			// 移動
			/*
			{
				ng::Vector3 position = transform.GetPosition();

				position.x = 1.f;

				transform.SetPosition(position);
			}
			*/
			// 回転
			/*
			{
				ng::Quaternion rotation = transform.GetRotation();

				ng::Vector3 angle;
				ng::QuaternionOp::ToEulerAngle(angle, rotation);

				angle.z += 1.f;

				ng::QuaternionOp::FromEulerAngle(rotation, angle);

				transform.SetRotation(rotation);
			}
			*/
		}
	}

	void CGameActorPlayerTest::_render()
	{
		m_sprite.RegisterRender();
	}

	void CGameActorPlayerTest::_state_default(float deltaTime)
	{
		CTransform& transform = GetTransform();
		// プレイヤー
		// 移動
		{
			ng::Vector3 position = transform.GetPosition();

			if(CInputModule::CheckKeyboardInput(ng::eKeyCode::LEFT, ng::eInputState::HELD)) {
				position.x -= 0.1f;
			} else if(CInputModule::CheckKeyboardInput(ng::eKeyCode::RIGHT, ng::eInputState::HELD)) {
				position.x += 0.1f;
			} else if(CInputModule::CheckKeyboardInput(ng::eKeyCode::UP, ng::eInputState::HELD)) {
				position.y += 0.1f;
			} else if(CInputModule::CheckKeyboardInput(ng::eKeyCode::DOWN, ng::eInputState::HELD)) {
				position.y -= 0.1f;
			}

			transform.SetPosition(position);
		}
		// 回転
		{
			ng::Quaternion rotation = transform.GetRotation();

			ng::Vector3 angle;
			ng::QuaternionOp::ToEulerAngle(angle, rotation);

			if(CInputModule::CheckKeyboardInput(ng::eKeyCode::R, ng::eInputState::HELD)) {
				angle.z -= 1.f;
			} else if(CInputModule::CheckKeyboardInput(ng::eKeyCode::Q, ng::eInputState::HELD)) {
				angle.z += 1.f;
			}

			ng::QuaternionOp::FromEulerAngle(rotation, angle);
			transform.SetRotation(rotation);
		}
		// スケーリング
		{
			ng::Vector3 scale = transform.GetScale();

			if(CInputModule::CheckKeyboardInput(ng::eKeyCode::J, ng::eInputState::HELD)) {
				scale.x -= 0.1f;
			} else if(CInputModule::CheckKeyboardInput(ng::eKeyCode::L, ng::eInputState::HELD)) {
				scale.x += 0.1f;
			} else if(CInputModule::CheckKeyboardInput(ng::eKeyCode::I, ng::eInputState::HELD)) {
				scale.y += 0.1f;
			} else if(CInputModule::CheckKeyboardInput(ng::eKeyCode::K, ng::eInputState::HELD)) {
				scale.y -= 0.1f;
			}

			transform.SetScale(scale);
		}

		// 弾生成
		if(CInputModule::CheckKeyboardInput(ng::eKeyCode::Z, ng::eInputState::PRESSED)) {
			CGameActorPlayerBulletTest* pBullet = APP_CREATE_GAME_ACTOR(CGameActorPlayerBulletTest());
			if(pBullet != nullptr) {
				ng::Vector3 position = pBullet->GetTransform().GetPosition();
				position = transform.GetPosition();
				pBullet->GetTransform().SetPosition(position);
			}
		}
	}

}	// namespace app
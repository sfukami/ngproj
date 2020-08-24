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
#include "app/input/appInputModule.h"

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

			// 親トランスフォーム設定
			CTransform& transform = m_sprite.GetTransform();
			transform.SetParent(&m_transform);
		}

		return true;
	}
	
	void CGameActorPlayerTest::Destroy()
	{
		m_sprite.Destroy();
	}

	void CGameActorPlayerTest::_update(float deltaTime)
	{
		// プレイヤー
		// 移動
		{
			ng::Vector3 position = m_transform.GetPosition();

			if(CInputModule::CheckKeyboardInput(ng::eKeyCode::LEFT, ng::eInputState::HELD)) {
				position.x -= 0.1f;
			}
			else if(CInputModule::CheckKeyboardInput(ng::eKeyCode::RIGHT, ng::eInputState::HELD)) {
				position.x += 0.1f;
			}
			else if(CInputModule::CheckKeyboardInput(ng::eKeyCode::UP, ng::eInputState::HELD)) {
				position.y += 0.1f;
			}
			else if(CInputModule::CheckKeyboardInput(ng::eKeyCode::DOWN, ng::eInputState::HELD)) {
				position.y -= 0.1f;
			}

			m_transform.SetPosition(position);
		}
		// 回転
		{
			ng::Quaternion rotation = m_transform.GetRotation();

			ng::Vector3 angle;
			ng::QuaternionOp::ToEulerAngle(angle, rotation);

			if(CInputModule::CheckKeyboardInput(ng::eKeyCode::R, ng::eInputState::HELD)) {
				angle.z -= 1.f;
			} else if(CInputModule::CheckKeyboardInput(ng::eKeyCode::Q, ng::eInputState::HELD)) {
				angle.z += 1.f;
			}

			ng::QuaternionOp::FromEulerAngle(rotation, angle);
			m_transform.SetRotation(rotation);
		}
		// スケーリング
		{
			ng::Vector3 scale = m_transform.GetScale();

			if(CInputModule::CheckKeyboardInput(ng::eKeyCode::J, ng::eInputState::HELD)) {
				scale.x -= 0.1f;
			}
			else if(CInputModule::CheckKeyboardInput(ng::eKeyCode::L, ng::eInputState::HELD)) {
				scale.x += 0.1f;
			}
			else if(CInputModule::CheckKeyboardInput(ng::eKeyCode::I, ng::eInputState::HELD)) {
				scale.y += 0.1f;
			}
			else if(CInputModule::CheckKeyboardInput(ng::eKeyCode::K, ng::eInputState::HELD)) {
				scale.y -= 0.1f;
			}

			m_transform.SetScale(scale);
		}

		// スプライト
		{
			CTransform& transform = m_sprite.GetTransform();

			// 移動
			{
				ng::Vector3 position = transform.GetPosition();

				position.x = 1.f;

				transform.SetPosition(position);
			}
			// 回転
			{
				ng::Quaternion rotation = transform.GetRotation();

				ng::Vector3 angle;
				ng::QuaternionOp::ToEulerAngle(angle, rotation);

				angle.z += 1.f;

				ng::QuaternionOp::FromEulerAngle(rotation, angle);

				transform.SetRotation(rotation);
			}
		}
	}

	void CGameActorPlayerTest::_render()
	{
		m_sprite.RegisterRender();
	}

}	// namespace app
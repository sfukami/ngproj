/*!
* @file		appGameActorEnemyTest.cpp
* @brief	ゲームアクター 敵 テスト
* @date		2020-08-28
* @author	s.fukami
*/

#include "appGameActorEnemyTest.h"
#include "app/resource/appResourceModule.h"
#include "app/input/appInputModule.h"
#include "app/graphic/material/appMaterialFormat.h"
#include "app/graphic/material/appMaterialUtil.h"

#include "app/graphic/shader/effect/appShaderEffectSpriteColor.h"

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
		{
			MaterialFormat format;
			MaterialUtil::GetMaterialFormatSprite(&format);
			format.SetShaderEffectName("sprite_color");
			format.SetRootSignatureName("sprite_t0");
			format.SetPipelineStateName("sprite_color");
			format.vertexShader.SetFilePath("../resource/shader/sprite_color.hlsl");
			format.pixelShader.SetFilePath("../resource/shader/sprite_color.hlsl");
			
			if(!m_sprite.Create(
				1, 1
				, format
				)) {
				return false;
			}

			// シェーダーエフェクトのパラメータ変更
			CMaterial& material = m_sprite.GetRender().GetMaterial();
			auto shdEffPtr = ng::DynamicCast<CShaderEffectSpriteColor>(material.GetShaderEffect());
			shdEffPtr->SetColor(ng::Color(1, 0, 0));
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
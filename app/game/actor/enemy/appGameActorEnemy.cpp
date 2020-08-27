/*!
* @file		appGameActorEnemy.cpp
* @brief	ゲームアクター 敵
* @date		2020-08-28
* @author	s.fukami
*/

#include "appGameActorEnemy.h"
#include "app/game/job/appGameJobUtil.h"

namespace app
{
	CGameActorEnemy::CGameActorEnemy()
		: CGameActor(eGameActorType::PLAYER)
	{
	}

	CGameActorEnemy::~CGameActorEnemy()
	{
	}

	void CGameActorEnemy::Schedule(float deltaTime)
	{
		GameJobUtil::CreateGameJob(eGameJobType::UPDATE_ENEMY, this, &CGameActorEnemy::Update, deltaTime);
		GameJobUtil::CreateGameJob(eGameJobType::RENDER_ENEMY, this, &CGameActorEnemy::Render);
	}

	void CGameActorEnemy::Update(float deltaTime)
	{
		_update(deltaTime);
	}

	void CGameActorEnemy::Render()
	{
		_render();
	}

	void CGameActorEnemy::_update(float deltaTime)
	{
	}

	void CGameActorEnemy::_render()
	{
	}

}	// namespace app
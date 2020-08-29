/*!
* @file		appGameActorEnemy.cpp
* @brief	ゲームアクター 敵
* @date		2020-08-28
* @author	s.fukami
*/

#include "appGameActorEnemy.h"

namespace app
{
	CGameActorEnemy::CGameActorEnemy()
		: CGameActor(eGameActorType::ENEMY)
	{
	}

	CGameActorEnemy::~CGameActorEnemy()
	{
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
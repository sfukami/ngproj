/*!
* @file		appGameActorBullet.cpp
* @brief	ゲームアクター 弾
* @date		2020-08-26
* @author	s.fukami
*/

#include "appGameActorBullet.h"

namespace app
{
	CGameActorBullet::CGameActorBullet(eGameActorType actorType)
		: CGameActor(actorType)
	{
	}

	CGameActorBullet::~CGameActorBullet()
	{
	}

	void CGameActorBullet::Update(float deltaTime)
	{
		_update(deltaTime);
	}

	void CGameActorBullet::Render()
	{
		_render();
	}

	void CGameActorBullet::_update(float deltaTime)
	{
	}

	void CGameActorBullet::_render()
	{
	}

}	// namespace app
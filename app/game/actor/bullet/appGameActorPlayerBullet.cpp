/*!
* @file		appGameActorPlayerBullet.cpp
* @brief	ゲームアクター プレイヤーの弾
* @date		2020-08-26
* @author	s.fukami
*/

#include "appGameActorPlayerBullet.h"
#include "app/game/job/appGameJobUtil.h"

namespace app
{
	CGameActorPlayerBullet::CGameActorPlayerBullet()
		: CGameActorBullet(eGameActorType::PLAYER_BULLET)
	{
	}

	CGameActorPlayerBullet::~CGameActorPlayerBullet()
	{
	}

	void CGameActorPlayerBullet::Schedule(float deltaTime)
	{
		GameJobUtil::CreateGameJob(eGameJobType::UPDATE_PLAYER_BULLET, this, &CGameActorPlayerBullet::Update, deltaTime);
		GameJobUtil::CreateGameJob(eGameJobType::RENDER_PLAYER_BULLET, this, &CGameActorPlayerBullet::Render);
	}

}	// namespace app
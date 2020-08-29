/*!
* @file		appGameActorPlayerBullet.cpp
* @brief	ゲームアクター プレイヤーの弾
* @date		2020-08-26
* @author	s.fukami
*/

#include "appGameActorPlayerBullet.h"

namespace app
{
	CGameActorPlayerBullet::CGameActorPlayerBullet()
		: CGameActorBullet(eGameActorType::PLAYER_BULLET)
	{
	}

	CGameActorPlayerBullet::~CGameActorPlayerBullet()
	{
	}

}	// namespace app
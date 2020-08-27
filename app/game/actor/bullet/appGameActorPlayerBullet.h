/*!
* @file		appGameActorPlayerBullet.h
* @brief	ゲームアクター プレイヤーの弾
* @date		2020-08-26
* @author	s.fukami
*/

#ifndef __APP_GAME_ACTOR_PLAYER_BULLET_H__
#define __APP_GAME_ACTOR_PLAYER_BULLET_H__

#include "appGameActorBullet.h"

namespace app
{
	/*!
	* @brief					ゲームアクター プレイヤーの弾
	*/
	class CGameActorPlayerBullet : public CGameActorBullet
	{
	public:
		CGameActorPlayerBullet();
		virtual ~CGameActorPlayerBullet();

		/*!
		* @brief					スケジュール
		* @param deltaTime			フレーム更新間隔
		*/
		void Schedule(float deltaTime);
	};

}	// namespace app

#endif	// __APP_GAME_ACTOR_PLAYER_BULLET_H__
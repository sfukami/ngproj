/*!
* @file		appGameActorEnemy.h
* @brief	ゲームアクター 敵
* @date		2020-08-28
* @author	s.fukami
*/

#ifndef __APP_GAME_ACTOR_ENEMY_H__
#define __APP_GAME_ACTOR_ENEMY_H__

#include "../appGameActor.h"

namespace app
{
	/*!
	* @brief					ゲームアクター 敵
	*/
	class CGameActorEnemy : public CGameActor
	{
	public:
		CGameActorEnemy();
		virtual ~CGameActorEnemy();

		/*!
		* @brief					更新
		* @param deltaTime			フレーム更新間隔
		*/
		void Update(float deltaTime);

		/*!
		* @brief					描画
		*/
		void Render();

	private:
		/*! 更新 */
		virtual void _update(float deltaTime);
		/*! 描画 */
		virtual void _render();
	};

}	// namespace app

#endif	// __APP_GAME_ACTOR_ENEMY_H__
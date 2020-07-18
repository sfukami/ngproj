/*!
* @file		appGameActorPlayer.h
* @brief	ゲームアクター プレイヤー
* @date		2020-07-12
* @author	s.fukami
*/

#ifndef __APP_GAME_ACTOR_PLAYER_H__
#define __APP_GAME_ACTOR_PLAYER_H__

#include "../appGameActor.h"

namespace app
{
	/*!
	* @brief					ゲームアクター プレイヤー
	*/
	class CGameActorPlayer : public CGameActor
	{
	public:
		CGameActorPlayer();
		virtual ~CGameActorPlayer();

		/*!
		* @brief					スケジュール
		* @param deltaTime			フレーム更新間隔
		*/
		void Schedule(float deltaTime);

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

#endif	// __APP_GAME_ACTOR_PLAYER_H__
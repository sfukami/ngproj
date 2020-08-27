/*!
* @file		appGameActorPlayerTest.h
* @brief	ゲームアクター プレイヤー テスト
* @date		2020-07-19
* @author	s.fukami
*/

#ifndef __APP_GAME_ACTOR_PLAYER_TEST_H__
#define __APP_GAME_ACTOR_PLAYER_TEST_H__

#include "../appGameActorPlayer.h"
#include "../../appGameActorStateMachine.h"
#include "app/graphic/render/sprite/appSprite.h"

namespace app
{
	/*!
	* @brief					ゲームアクター プレイヤー テスト
	*/
	class CGameActorPlayerTest : public CGameActorPlayer
	{
	public:
		CGameActorPlayerTest();
		~CGameActorPlayerTest();

		/*!
		* @brief					生成
		* @return					成否
		*/
		bool Create();

		/*!
		* @brief					破棄
		*/
		void Destroy();

	private:
		/*! 更新 */
		void _update(float deltaTime);
		/*! 描画 */
		void _render();

		/*! ステート処理 */
		void _state_default(float deltaTime);

	private:
		//! ステート
		enum class State
		{
			DEFAULT,	//!< デフォルト

			NUM
		};

	private:
		CSprite m_sprite;	//!< スプライト

		CGameActorStateMachine<CGameActorPlayerTest, State, State::NUM> m_stateMachine;	//!< ステートマシン
	};

}	// namespace app

#endif	// __APP_GAME_ACTOR_PLAYER_TEST_H__
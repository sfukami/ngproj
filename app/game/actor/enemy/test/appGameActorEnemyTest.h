/*!
* @file		appGameActorEnemyTest.h
* @brief	ゲームアクター 敵 テスト
* @date		2020-08-28
* @author	s.fukami
*/

#ifndef __APP_GAME_ACTOR_ENEMY_TEST_H__
#define __APP_GAME_ACTOR_ENEMY_TEST_H__

#include "../appGameActorEnemy.h"
#include "../../appGameActorStateMachine.h"
#include "app/game/object/sprite/appSpriteObject.h"

namespace app
{
	/*!
	* @brief					ゲームアクター 敵 テスト
	*/
	class CGameActorEnemyTest : public CGameActorEnemy
	{
	public:
		CGameActorEnemyTest();
		~CGameActorEnemyTest();

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
		CSpriteObject m_sprite;	//!< スプライト

		CGameActorStateMachine<CGameActorEnemyTest, State, State::NUM> m_stateMachine;	//!< ステートマシン
	};

}	// namespace app

#endif	// __APP_GAME_ACTOR_ENEMY_TEST_H__
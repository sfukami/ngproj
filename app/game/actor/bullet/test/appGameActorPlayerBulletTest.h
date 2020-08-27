/*!
* @file		appGameActorPlayerBulletTest.h
* @brief	ゲームアクター プレイヤーの弾 テスト
* @date		2020-08-26
* @author	s.fukami
*/

#ifndef __APP_GAME_ACTOR_PLAYER_BULLET_TEST_H__
#define __APP_GAME_ACTOR_PLAYER_BULLET_TEST_H__

#include "../appGameActorPlayerBullet.h"
#include "../../appGameActorStateMachine.h"
#include "app/transform/appTransform.h"
#include "app/graphic/render/sprite/appSprite.h"

namespace app
{
	/*!
	* @brief					ゲームアクター プレイヤーの弾 テスト
	*/
	class CGameActorPlayerBulletTest : public CGameActorPlayerBullet
	{
	public:
		CGameActorPlayerBulletTest();
		~CGameActorPlayerBulletTest();

		/*!
		* @brief					生成
		* @return					成否
		*/
		bool Create();

		/*!
		* @brief					破棄
		*/
		void Destroy();

		/*!
		* @brief					削除チェック
		*/
		bool CheckDelete() const;

		/*! トランスフォーム取得 */
		CTransform& GetTransform();
		const CTransform& GetTransform() const;

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
		CTransform m_transform;	//!< トランスフォーム
		CSprite m_sprite;	//!< スプライト

		CGameActorStateMachine<CGameActorPlayerBulletTest, State, State::NUM> m_stateMachine;	//!< ステートマシン
	};

}	// namespace app

#endif	// __APP_GAME_ACTOR_PLAYER_BULLET_TEST_H__
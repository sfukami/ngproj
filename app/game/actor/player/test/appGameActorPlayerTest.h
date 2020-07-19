/*!
* @file		appGameActorPlayerTest.h
* @brief	ゲームアクター プレイヤー テスト
* @date		2020-07-19
* @author	s.fukami
*/

#ifndef __APP_GAME_ACTOR_PLAYER_TEST_H__
#define __APP_GAME_ACTOR_PLAYER_TEST_H__

#include "../appGameActorPlayer.h"
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
		virtual void _update(float deltaTime);
		/*! 描画 */
		virtual void _render();

	private:
		CSprite m_sprite;	//!< スプライト
	};

}	// namespace app

#endif	// __APP_GAME_ACTOR_PLAYER_TEST_H__
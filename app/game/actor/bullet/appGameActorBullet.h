/*!
* @file		appGameActorBullet.h
* @brief	ゲームアクター 弾
* @date		2020-08-26
* @author	s.fukami
*/

#ifndef __APP_GAME_ACTOR_BULLET_H__
#define __APP_GAME_ACTOR_BULLET_H__

#include "../appGameActor.h"

namespace app
{
	/*!
	* @brief					ゲームアクター 弾
	*/
	class CGameActorBullet : public CGameActor
	{
	public:
		/*!
		* @brief					コンストラクタ
		* @param actorType			ゲームアクタータイプ
		*/
		explicit CGameActorBullet(eGameActorType actorType);

		/*!
		* @brief					デストラクタ
		*/
		virtual ~CGameActorBullet();

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

#endif	// __APP_GAME_ACTOR_BULLET_H__
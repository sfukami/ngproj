/*!
* @file		appGameActor.h
* @brief	ゲームアクター
* @date		2020-07-12
* @author	s.fukami
*/

#ifndef __APP_GAME_ACTOR_H__
#define __APP_GAME_ACTOR_H__

#include "ngLibCore/container/list/intrusive/ngIntrusiveListNode.h"
#include "appGameActorType.h"

namespace app
{
	/*!
	* @brief					ゲームアクター
	*/
	class CGameActor : public ng::CIntrusiveListNode<CGameActor>
	{
	public:
		/*!
		* @brief					コンストラクタ
		* @param actorType			ゲームアクタータイプ
		*/
		explicit CGameActor(eGameActorType actorType);

		/*!
		* @brief					デストラクタ
		*/
		virtual ~CGameActor();
		
		/*!
		* @brief					スケジュール
		* @param deltaTime			フレーム更新間隔
		*/
		virtual void Schedule(float deltaTime);

		/*!
		* @brief					更新
		* @param deltaTime			フレーム更新間隔
		*/
		virtual void Update(float deltaTime);

		/*!
		* @brief					描画
		*/
		virtual void Render();

		/*! ゲームアクタータイプ取得 */
		eGameActorType GetActorType() const;

	private:
		eGameActorType m_actorType;	//!< ゲームアクタータイプ
	};

}	// namespace app

#endif	// __APP_GAME_ACTOR_H__
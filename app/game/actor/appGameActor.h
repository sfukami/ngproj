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
#include "app/transform/appTransformObject.h"

namespace app
{
	/*!
	* @brief					ゲームアクター
	*/
	class CGameActor : public ng::CIntrusiveListNode<CGameActor>, public CTransformObject
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
		* @brief					生成
		* @return					成否
		*/
		virtual bool Create();

		/*!
		* @brief					更新
		* @param deltaTime			フレーム更新間隔
		*/
		virtual void Update(float deltaTime);

		/*!
		* @brief					描画
		*/
		virtual void Render();

		/*!
		* @brief					破棄
		*/
		virtual void Destroy();

		/*!
		* @brief					削除チェック
		*/
		virtual bool CheckDelete() const;

		/*! ゲームアクタータイプ取得 */
		eGameActorType GetActorType() const;

	private:
		eGameActorType m_actorType;	//!< ゲームアクタータイプ
	};

}	// namespace app

#endif	// __APP_GAME_ACTOR_H__
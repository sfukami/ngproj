/*!
* @file		appGameWorld.h
* @brief	ゲームワールド
* @date		2020-07-15
* @author	s.fukami
*/

#ifndef __APP_GAME_WORLD_H__
#define __APP_GAME_WORLD_H__

#include "ngLibCore/container/list/ngIntrusiveList.h"
#include "ngLibCore/container/array/ngFixedArray.h"
#include "../actor/appGameActor.h"
#include "../actor/appGameActorType.h"

namespace app
{
	/*!
	* @brief					ゲームワールド
	*/
	class CGameWorld
	{
	public:
		CGameWorld();
		~CGameWorld();

		/*!
		* @brief					初期化
		* @return					成否
		*/
		bool Initialize();

		/*!
		* @brief					更新
		* @param deltaTime			フレーム更新間隔
		*/
		void Update(float deltaTime);

		/*!
		* @brief					描画	
		*/
		void Render();

		/*!
		* @brief					終了処理
		*/
		void Finalize();
		
		/*!
		* @brief					アクター追加
		*/
		void AddActor(CGameActor& actor);

	private:
		using ActorList = ng::CIntrusiveList<CGameActor>;	//!< アクターリスト
		using ActorListArray = ng::CFixedArray<ActorList, static_cast<ng::u32>(eGameActorType::NUM)>;	//!< アクターリストの配列

	private:
		/*! 各アクターの削除チェック */
		void _checkDeleteActors();

		/*! 各アクターのスケジュール実行 */
		void _scheduleActors(float deltaTime);

		/*! 指定のアクタータイプを全削除 */
		void _clearActor(eGameActorType actorType);

		/*! アクターリスト取得 */
		ActorList& _getActorList(eGameActorType actorType);
		const ActorList& _getActorList(eGameActorType actorType) const;

	private:
		ActorListArray m_actorListArr;	//!< アクターリストの配列
	};

}	// namespace app

#endif	// __APP_GAME_WORLD_H__
/*!
* @file		appGameModule.h
* @brief	ゲームモジュール
* @date		2020-07-16
* @author	s.fukami
*/

#ifndef __APP_GAME_MODULE_H__
#define __APP_GAME_MODULE_H__

#include "ngLibCore/traits/ngNonInstantiable.h"
#include "actor/appGameActorType.h"
#include "job/appGameJobType.h"

namespace app
{
	class CGame;
	class CGameActor;
	class CGameJob;
}

namespace app
{
	/*!
	* @brief					ゲームモジュール
	*/
	class CGameModule : public ng::CNonInstantiable
	{
		friend class CGame;

	public:
		/*!
		* @brief					ゲームアクター追加
		* @param pActor				追加するアクター
		*/
		static void AddActor(CGameActor* pActor);

		/*!
		* @brief					ゲームジョブ追加
		* @param jobType			ゲームジョブ種類
		* @param pJob				追加するジョブ
		* @return					成否
		*/
		static bool AddGameJob(eGameJobType jobType, CGameJob* pJob);

	private:
		/*! ゲームへの参照を設定 */
		static void SetGame(CGame* pGame);

		/*! 有効か */
		static bool _isValid();

	private:
		static CGame* s_pGame;	//!< ゲームへの参照
	};

}	// namespace app

#endif	// __APP_GAME_MODULE_H__
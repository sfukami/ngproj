/*!
* @file		appGame.h
* @brief	ゲーム
* @date		2020-07-16
* @author	s.fukami
*/

#ifndef __APP_GAME_H__
#define __APP_GAME_H__

#include "world/appGameWorld.h"
#include "job/appGameJobManager.h"

namespace app
{
	class CGameJob;
}

namespace app
{
	/*!
	* @brief					ゲーム
	*/
	class CGame
	{
	public:
		CGame();
		~CGame();

		/*!
		* @brief					初期化
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
		* @brief					ゲームアクター追加
		* @param pActor				追加するアクター
		*/
		void AddActor(CGameActor* pActor);

		/*!
		* @brief					ゲームジョブ追加
		* @param jobType			ゲームジョブ種類
		* @param pJob				追加するジョブ
		* @return					成否
		*/
		bool EnqueueJob(eGameJobType jobType, CGameJob* pJob);

	private:
		CGameWorld m_world;		//!< ゲームワールド
		CGameJobManager m_jobMngr;	//!< ジョブ管理
	};

}	// namespace app

#endif	// __APP_GAME_H__
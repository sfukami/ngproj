/*!
* @file		appGameJobManager.h
* @brief	ゲーム ジョブ管理
* @date		2020-07-16
* @author	s.fukami
*/

#ifndef __APP_GAME_JOB_MANAGER_H__
#define __APP_GAME_JOB_MANAGER_H__

#include "app/job/appJobManager.h"
#include "appGameJobType.h"

namespace ng
{
	class IMemoryAllocator;
}
namespace app
{
	class CGameJob;
}

namespace app
{
	/*!
	* @brief					ゲーム ジョブ管理
	*/
	class CGameJobManager
	{
	public:
		CGameJobManager();
		~CGameJobManager();

		/*!
		* @brief					初期化
		* @param alloc				利用するメモリアロケータ
		*/
		bool Initialize(ng::IMemoryAllocator& alloc);

		/*!
		* @brief					ジョブ実行
		*/
		void ExecuteJob();

		/*!
		* @brief					ジョブ実行 範囲指定
		* @param begin				先頭のジョブタイプ
		* @param end				末尾のジョブタイプ
		*/
		void ExecuteJobRange(eGameJobType begin, eGameJobType end);

		/*!
		* @brief					終了処理
		*/
		void Finalize();

		/*!
		* @brief					ジョブ追加
		* @param jobType			ゲームジョブ種類
		* @param pJob				追加するジョブ
		* @return					成否
		*/
		bool EnqueueJob(eGameJobType jobType, CGameJob* pJob);

	private:
		CJobManager m_jobMngr;	//!< ジョブ管理
	};

}	// namespace app

#endif	// __APP_GAME_JOB_MANAGER_H__
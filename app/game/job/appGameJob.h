/*!
* @file		appGameJob.h
* @brief	ゲームジョブ 基底クラス
* @date		2020-07-16
* @author	s.fukami
*/

#ifndef __APP_GAME_JOB_H__
#define __APP_GAME_JOB_H__

#include "ngLibCore/job/ngJob.h"

namespace app
{
	/*!
	* @brief					ゲームジョブ 基底クラス
	*/
	class CGameJob : public ng::IJob
	{
	public:
		CGameJob();
		virtual ~CGameJob();

		/*!
		* @brief					ジョブ実行
		*/
		virtual void Execute();
	};

}	// namespace app

#endif	// __APP_GAME_JOB_H__
/*!
* @file		appGameJobQueueSize.h
* @brief	ゲーム ジョブキューのサイズ
* @date		2020-07-16
* @author	s.fukami
*/

#ifndef __APP_GAME_JOB_QUEUE_SIZE_H__
#define __APP_GAME_JOB_QUEUE_SIZE_H__

namespace app
{
	enum class eGameJobType : unsigned int;
}

namespace app
{
	/*!
	* @brief					各ジョブ種類のジョブキューサイズを取得
	*/
	unsigned int GetGameJobQueueSize(eGameJobType jobType);

	/*!
	* @brief					全ジョブ種類のジョブキューサイズを取得
	*/
	const unsigned int* GetGameJobQueueSizeTable();

}	// namespace app

#endif	// __APP_GAME_JOB_QUEUE_SIZE_H__
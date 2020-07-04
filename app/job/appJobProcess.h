/*!
* @file		ngJobProcess.h
* @brief	ジョブ処理定義
* @date		2020-07-03
* @author	s.fukami
*/

#ifndef __APP_JOB_PROCESS_H__
#define __APP_JOB_PROCESS_H__

namespace app
{
	/*!
	* @brief					ジョブ処理定義
	*/
	enum class eJobProcess : unsigned int
	{
		UPDATE,			//!< 更新時処理
		LATE_UPDATE,	//!< 更新後処理
		END_OF_FRAME,	//!< 描画後処理

		NUM
	};

}	// namespace app

#endif	// __APP_JOB_PROCESS_H__
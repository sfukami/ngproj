/*!
* @file		ngJob.h
* @brief	ジョブ インターフェース
* @date		2020-07-01
* @author	s.fukami
*/

#ifndef __NG_CORE_JOB_H__
#define __NG_CORE_JOB_H__

namespace ng
{
	/*!
	* @brief					ジョブ インターフェース
	*/
	NG_DECL class IJob
	{
	public:
		IJob() { }
		virtual ~IJob() { }

		/*!
		* @brief					ジョブ実行
		*/
		virtual void Execute() = 0;
	};

}	// namespace ng

#endif	// __NG_CORE_JOB_H__
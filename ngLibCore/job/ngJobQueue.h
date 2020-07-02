﻿/*!
* @file		ngJobQueue.h
* @brief	ジョブキュー
* @date		2020-07-01
* @author	s.fukami
*/

#ifndef __NG_CORE_JOB_QUEUE_H__
#define __NG_CORE_JOB_QUEUE_H__

#include "ngLibCore/memory/pointer/ngSharedPtr.h"
#include "ngLibCore/container/queue/ngFixedQueue.h"

namespace ng
{
	class IMemoryAllocator;
	class IJob;
}

namespace ng
{
	/*!
	* @brief					ジョブキュー
	*/
	NG_DECL class CJobQueue
	{
	public:
		CJobQueue();
		~CJobQueue();

		/*!
		* @brief					初期化
		* @param max				ジョブの最大数
		* @param alloc				使用するメモリアロケータ
		* @return					NG エラーコード
		*/
		NG_ERRCODE Initialize(u32 max, IMemoryAllocator& alloc);

		/*!
		* @brief					全ジョブの実行
		*/
		void Execute();

		/*!
		* @brief					終了処理
		*/
		void Finalize();

		/*!
		* @brief					ジョブ追加
		* @return					成否
		*/
		bool AddJob(CSharedPtr<IJob>& jobPtr);

	private:
		CFixedQueue<CSharedPtr<IJob>> m_jobQueue;	//!< ジョブのキュー
	};

}	// namespace ng

#endif	// __NG_CORE_JOB_QUEUE_H__
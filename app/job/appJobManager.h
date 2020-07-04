/*!
* @file		appJobManager.h
* @brief	ジョブ管理
* @date		2020-07-03
* @author	s.fukami
*/

#ifndef __APP_JOB_MANAGER_H__
#define __APP_JOB_MANAGER_H__

#include "ngLibCore/job/ngJobQueue.h"
#include "ngLibCore/container/array/ngFixedArray.h"
#include "appJobProcess.h"

namespace ng
{
	class IMemoryAllocator;
	class IJob;
	template <class T> class CSharedPtr;
}

namespace app
{
	/*!
	* @brief					ジョブ管理
	*/
	class CJobManager
	{
	public:
		CJobManager();
		~CJobManager();

		/*!
		* @brief					初期化
		* @param jobMax				ジョブの最大数
		* @param alloc				使用するメモリアロケータ
		* @return					成否
		*/
		bool Initialize(ng::u32 jobMax, ng::IMemoryAllocator& alloc);

		/*!
		* @brief					ジョブ追加
		* @param jobPtr				追加するジョブ
		* @param jobProc			ジョブ処理定義
		* @return					成否
		*/
		bool AddJob(
			ng::CSharedPtr<ng::IJob>& jobPtr,
			eJobProcess jobProc
			);

		/*!
		* @brief					ジョブ追加
		* @param jobProc			ジョブ処理定義
		*/
		void ExecuteJob(eJobProcess jobProc);

		/*!
		* @brief				終了処理
		*/
		void Finalize();

	private:
		/*! ジョブキュー取得 */
		ng::CJobQueue& _getJobQueue(eJobProcess jobProc);

	private:
		ng::CFixedArray<ng::CJobQueue, static_cast<int>(eJobProcess::NUM)> m_jobQueueArr;	//!< ジョブキューの配列
	};

}	// namespace app

#endif	// __APP_JOB_MANAGER_H__
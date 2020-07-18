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

namespace ng
{
	class IMemoryAllocator;
	class IJob;
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
		* @param slotMax			スロット最大数
		* @param jobMaxPerSlot		スロット毎のジョブ最大数
		* @param alloc				使用するメモリアロケータ
		* @return					成否
		*/
		bool Initialize(
			unsigned int slotMax
			, const unsigned int jobMaxPerSlot[]
			, ng::IMemoryAllocator& alloc
			);

		/*!
		* @brief					ジョブ追加
		* @param slot				対象のスロット
		* @param pJob				追加するジョブ
		* @return					成否
		*/
		bool EnqueueJob(unsigned int slot, ng::IJob* pJob);

		/*!
		* @brief					ジョブ実行
		* @param slot				対象のスロット
		*/
		void ExecuteJob(unsigned int slot);

		/*!
		* @brief					終了処理
		*/
		void Finalize();

	private:
		/*! 初期化済みか */
		bool _isInit() const;
		
		/*! ジョブキュー取得 */
		ng::CJobQueue& _getJobQueue(unsigned int slot);
		const ng::CJobQueue& _getJobQueue(unsigned int slot) const;

	private:
		ng::CFixedArray<ng::CJobQueue> m_jobQueueArr;	//!< ジョブキューの配列
		bool m_isInit;	//!< 初期化済みか
	};

}	// namespace app

#endif	// __APP_JOB_MANAGER_H__
/*!
* @file		appJobManager.cpp
* @brief	ジョブ管理
* @date		2020-07-03
* @author	s.fukami
*/

#include "appJobManager.h"

namespace app
{
	CJobManager::CJobManager()
		: m_isInit(false)
	{
	}

	CJobManager::~CJobManager()
	{
	}

	bool CJobManager::Initialize(
		unsigned int slotMax
		, const unsigned int jobMaxPerSlot[]
		, ng::IMemoryAllocator& alloc
		)
	{
		NG_ERRCODE err = m_jobQueueArr.Initialize(alloc, slotMax);
		if(NG_FAILED(err)) {
			NG_ERRLOG_C("JobManager", err, "ジョブキュー配列の初期化に失敗しました.");
			return false;
		}

		for(unsigned int i = 0; i < slotMax; i++)
		{
			unsigned int jobMax = jobMaxPerSlot[i];
			ng::CJobQueue& jobQueue = m_jobQueueArr[i];

			if(NG_FAILED(err = jobQueue.Initialize(jobMax, alloc))) {
				NG_ERRLOG_C("JobManager", err, "ジョブキューの初期化に失敗しました.");
				Finalize();
				return false;
			}
		}

		m_isInit = true;

		return true;
	}

	bool CJobManager::EnqueueJob(unsigned int slot, ng::IJob* pJob)
	{
		NG_ASSERT(_isInit());

		return _getJobQueue(slot).EnqueueJob(pJob);
	}
	void CJobManager::ExecuteJob(unsigned int slot)
	{
		NG_ASSERT(_isInit());

		_getJobQueue(slot).Execute();
	}
	void CJobManager::Finalize()
	{
		for(ng::u32 i = 0; i < m_jobQueueArr.Size(); i++)
		{
			_getJobQueue(i).Finalize();
		}

		m_jobQueueArr.Finalize();

		m_isInit = false;
	}

	bool CJobManager::_isInit() const
	{
		return m_isInit;
	}

	ng::CJobQueue& CJobManager::_getJobQueue(unsigned int slot)
	{
		NG_ASSERT(_isInit());
		NG_ASSERT(slot < m_jobQueueArr.Size());

		return m_jobQueueArr[slot];
	}
	const ng::CJobQueue& CJobManager::_getJobQueue(unsigned int slot) const
	{
		return const_cast<CJobManager*>(this)->_getJobQueue(slot);
	}

}	// namespace app
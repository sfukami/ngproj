/*!
* @file		appJobManager.cpp
* @brief	ジョブ管理
* @date		2020-07-03
* @author	s.fukami
*/

#include "ngLibCore/memory/pointer/ngSharedPtr.h"
#include "appJobManager.h"

namespace app
{
	CJobManager::CJobManager()
	{
	}

	CJobManager::~CJobManager()
	{
	}

	bool CJobManager::Initialize(ng::u32 jobMax, ng::IMemoryAllocator& alloc)
	{
		for(ng::size_type i = 0; i < m_jobQueueArr.Size(); i++)
		{
			NG_ERRCODE err = m_jobQueueArr[i].Initialize(jobMax, alloc);
			if(NG_FAILED(err)) {
				NG_ERRLOG_C("JobManager", err, "ジョブキューの初期化に失敗しました.");
				return false;
			}
		}

		return true;
	}

	bool CJobManager::AddJob(
		ng::CSharedPtr<ng::IJob>& jobPtr,
		eJobProcess jobProc
		)
	{
		ng::CJobQueue& jobQueue = _getJobQueue(jobProc);

		return jobQueue.AddJob(jobPtr);
	}

	void CJobManager::ExecuteJob(eJobProcess jobProc)
	{
		ng::CJobQueue& jobQueue = _getJobQueue(jobProc);

		jobQueue.Execute();
	}

	void CJobManager::Finalize()
	{
		for(ng::size_type i = 0; i < m_jobQueueArr.Size(); i++)
		{
			m_jobQueueArr[i].Finalize();
		}
	}

	ng::CJobQueue& CJobManager::_getJobQueue(eJobProcess jobProc)
	{
		NG_ASSERT(jobProc < eJobProcess::NUM);

		return m_jobQueueArr[ static_cast<int>(jobProc) ];
	}
	
}	// namespace app
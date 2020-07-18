/*!
* @file		ngJobQueue.cpp
* @brief	ジョブキュー
* @date		2020-07-01
* @author	s.fukami
*/

#include "ngJobQueue.h"
#include "ngJob.h"

namespace ng
{
	CJobQueue::CJobQueue()
	{
	}

	CJobQueue::~CJobQueue()
	{
		Finalize();
	}

	NG_ERRCODE CJobQueue::Initialize(u32 max, IMemoryAllocator& alloc)
	{
		NG_ERRCODE ret = m_jobQueue.Initialize(max, alloc);

		if(NG_FAILED(ret)) {
			NG_ERRLOG_C("JobQueue", ret, "ジョブキューの初期化に失敗しました.");
			return ret;
		}

		return ret;
	}

	void CJobQueue::Execute()
	{
		while(!m_jobQueue.Empty())
		{
			m_jobQueue.Front()->Execute();
			m_jobQueue.PopFront();
		}
	}

	void CJobQueue::Finalize()
	{
		m_jobQueue.Finalize();
	}

	bool CJobQueue::EnqueueJob(IJob* pJob)
	{
		if(m_jobQueue.Full()) {
			return false;
		}

		m_jobQueue.PushBack(pJob);

		return true;
	}

}	// namespace ng
/*!
* @file		appGameJobManager.cpp
* @brief	ゲーム ジョブ管理
* @date		2020-07-16
* @author	s.fukami
*/

#include "appGameJobManager.h"
#include "appGameJobType.h"
#include "appGameJob.h"

namespace app
{
	CGameJobManager::CGameJobManager()
	{
	}
	CGameJobManager::~CGameJobManager()
	{
	}

	bool CGameJobManager::Initialize(ng::IMemoryAllocator& alloc)
	{
		const unsigned int jobQueueNum = ng::UnderlyingCast(eGameJobType::NUM);
		unsigned int jobQueueSizeTable[ jobQueueNum ];

		// 各ジョブキューのサイズ
		for(int i = 0; i < NG_ARRAY_SIZE(jobQueueSizeTable); i++)
		{
			jobQueueSizeTable[i] = 1;
		}

		// ジョブ管理初期化
		if(!m_jobMngr.Initialize(
			jobQueueNum
			, jobQueueSizeTable
			, alloc
			)) {
			NG_ERRLOG("GameJobManager", "ジョブ管理の初期化に失敗しました.");
			return false;
		}

		return true;
	}

	void CGameJobManager::ExecuteJob()
	{
		for(auto slot : eGameJobType())
		{
			m_jobMngr.ExecuteJob(ng::UnderlyingCast(slot));
		}
	}

	void CGameJobManager::ExecuteJobRange(eGameJobType begin, eGameJobType end)
	{
		NG_ASSERT_COMPARE(begin, <, end);

		for(eGameJobType slot = begin; slot != end; ++slot)
		{
			m_jobMngr.ExecuteJob(ng::UnderlyingCast(slot));
		}
	}

	void CGameJobManager::Finalize()
	{
		m_jobMngr.Finalize();
	}

	bool CGameJobManager::EnqueueJob(eGameJobType jobType, CGameJob* pJob)
	{
		return m_jobMngr.EnqueueJob(ng::UnderlyingCast(jobType), pJob);
	}

}	// namespace app
/*!
* @file		appJobModule.cpp
* @brief	ジョブ機能
* @date		2020-07-03
* @author	s.fukami
*/

#include "appJobModule.h"

namespace app
{
	CJobManager* CJobModule::s_pJobMngr = nullptr;

	bool CJobModule::AddJob(
		ng::CSharedPtr<ng::IJob>& jobPtr,
		eJobProcess jobProc
		)
	{
		if(_isValid()) {
			return s_pJobMngr->AddJob(jobPtr, jobProc);
		}

		return false;
	}

	void CJobModule::SetJobManager(CJobManager* pJobMngr)
	{
		s_pJobMngr = pJobMngr;
	}

	bool CJobModule::_isValid()
	{
		return (s_pJobMngr != nullptr);
	}

}	// namespace app
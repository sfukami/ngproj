/*!
* @file		appGameModule.h
* @brief	ゲームモジュール
* @date		2020-07-16
* @author	s.fukami
*/

#include "appGameModule.h"
#include "appGame.h"

namespace app
{
	CGame* CGameModule::s_pGame = nullptr;

	void CGameModule::AddActor(CGameActor* pActor)
	{
		if(!_isValid()) return;

		s_pGame->AddActor(pActor);
	}

	bool CGameModule::AddGameJob(eGameJobType jobType, CGameJob* pJob)
	{
		if(!_isValid()) return false;

		return s_pGame->EnqueueJob(jobType, pJob);
	}

	void CGameModule::SetGame(CGame* pGame)
	{
		s_pGame = pGame;
	}

	bool CGameModule::_isValid()
	{
		return (s_pGame != nullptr);
	}

}	// namespace app
/*!
* @file		appGame.cpp
* @brief	ゲーム
* @date		2020-07-16
* @author	s.fukami
*/

#include "appGame.h"
#include "appGameModule.h"
#include "app/memory/appMemoryUtil.h"

namespace app
{
	CGame::CGame()
	{
	}
	CGame::~CGame()
	{
	}

	bool CGame::Initialize()
	{
		// ジョブ管理初期化
		if(!m_jobMngr.Initialize(APP_MEMALLOC_APPLICATION)) {
			NG_ERRLOG("Game", "ジョブ管理の初期化に失敗しました.");
			return false;
		}

		// ゲームワールド初期化
		if(!m_world.Initialize()) {
			NG_ERRLOG("Game", "ゲームワールドの初期化に失敗しました.");
			return false;
		}

		// ゲームモジュールへ参照を設定
		CGameModule::SetGame(this);

		return true;
	}

	void CGame::Update(float deltaTime)
	{
		m_world.Update(deltaTime);

		m_jobMngr.ExecuteJobRange(eGameJobType::BEGIN_UPDATE, eGameJobType::END_UPDATE);
	}

	void CGame::Render()
	{
		m_world.Render();

		m_jobMngr.ExecuteJobRange(eGameJobType::BEGIN_RENDER, eGameJobType::END_RENDER);
	}

	void CGame::Finalize()
	{
		m_world.Finalize();
		m_jobMngr.Finalize();

		// ゲームモジュールの参照をクリア
		CGameModule::SetGame(nullptr);
	}

	void CGame::AddActor(CGameActor* pActor)
	{
		NG_ASSERT_NOT_NULL(pActor);

		m_world.AddActor(*pActor);
	}

	bool CGame::EnqueueJob(eGameJobType jobType, CGameJob* pJob)
	{
		NG_ASSERT_NOT_NULL(pJob);

		return m_jobMngr.EnqueueJob(jobType, pJob);
	}

}	// namespace app
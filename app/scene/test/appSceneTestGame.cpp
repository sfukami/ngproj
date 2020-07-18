/*!
* @file		appSceneTestGame.cpp
* @brief	シーン ゲームテスト
* @date		2020-07-15
* @author	s.fukami
*/

#include "app/common/appCommon.h"
#include "appSceneTestGame.h"
#include "app/graphic/appGraphicModule.h"
#include "app/graphic/pipeline/appGraphicPipelineDefault.h"
//test
#include "app/game/actor/appGameActorMacro.h"
#include "app/game/actor/player/appGameActorPlayer.h"

namespace app
{
	CSceneTestGame::CSceneTestGame()
	{
	}
	CSceneTestGame::~CSceneTestGame()
	{
	}

	bool CSceneTestGame::Initialize()
	{
		m_pPipeline = NG_NEW(APP_MEMALLOC_APPLICATION) CGraphicPipelineDefault();

		// グラフィックパイプライン初期化
		if(m_pPipeline->Initialize()) {
			CGraphicModule::SetGraphicPipeline(m_pPipeline);
		} else {
			NG_ERRLOG("SceneTestGame", "グラフィックパイプラインの初期化に失敗しました.");
			NG_SAFE_DELETE(APP_MEMALLOC_APPLICATION, m_pPipeline);
			return false;
		}

		// ゲーム初期化
		if(!m_game.Initialize()) {
			NG_ERRLOG("SceneTestGame", "ゲームの初期化に失敗しました.");
			return false;
		}

		//test
		CGameActorPlayer* pPlayer = APP_CREATE_GAME_ACTOR(CGameActorPlayer());

		return true;
	}

	void CSceneTestGame::Update(float deltaTime)
	{
		m_game.Update(deltaTime);
	}

	void CSceneTestGame::Render()
	{
		m_game.Render();
	}

	void CSceneTestGame::Finalize()
	{
		m_game.Finalize();
		
		if(m_pPipeline != nullptr) {
			NG_SAFE_DELETE(APP_MEMALLOC_APPLICATION, m_pPipeline);
		}
	}

}	// namespace app
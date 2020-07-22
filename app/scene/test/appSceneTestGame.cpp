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
#include "app/game/actor/player/test/appGameActorPlayerTest.h"
//test
#include "app/resource/appResourceModule.h"
#include "app/resource/texture/appTexture.h"
#include "ngLibApp/resource/ngResourceHandle.h"

namespace app
{
	CSceneTestGame::CSceneTestGame()
		: m_pPlayer(nullptr)
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
		//CGameActorPlayer* pPlayer = APP_CREATE_GAME_ACTOR(CGameActorPlayer());
		m_pPlayer = APP_CREATE_GAME_ACTOR(CGameActorPlayerTest());
		m_pPlayer->Create();

		/*
		//test
		const char* pFilePath = "../resource/texture/test.bmp";
		ng::CResourceHandle<CTexture> texHndl;
		CResourceModule::LoadResource(pFilePath, eResourceMemoryType::FIXED, texHndl);

		auto texPtr = texHndl.GetResource();
		*/

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
		if(m_pPlayer != nullptr) {
			m_pPlayer->Destroy();
			//NG_SAFE_DELETE(GameActorMacro::_GetGameActorMemAlloc(), m_pPlayer);
		}

		m_game.Finalize();
		
		if(m_pPipeline != nullptr) {
			NG_SAFE_DELETE(APP_MEMALLOC_APPLICATION, m_pPipeline);
		}
	}

}	// namespace app
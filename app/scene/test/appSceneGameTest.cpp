/*!
* @file		appSceneGameTest.cpp
* @brief	シーン ゲームテスト
* @date		2020-07-15
* @author	s.fukami
*/

#include "app/common/appCommon.h"
#include "appSceneGameTest.h"
#include "app/graphic/appGraphicModule.h"
#include "app/graphic/pipeline/appGraphicPipelineDefault.h"

#include "app/game/actor/appGameActorMacro.h"
#include "app/game/actor/player/test/appGameActorPlayerTest.h"
#include "app/game/actor/enemy/test/appGameActorEnemyTest.h"

namespace app
{
	CSceneGameTest::CSceneGameTest()
		: m_pPlayer(nullptr)
	{
	}
	CSceneGameTest::~CSceneGameTest()
	{
	}

	bool CSceneGameTest::Initialize()
	{
		m_pPipeline = NG_NEW(APP_GET_MEMALLOC(APPLICATION)) CGraphicPipelineDefault();

		// グラフィックパイプライン初期化
		if(m_pPipeline->Initialize()) {
			CGraphicModule::SetGraphicPipeline(m_pPipeline);
		} else {
			NG_ERRLOG("SceneGameTest", "グラフィックパイプラインの初期化に失敗しました.");
			NG_SAFE_DELETE(APP_GET_MEMALLOC(APPLICATION), m_pPipeline);
			return false;
		}

		// ゲーム初期化
		if(!m_game.Initialize()) {
			NG_ERRLOG("SceneGameTest", "ゲームの初期化に失敗しました.");
			return false;
		}

		// プレイヤー生成
		{
			CGameActorPlayerTest* pPlayer = APP_CREATE_GAME_ACTOR(CGameActorPlayerTest());
			if(pPlayer != nullptr) {
				CTransform& transform = pPlayer->GetTransform();
				transform.SetPosition(ng::Vector3(0.f, -1.f, 0.f));
			}
		}
		// 敵生成
		{
			CGameActorEnemyTest* pEnemy = APP_CREATE_GAME_ACTOR(CGameActorEnemyTest());
			if(pEnemy != nullptr) {
				CTransform& transform = pEnemy->GetTransform();
				transform.SetPosition(ng::Vector3(0.f, 1.f, 0.f));
			}
		}

		return true;
	}

	void CSceneGameTest::Update(float deltaTime)
	{
		m_game.Update(deltaTime);
	}

	void CSceneGameTest::Render()
	{
		m_game.Render();
	}

	void CSceneGameTest::Finalize()
	{
		m_game.Finalize();
		
		if(m_pPipeline != nullptr) {
			NG_SAFE_DELETE(APP_GET_MEMALLOC(APPLICATION), m_pPipeline);
		}
	}

}	// namespace app
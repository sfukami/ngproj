/*!
* @file		appSceneRoot.cpp
* @brief	シーン テスト
* @date		2020-06-30
* @author	s.fukami
*/

#include "app/common/appCommon.h"
#include "appSceneRoot.h"
#include "../appSceneModule.h"
#include "../test/appSceneTest.h"
#include "../test/appSceneTestImGui.h"
#include "../test/appSceneTestGame.h"
#include "../../memory/appMemoryModule.h"

namespace app
{
	CSceneRoot::CSceneRoot()
	{
	}
	CSceneRoot::~CSceneRoot()
	{
	}

	bool CSceneRoot::Initialize()
	{
		return true;
	}

	void CSceneRoot::Update(float deltaTime)
	{
		auto scenePtr = NG_MAKE_SHARED_PTR(IScene, APP_MEMALLOC_APPLICATION,
			//CSceneTest()
			//CSceneTestImGui()
			CSceneTestGame()
			);
		//CSceneModule::ChangeScene(eSceneId::GAME, scenePtr);
		CSceneModule::RequestChangeScene(eSceneId::GAME, scenePtr);
	}

	void CSceneRoot::Render()
	{
	}

	void CSceneRoot::Finalize()
	{
	}

}	// namespace app
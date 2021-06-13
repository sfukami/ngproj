/*!
* @file		appSceneRoot.cpp
* @brief	シーン テスト
* @date		2020-06-30
* @author	s.fukami
*/

#include "app/common/appCommon.h"
#include "../../memory/appMemoryModule.h"
#include "../appSceneModule.h"
#include "appSceneRoot.h"
// Test Scene
#include "../test/appSceneGraphicPipelineTest.h"
#include "../test/appSceneGameTest.h"

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
		auto scenePtr = NG_MAKE_SHARED_PTR_CTOR(IScene, APP_GET_MEMALLOC(APPLICATION),
			CSceneGraphicPipelineTest()
			//CSceneGameTest()
			);
		CSceneModule::RequestChangeScene(eSceneId::GAME, scenePtr);
	}

	void CSceneRoot::Render()
	{
	}

	void CSceneRoot::Finalize()
	{
	}

	const char* CSceneRoot::GetName() const
	{
		return "SceneRoot";
	}

}	// namespace app
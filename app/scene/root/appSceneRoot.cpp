/*!
* @file		appSceneRoot.cpp
* @brief	シーン テスト
* @date		2020-06-30
* @author	s.fukami
*/

#include "appSceneRoot.h"
#include "../appSceneModule.h"
#include "../test/appSceneTest.h"

//test
#include "ngLibCore/system/ngSysUtil.h"

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
		auto scenePtr = NG_MAKE_SHARED_PTR(IScene, NG_SYSALLOC_MAINSYS, CSceneTest());
		CSceneModule::ChangeScene(eSceneId::GAME, scenePtr);
	}

	void CSceneRoot::Render()
	{
	}

	void CSceneRoot::Finalize()
	{
	}

}	// namespace app
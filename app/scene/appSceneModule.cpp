/*!
* @file		appSceneModule.cpp
* @brief	シーン機能
* @date		2020-07-01
* @author	s.fukami
*/

#include "ngLibCore/job/ngJob.h"
#include "app/common/appCommon.h"
#include "appSceneModule.h"

namespace app
{
	CSceneManager* CSceneModule::s_pSceneMngr = nullptr;

	void CSceneModule::RequestChangeScene(eSceneId sceneId, ng::CSharedPtr<IScene>& scenePtr)
	{
		if(!_isValid()) return;

		s_pSceneMngr->RequestChangeScene(static_cast<unsigned int>(sceneId), scenePtr);
	}

	bool CSceneModule::ChangeScene(eSceneId sceneId, ng::CSharedPtr<IScene>& scenePtr)
	{
		if(!_isValid()) return false;
		
		return s_pSceneMngr->RegisterScene(static_cast<unsigned int>(sceneId), scenePtr);
	}

	void CSceneModule::SetSceneManager(CSceneManager* pSceneMngr)
	{
		s_pSceneMngr = pSceneMngr;
	}

	bool CSceneModule::_isValid()
	{
		return (s_pSceneMngr != nullptr);
	}

}	// namespace app
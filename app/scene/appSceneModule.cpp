/*!
* @file		appSceneModule.cpp
* @brief	シーン機能
* @date		2020-07-01
* @author	s.fukami
*/

#include "appSceneModule.h"

namespace app
{
	CSceneManager* CSceneModule::s_pSceneMngr = nullptr;

	bool CSceneModule::ChangeScene(eSceneId sceneId, ng::CSharedPtr<IScene>& scenePtr)
	{
		if(_isValid()) {
			return s_pSceneMngr->RegisterScene(static_cast<unsigned int>(sceneId), scenePtr);
		}

		return true;
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
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

	void CSceneModule::SetSceneManager(CSceneManager* pSceneMngr)
	{
		s_pSceneMngr = pSceneMngr;
	}

}	// namespace app
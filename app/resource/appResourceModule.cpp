/*!
* @file		appResourceModule.cpp
* @brief	リソースモジュール
* @date		2020-07-22
* @author	s.fukami
*/

#include "appResourceModule.h"
#include "appResourceSystem.h"

namespace app
{
	CResourceSystem* CResourceModule::s_pResSys = nullptr;

	bool CResourceModule::LoadResource(
		const char* fileName, eResourceMemoryType resMemType, const void* pBuildParam, ng::IResourceHandle& handle
		)
	{
		if(!_isValid()) return false;

		return s_pResSys->LoadResource(fileName, resMemType, pBuildParam, handle);
	}

	void CResourceModule::SetResourceSystem(CResourceSystem* pResSys)
	{
		s_pResSys = pResSys;
	}

	bool CResourceModule::_isValid()
	{
		return (s_pResSys != nullptr);
	}

}	// namespace app
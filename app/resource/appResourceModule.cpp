/*!
* @file		appResourceModule.cpp
* @brief	リソースモジュール
* @date		2020-07-22
* @author	s.fukami
*/

#include "appResourceModule.h"

namespace app
{
	CResourceSystem* CResourceModule::s_pResSys = nullptr;

	void CResourceModule::SetResourceSystem(CResourceSystem* pResSys)
	{
		s_pResSys = pResSys;
	}

	bool CResourceModule::_isValid()
	{
		return (s_pResSys != nullptr);
	}

}	// namespace app
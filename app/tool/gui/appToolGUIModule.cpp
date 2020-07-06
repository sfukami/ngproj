/*!
* @file		appToolGUIModule.cpp
* @brief	ツールGUI機能
* @date		2020-07-06
* @author	s.fukami
*/

#include "appToolGUIModule.h"
#include "appToolGUI.h"

namespace app
{
	CToolGUI* CToolGUIModule::s_pToolGUI = nullptr;

	void CToolGUIModule::RenderToolGUI()
	{
		if(_isValid()) {
			s_pToolGUI->Render();
		}
	}

	void CToolGUIModule::SetToolGUI(CToolGUI* pToolGUI)
	{
		s_pToolGUI = pToolGUI;
	}

	bool CToolGUIModule::_isValid()
	{
		return (s_pToolGUI != nullptr);
	}

}	// namespace app
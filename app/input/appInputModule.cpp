/*!
* @file		appInputModule.cpp
* @brief	入力機能
* @date		2020-07-01
* @author	s.fukami
*/

#include "appInputModule.h"
#include "appInput.h"

namespace app
{
	CInput* CInputModule::s_pInput = nullptr;

	bool CInputModule::CheckKeyboardInput(
		ng::eKeyCode code,
		ng::eInputState state
		)
	{
		if(_isValid()) {
			return s_pInput->CheckKeyboardInput(code, state);
		}

		return false;
	}

	bool CInputModule::CheckMouseInput(
		ng::eMouseCode code,
		ng::eInputState state
		)
	{
		if(_isValid()) {
			return s_pInput->CheckMouseInput(code, state);
		}

		return false;
	}

	void CInputModule::SetInput(CInput* pInput)
	{
		s_pInput = pInput;
	}

	bool CInputModule::_isValid()
	{
		return (s_pInput != nullptr);
	}

}	// namespace app
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

	ng::Point CInputModule::GetCursorClientPos()
	{
		if(_isValid()) {
			return s_pInput->GetCursorClientPos();
		}

		return ng::Point::ZERO;
	}

	ng::Point CInputModule::GetMoveDelta()
	{
		if(_isValid()) {
			return s_pInput->GetMoveDelta();
		}

		return ng::Point::ZERO;
	}

	ng::s32 CInputModule::GetWheelDelta()
	{
		if(_isValid()) {
			return s_pInput->GetWheelDelta();
		}

		return 0;
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
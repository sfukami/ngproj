/*!
* @file		appSceneInputTest.cpp
* @brief	シーン 入力テスト
* @date		2020-06-30
* @author	s.fukami
*/

#include "app/common/appCommon.h"
#include "appSceneInputTest.h"
#include "../../input/appInputModule.h"

namespace app
{
	CSceneInputTest::CSceneInputTest()
	{
	}
	CSceneInputTest::~CSceneInputTest()
	{
	}

	bool CSceneInputTest::Initialize()
	{
		return true;
	}

	void CSceneInputTest::Update(float deltaTime)
	{
		// Keyboard
		if(CInputModule::IsValidKeyboard()) {
			if(CInputModule::CheckKeyboardInput(ng::eKeyCode::Z, ng::eInputState::PRESSED)) {
				ng::DPrintf("key Z pressed.\n");
			}
			if(CInputModule::CheckKeyboardInput(ng::eKeyCode::Z, ng::eInputState::RELEASED)) {
				ng::DPrintf("key Z released.\n");
			}
			if(CInputModule::CheckKeyboardInput(ng::eKeyCode::Z, ng::eInputState::HELD)) {
				ng::DPrintf("key Z held.\n");
			}
		}

		// Mouse
		if(CInputModule::IsValidMouse()) {
			ng::Point cursorPos = CInputModule::GetMouseCursorClientPos();
		
			if(CInputModule::CheckMouseInput(ng::eMouseCode::LEFT, ng::eInputState::PRESSED)) {
				ng::DPrintf("button Left pressed. (%d,%d)\n", cursorPos.x, cursorPos.y);
			}
			if(CInputModule::CheckMouseInput(ng::eMouseCode::LEFT, ng::eInputState::RELEASED)) {
				ng::DPrintf("button Left released. (%d,%d)\n", cursorPos.x, cursorPos.y);
			}
			if(CInputModule::CheckMouseInput(ng::eMouseCode::LEFT, ng::eInputState::HELD)) {
				ng::DPrintf("button Left held. (%d,%d)\n", cursorPos.x, cursorPos.y);
			}
		}
	}

	void CSceneInputTest::Render()
	{
	}

	void CSceneInputTest::Finalize()
	{
	}

}	// namespace app
/*!
* @file		appInput.cpp
* @brief	アプリケーション入力
* @date		2020-06-24
* @author	s.fukami
*/

#include "ngLibApp/input/ngInputManager.h"
#include "appInput.h"

namespace app
{
	CInput::CInput()
	{
	}
	CInput::~CInput()
	{
	}

	bool CInput::Initialize(
		HWND hWnd
		)
	{
		// シングルトンインスタンス生成
		ng::CInputManager::CreateInstance();

		// Directインプット セットアップ
		{
			// Directインプット生成
			if(NG_FAILED(m_dinput.Create())) {
				NG_ERRLOG("Game", "Directインプットの生成に失敗しました.");
				return false;
			}
			// DirectInputキーボードのセットアップ
			if(NG_FAILED(m_dinput.SetupKeyboard(
				hWnd,
				DISCL_NONEXCLUSIVE | DISCL_FOREGROUND | DISCL_NOWINKEY
				))) {
				NG_ERRLOG("Game", "DirectInputキーボードのセットアップに失敗しました.");
				return false;
			}
			// DirectInputマウスのセットアップ
			if(NG_FAILED(m_dinput.SetupMouse(
				hWnd,
				DISCL_NONEXCLUSIVE | DISCL_FOREGROUND
				))) {
				NG_ERRLOG("Game", "DirectInputマウスのセットアップに失敗しました.");
				return false;
			}
		}

		// 入力管理へ割り当て
		ng::CInputManager::GetInstance().AssignInput(&m_dinput);

		return true;
	}

	void CInput::Finalize()
	{
		// Directインプット 破棄
		m_dinput.Destroy();

		// 入力管理から割り当て解除
		ng::CInputManager::GetInstance().UnassignInput();

		// シングルトンインスタンス破棄
		ng::CInputManager::DestroyInstance();
	}

	void CInput::Update()
	{
		ng::CInputManager::GetInstance().Update();
	}

	bool CInput::CheckKeyboardInput(
		ng::eKeyCode code,
		ng::eInputState state
		) const
	{
		return ng::CInputManager::GetInstance().CheckKeyboardInput(code, state);
	}

	bool CInput::CheckMouseInput(
		ng::eMouseCode code,
		ng::eInputState state
		) const
	{
		return ng::CInputManager::GetInstance().CheckMouseInput(code, state);
	}

	ng::Point CInput::GetMouseCursorClientPos() const
	{
		return ng::CInputManager::GetInstance().GetMouseCursorClientPos();
	}

	ng::Point CInput::GetMouseMoveDelta() const
	{
		return ng::CInputManager::GetInstance().GetMouseMoveDelta();
	}

	ng::s32 CInput::GetMouseWheelDelta() const
	{
		return ng::CInputManager::GetInstance().GetMouseWheelDelta();
	}

	bool CInput::IsValidKeyboard() const
	{
		return ng::CInputManager::GetInstance().IsValidKeyboard();
	}

	bool CInput::IsValidMouse() const
	{
		return ng::CInputManager::GetInstance().IsValidMouse();
	}

}	// namespace app
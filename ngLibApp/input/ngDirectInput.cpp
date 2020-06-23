/*!
* @file		ngDirectInput.cpp
* @brief	Directインプット
* @date		2019-08-09
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "ngLibCore/dx/ngDXCommon.h"
#include "ngDirectInput.h"

namespace ng
{
	CDirectInput::CDirectInput()
		: m_pIInput(nullptr)
	{
	}
	CDirectInput::~CDirectInput()
	{
		Destroy();
	}

	NG_ERRCODE CDirectInput::Create()
	{
		Destroy();
		
		// DirectInput8 生成
		NG_ERRCODE ret = DirectInput8Create(
			::GetModuleHandle(0),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(LPVOID*)&m_pIInput,
			nullptr
			);
		if(NG_FAILED(ret)) {
			NG_DXERR(ret, DirectInput8Create, "DirectInput8の生成に失敗");
			return ret;
		}

		return ret;
	}

	NG_ERRCODE CDirectInput::SetupKeyboard(HWND hWnd, DWORD cooperativeLevel)
	{
		if(!IsValid()) {
			NG_ERRMSG("DirectInput", "Directインプットが有効でないため、DirectInputキーボードのセットアップに失敗しました");
			return eNG_E_FAIL;
		}

		// DirectInputキーボード セットアップ
		NG_ERRCODE ret = m_keyboard.Setup(m_pIInput, hWnd, cooperativeLevel);

		if(NG_FAILED(ret)) {
			NG_ERRLOG(ret, "DirectInputキーボードのセットアップに失敗");
			return ret;
		}

		return ret;
	}

	void CDirectInput::Update()
	{
		m_keyboard.Poll();
	}

	void CDirectInput::Destroy()
	{
		m_keyboard.Shutdown();

		NG_SAFE_RELEASE(m_pIInput);
	}

	bool CDirectInput::IsValid() const
	{
		return (m_pIInput != nullptr);
	}

	bool CDirectInput::CheckKeyboardInput(
		eKeyCode code,
		eInputState state
		) const
	{
		return m_keyboard.CheckInputState(code, state);
	}

	IDirectInput8* CDirectInput::Interface()
	{
		return m_pIInput;
	}
	const IDirectInput8* CDirectInput::Interface() const
	{
		return m_pIInput;
	}

}	// namespace ng
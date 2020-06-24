/*!
* @file		ngDIMouse.cpp
* @brief	DirectInput マウス入力
* @date		2019-08-10
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "ngLibCore/dx/ngDXCommon.h"
#include "ngDIMouse.h"

namespace ng
{
	CDIMouse::CDIMouse()
		: m_pIDIDevice(nullptr)
	{
	}
	CDIMouse::~CDIMouse()
	{
		Shutdown();
	}

	NG_ERRCODE CDIMouse::Setup(IDirectInput8* pIDirectInput8, HWND hWnd, DWORD cooperativeLevel)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		if(pIDirectInput8 == nullptr) {
			NG_ERRLOG("DIMouse", "DirectInput8 インターフェースが無効です.");
			return eNG_E_FAIL;
		}

		Shutdown();

		// DirectInput8デバイス生成
		ret = pIDirectInput8->CreateDevice(
			GUID_SysMouse,
			&m_pIDIDevice,
			nullptr
			);
		if(NG_FAILED(ret)) {
			NG_DXERRLOG("DIMouse", ret, CreateDevice, "DirectInput8Deviceの生成に失敗しました.");
			return ret;
		}

		// デバイスのデータフォーマットをマウスに設定
		ret = m_pIDIDevice->SetDataFormat(&c_dfDIMouse2);
		if(NG_FAILED(ret)) {
			NG_DXERRLOG("DIMouse", ret, SetDataFormat, "入力デバイスのデータフォーマット設定に失敗しました.");
			return ret;
		}

		// デバイスの強調レベルを設定
		ret = m_pIDIDevice->SetCooperativeLevel(
			hWnd,
			cooperativeLevel
			);
		if(NG_FAILED(ret)) {
			NG_DXERRLOG("DIMouse", ret, SetCooperativeLevel, "入力デバイスの協調レベル設定に失敗しました.");
			return ret;
		}

		// デバイスの動作プロパティ設定
		{
			DIPROPDWORD diprop;
			diprop.diph.dwSize			= sizeof(diprop);
			diprop.diph.dwHeaderSize	= sizeof(diprop.diph);
			diprop.diph.dwObj			= 0;
			diprop.diph.dwHow			= DIPH_DEVICE;
			diprop.dwData				= DIPROPAXISMODE_REL;	// 相対値モードで設定（絶対値はDIPROPAXISMODE_ABS）
			if(NG_FAILED(ret = m_pIDIDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph))) {
				NG_DXERRLOG("DIMouse", ret, SetProperty, "入力デバイスの動作プロパティ設定に失敗しました.");
				return ret;
			}
		}

		m_hWnd = hWnd;

		return ret;
	}

	void CDIMouse::Shutdown()
	{
		if(IsValid()) {
			m_pIDIDevice->Unacquire();
			NG_SAFE_RELEASE(m_pIDIDevice);
		}
	}

	void CDIMouse::Poll()
	{
		if(!IsValid()) return;

		// デバイスのアクセス権を取得
		// DIERR_INPUTLOST で他のアプリケーションで占有されているか、デバイスロストしている
		NG_ERRCODE err = m_pIDIDevice->Acquire();

		if(err == DI_OK || err == eNG_S_FALSE) {
			m_mouseState.Swap();
			m_pIDIDevice->GetDeviceState(sizeof(DIMOUSESTATE2), m_mouseState.pCurrState);
		}
	}

	bool CDIMouse::CheckInputState(
		eMouseCode code,
		eInputState state
		) const
	{
		if(!IsValid()) return false;

		bool isPrev = _chkFlagOn( m_mouseState.GetPrev(code) );
		bool isCurr = _chkFlagOn( m_mouseState.GetCurr(code) );

		if(isPrev && isCurr)		return (state & eInputState::HELD) != 0;
		else if(!isPrev && isCurr)	return (state & eInputState::PRESSED) != 0;
		else if(isPrev && !isCurr)	return (state & eInputState::RELEASED) != 0;

		return (state & eInputState::NONE) != 0;
	}

	Point CDIMouse::GetCursorClientPos() const
	{
		if(!IsValid()) return Point::ZERO;
		
		Point pos;
		{
			POINT pt;
			if(::GetCursorPos(&pt)) {
				if(::ScreenToClient(m_hWnd, &pt)) {
					pos.x = pt.x;
					pos.y = pt.y;
				}
			}
		}

		return pos;
	}

	Point CDIMouse::GetMoveDelta() const
	{
		if(!IsValid()) return Point::ZERO;
		
		return Point(
			m_mouseState.pCurrState->lX,
			m_mouseState.pCurrState->lY
			);
	}

	s32 CDIMouse::GetWheelDelta() const
	{
		if(!IsValid()) return 0;

		return m_mouseState.pCurrState->lZ;
	}

	bool CDIMouse::IsValid() const
	{
		return (m_pIDIDevice != nullptr);
	}

	IDirectInputDevice8* CDIMouse::Interface()
	{
		return m_pIDIDevice;
	}
	const IDirectInputDevice8* CDIMouse::Interface() const
	{
		return m_pIDIDevice;
	}

	bool CDIMouse::_chkFlagOn(BYTE flag) const
	{
		return (flag & 0x80);
	}

	CDIMouse::MouseState::MouseState()
		: pCurrState(&state[0])
		, pPrevState(&state[1])
	{
		NG_ZERO_MEMORY(state, sizeof(state));
	}

	BYTE CDIMouse::MouseState::GetCurr(eMouseCode code) const
	{
		return GetFlag(*pCurrState, code);
	}

	BYTE CDIMouse::MouseState::GetPrev(eMouseCode code) const
	{
		return GetFlag(*pPrevState, code);
	}

	BYTE CDIMouse::MouseState::GetFlag(const DIMOUSESTATE2& state, eMouseCode code) const
	{
		NG_ASSERT(static_cast<u32>(code) < (u32)NG_ARRAY_SIZE(state.rgbButtons), "入力コードが範囲外です.");
		return state.rgbButtons[ static_cast<u32>(code) ];
	}

	void CDIMouse::MouseState::Swap()
	{
		DIMOUSESTATE2* temp = pPrevState;
		pPrevState = pCurrState;
		pCurrState = temp;
	}

}	// namespace ng
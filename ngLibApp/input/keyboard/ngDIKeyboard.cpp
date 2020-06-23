/*!
* @file		ngDIKeyboard.cpp
* @brief	DirectInputキーボード入力
* @date		2019-08-08
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "ngLibCore/dx/ngDXCommon.h"
#include "ngDIKeyboard.h"

namespace ng
{
	CDIKeyboard::CDIKeyboard()
		: m_pIDIDevice(nullptr)
	{
	}
	CDIKeyboard::~CDIKeyboard()
	{
		Shutdown();
	}

	NG_ERRCODE CDIKeyboard::Setup(IDirectInput8* pIDirectInput8, HWND hWnd, DWORD cooperativeLevel)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		if(pIDirectInput8 == nullptr) {
			NG_ERRLOG("DIKeyboard", "DirectInput8 インターフェースが無効です.");
			return eNG_E_FAIL;
		}

		Shutdown();

		// DirectInput8デバイス生成
		ret = pIDirectInput8->CreateDevice(
			GUID_SysKeyboard,
			&m_pIDIDevice,
			nullptr
			);
		if(NG_FAILED(ret)) {
			NG_DXERR("DIKeyboard", ret, CreateDevice, "DirectInput8Deviceの生成に失敗しました.");
			return ret;
		}

		// デバイスのデータフォーマットをキーボードに設定
		ret = m_pIDIDevice->SetDataFormat(&c_dfDIKeyboard);
		if(NG_FAILED(ret)) {
			NG_DXERR("DIKeyboard", ret, SetDataFormat, "入力デバイスのデータフォーマット設定に失敗しました.");
			return ret;
		}

		// デバイスの強調レベルを設定
		ret = m_pIDIDevice->SetCooperativeLevel(
			hWnd,
			cooperativeLevel
			);
		if(NG_FAILED(ret)) {
			NG_DXERR("DIKeyboard", ret, SetCooperativeLevel, "入力デバイスの協調レベル設定に失敗しました.");
			return ret;
		}

		// ※ウィンドウフォーカスが外れている場合に失敗となる
		// ※デバッグを考慮しエラーとしない
		/*
		ret = m_pIDIDevice->Acquire();
		if(NG_FAILED(ret)) {
			NG_DXERR("DIKeyboard", ret, Acquire, "入力デバイスのアクセス権取得に失敗しました.");
			return ret;
		}
		*/

		return ret;
	}

	void CDIKeyboard::Shutdown()
	{
		if(IsValid()) {
			m_pIDIDevice->Unacquire();
			NG_SAFE_RELEASE(m_pIDIDevice);
		}
	}

	void CDIKeyboard::Poll()
	{
		if(!IsValid()) return;

		// デバイスのアクセス権を取得
		// DIERR_INPUTLOST で他のアプリケーションで占有されているか、デバイスロストしている
		NG_ERRCODE err = m_pIDIDevice->Acquire();

		if(err == DI_OK || err == eNG_S_FALSE) {
			m_keyFlag.Swap();
			m_pIDIDevice->GetDeviceState(sizeof(m_keyFlag.diks[0]), m_keyFlag.pCurrDiks);
		}
	}

	bool CDIKeyboard::CheckInputState(
		eKeyCode code,
		eInputState state
		) const
	{
		if(!IsValid()) return false;

		bool isPrev = _chkFlagOn( m_keyFlag.GetPrev(code) );
		bool isCurr = _chkFlagOn( m_keyFlag.GetCurr(code) );

		if(isPrev && isCurr)		return (state & eInputState::HELD) != 0;
		else if(!isPrev && isCurr)	return (state & eInputState::PRESSED) != 0;
		else if(isPrev && !isCurr)	return (state & eInputState::RELEASED) != 0;

		return (state & eInputState::NONE) != 0;
	}

	bool CDIKeyboard::IsValid() const
	{
		return (m_pIDIDevice != nullptr);
	}

	IDirectInputDevice8* CDIKeyboard::Interface()
	{
		return m_pIDIDevice;
	}
	const IDirectInputDevice8* CDIKeyboard::Interface() const
	{
		return m_pIDIDevice;
	}

	bool CDIKeyboard::_chkFlagOn(BYTE flag) const
	{
		return (flag & 0x80);
	}

	CDIKeyboard::KeyFlag::KeyFlag()
		: pCurrDiks(diks[0])
		, pPrevDiks(diks[1])
	{
		NG_ZERO_MEMORY(diks, sizeof(diks));
	}

	BYTE CDIKeyboard::KeyFlag::GetCurr(eKeyCode code) const
	{
		return GetFlag(pCurrDiks, code);
	}

	BYTE CDIKeyboard::KeyFlag::GetPrev(eKeyCode code) const
	{
		return GetFlag(pPrevDiks, code);
	}
	
	BYTE CDIKeyboard::KeyFlag::GetFlag(const BYTE* pDiks, eKeyCode code) const
	{
		NG_ASSERT(UnderlyingCast(code) < KEYCODE_MAX, "入力コードが範囲外です.");
		return pDiks[ UnderlyingCast(code) ];
	}

	void CDIKeyboard::KeyFlag::Swap()
	{
		BYTE* temp = pPrevDiks;
		pPrevDiks = pCurrDiks;
		pCurrDiks = temp;
	}

}	// namespace ng
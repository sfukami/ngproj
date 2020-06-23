/*!
* @file		ngDIKeyboard.h
* @brief	DirectInputキーボード入力
* @date		2019-08-08
* @author	s.fukami
*/

#ifndef __NG_APP_DI_KEYBOARD_H__
#define __NG_APP_DI_KEYBOARD_H__

#include "../ngInputCode.h"
#include "../ngInputState.h"

struct IDirectInput8;
struct IDirectInputDevice8;

namespace ng
{
	/*!
	* @brief					DirectInputキーボード入力
	*/
	class NG_DECL CDIKeyboard
	{
	public:
		CDIKeyboard();
		~CDIKeyboard();

		/*!
		* @brief					セットアップ
		* @param DInput				DirectInput8 インターフェース
		* @param hWnd				ウィンドウハンドル
		* @param cooperativeLevel	協調レベル
		* @return					NG エラーコード
		*/
		NG_ERRCODE Setup(IDirectInput8* pIDirectInput8, HWND hWnd, DWORD cooperativeLevel);

		/*!
		* @brief					終了処理
		*/
		void Shutdown();

		/*!
		* @brief					入力状態更新
		*/
		void Poll();

		/*!
		* @brief					キー入力状態チェック
		* @param code				入力コード
		* @param state				チェックする入力状態
		*/
		bool CheckInputState(
			eKeyCode code,
			eInputState state
			) const;

		/*!
		* @brief					有効か
		*/
		bool IsValid() const;

		/*!
		* @brief					DirectInput8デバイス インターフェース取得
		*/
		IDirectInputDevice8* Interface();
		const IDirectInputDevice8* Interface() const;

	private:
		/*! 入力が有効かチェック */
		bool _chkFlagOn(BYTE flag) const;

	private:
		static const int KEYCODE_MAX = 256;		//!< キーコード数

		/*! キー入力フラグ */
		struct KeyFlag
		{
			KeyFlag();
			BYTE GetCurr(eKeyCode code) const;
			BYTE GetPrev(eKeyCode code) const;
			BYTE GetFlag(const BYTE* pDiks, eKeyCode code) const;
			void Swap();

			BYTE diks[2][KEYCODE_MAX];
			BYTE *pCurrDiks, *pPrevDiks;
		};

	private:
		IDirectInputDevice8* m_pIDIDevice;	//!< DirectInput8デバイス インターフェース

		KeyFlag m_keyFlag;		//!< キー入力フラグ
	};

}	// namespace ng

#endif	// __NG_APP_DI_KEYBOARD_H__
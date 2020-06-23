/*!
* @file		ngDirectInput.h
* @brief	Directインプット
* @date		2019-08-09
* @author	s.fukami
*/

#ifndef __NG_APP_DIRECT_INPUT_H__
#define __NG_APP_DIRECT_INPUT_H__

#include <dinput.h>
#include "ngInput.h"
#include "keyboard/ngDIKeyboard.h"
#include "mouse/ngDIMouse.h"

struct IDirectInput8;

namespace ng
{
	enum class eKeyCode : u32;
	enum class eMouseCode : u32;
	enum class eInputState : u32;
}

namespace ng
{
	/*!
	* @brief					Directインプット
	*/
	class NG_DECL CDirectInput : public IInput
	{
	public:
		CDirectInput();
		~CDirectInput();

		/*!
		* @brief					Directインプット生成
		* @return					NG エラーコード
		*/
		NG_ERRCODE Create();

		/*!
		* @brief					DirectInputキーボード セットアップ
		* @param hWnd				ウィンドウハンドル
		* @param cooperativeLevel	協調レベル
		* @return					NG エラーコード
		*/
		NG_ERRCODE SetupKeyboard(HWND hWnd, DWORD cooperativeLevel);

		/*!
		* @brief					DirectInputマウス セットアップ
		* @param hWnd				ウィンドウハンドル
		* @param cooperativeLevel	協調レベル
		* @return					NG エラーコード
		*/
		NG_ERRCODE SetupMouse(HWND hWnd, DWORD cooperativeLevel);

		/*!
		* @brief					更新
		*/
		void Update();

		/*!
		* @brief					破棄
		*/
		void Destroy();

		/*!
		* @brief					キーボード入力状態チェック
		* @param code				入力コード
		* @param state				チェックする入力状態
		*/
		bool CheckKeyboardInput(
			eKeyCode code,
			eInputState state
			) const;

		/*!
		* @brief					マウス入力状態チェック
		* @param code				入力コード
		* @param state				チェックする入力状態
		*/
		bool CheckMouseInput(
			eMouseCode code,
			eInputState state
			) const;

		/*!
		* @brief					有効か
		*/
		bool IsValid() const;

		/*!
		* @brief					DirectInput8 インターフェース取得
		*/
		IDirectInput8* Interface();
		const IDirectInput8* Interface() const;

	private:
		IDirectInput8* m_pIInput;	//!< DirectInput8 インターフェース

		CDIKeyboard m_keyboard;		//!< DirectInputキーボード
		CDIMouse m_mouse;			//!< DirectInputマウス
	};

}	// namespace ng

#endif	// __NG_APP_DIRECT_INPUT_H__
/*!
* @file		appInput.h
* @brief	アプリケーション入力
* @date		2020-06-24
* @author	s.fukami
*/

#ifndef __APP_INPUT_H__
#define __APP_INPUT_H__

#include "ngLibApp/input/ngDirectInput.h"
#include "ngLibApp/input/ngInputCode.h"
#include "ngLibApp/input/ngInputState.h"

namespace app
{
	/*!
	* @brief					アプリケーション入力
	*/
	class CInput
	{
	public:
		CInput();
		~CInput();

		/*!
		* @brief					初期化
		* @param hWnd				ウィンドウハンドル
		* @return					成否
		*/
		bool Initialize(
			HWND hWnd
			);

		/*!
		* @brief					終了処理
		*/
		void Finalize();

		/*!
		* @brief					更新
		*/
		void Update();

		/*!
		* @brief					キーボード入力状態チェック
		* @param code				入力コード
		* @param state				チェックする入力状態
		*/
		bool CheckKeyboardInput(
			ng::eKeyCode code,
			ng::eInputState state
			) const;

		/*!
		* @brief					マウス入力状態チェック
		* @param code				入力コード
		* @param state				チェックする入力状態
		*/
		bool CheckMouseInput(
			ng::eMouseCode code,
			ng::eInputState state
			) const;

	private:
		ng::CDirectInput m_dinput;	//!< Directインプット
	};

}	// namespace ng

#endif	// __APP_INPUT_H__
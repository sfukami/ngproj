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

		/*!
		* @brief					クライアント座標におけるマウスカーソルの座標を取得
		* @return					マウスカーソルの座標
		*/
		ng::Point GetCursorClientPos() const;

		/*!
		* @brief					マウスカーソルの相対的な移動量を取得
		* @return					マウスカーソルの移動量（ピクセル）
		*/
		ng::Point GetMoveDelta() const;

		/*!
		* @brief					マウスホイールの相対的な変化量を取得
		* @return					マウスホイールの変化量
		*/
		ng::s32 GetWheelDelta() const;

	private:
		ng::CDirectInput m_dinput;	//!< Directインプット
	};

}	// namespace ng

#endif	// __APP_INPUT_H__
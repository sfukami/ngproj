/*!
* @file		appInputModule.h
* @brief	入力機能
* @date		2020-07-01
* @author	s.fukami
*/

#ifndef __APP_INPUT_MODULE_H__
#define __APP_INPUT_MODULE_H__

#include "ngLibCore/traits/ngNonInstantiable.h"
#include "ngLibCore/geometry/point/ngPoint.h"
#include "ngLibApp/input/ngInputCode.h"
#include "ngLibApp/input/ngInputState.h"

namespace app
{
	class CInput;
}

namespace app
{
	/*!
	* @brief					入力機能
	*/
	class CInputModule : public ng::CNonInstantiable
	{
		friend class CGame;

	public:
		/*!
		* @brief					キーボード入力状態チェック
		* @param code				入力コード
		* @param state				チェックする入力状態
		*/
		static bool CheckKeyboardInput(
			ng::eKeyCode code,
			ng::eInputState state
			);

		/*!
		* @brief					マウス入力状態チェック
		* @param code				入力コード
		* @param state				チェックする入力状態
		*/
		static bool CheckMouseInput(
			ng::eMouseCode code,
			ng::eInputState state
			);

		/*!
		* @brief					クライアント座標におけるマウスカーソルの座標を取得
		* @return					マウスカーソルの座標
		*/
		static ng::Point GetMouseCursorClientPos();

		/*!
		* @brief					マウスカーソルの相対的な移動量を取得
		* @return					マウスカーソルの移動量（ピクセル）
		*/
		static ng::Point GetMouseMoveDelta();

		/*!
		* @brief					マウスホイールの相対的な変化量を取得
		* @return					マウスホイールの変化量
		*/
		static ng::s32 GetMouseWheelDelta();

		/*!
		* @brief					キーボードが有効か
		*/
		static bool IsValidKeyboard();

		/*!
		* @brief					マウスが有効か
		*/
		static bool IsValidMouse();

	private:
		/*! 入力のインスタンスを設定 */
		static void SetInput(CInput* pInput);

		/*! 有効か */
		static bool _isValid();
		
	private:
		static CInput* s_pInput;	//!< 入力への参照
	};

}	// namespace app

#endif	// __APP_INPUT_MODULE_H__
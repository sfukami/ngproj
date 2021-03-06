﻿/*!
* @file		ngInputManager.h
* @brief	デバイス入力管理
* @date		2020-06-23
* @author	s.fukami
*/

#ifndef __NG_APP_INPUT_MANAGER_H__
#define __NG_APP_INPUT_MANAGER_H__

#include "ngLibCore/traits/ngSingleton.h"
#include "ngLibCore/geometry/point/ngPoint.h"

namespace ng
{
	class IInput;
	enum class eKeyCode : u32;
	enum class eMouseCode : u32;
	enum class eInputState : u32;
}

namespace ng
{
	/*!
	* @brief					デバイス入力管理
	*/
	class NG_DECL CInputManager : public CSingleton<CInputManager>
	{
		NG_SINGLETON(CInputManager);

	private:
		CInputManager();
		~CInputManager();

	public:
		/*!
		* @brief					デバイス入力割り当て
		*/
		void AssignInput(IInput* pInput);

		/*!
		* @brief					更新
		*/
		void Update();

		/*!
		* @brief					デバイス入力割り当て解除
		*/
		void UnassignInput();

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
		* @brief					クライアント座標におけるマウスカーソルの座標を取得
		* @return					マウスカーソルの座標
		*/
		Point GetMouseCursorClientPos() const;

		/*!
		* @brief					マウスカーソルの相対的な移動量を取得
		* @return					マウスカーソルの移動量（ピクセル）
		*/
		Point GetMouseMoveDelta() const;

		/*!
		* @brief					マウスホイールの相対的な変化量を取得
		* @return					マウスホイールの変化量
		*/
		s32 GetMouseWheelDelta() const;

		/*!
		* @brief					キーボードが有効か
		*/
		bool IsValidKeyboard() const;

		/*!
		* @brief					マウスが有効か
		*/
		bool IsValidMouse() const;

		/*!
		* @brief					デバイス入力が割り当て済みか
		*/
		bool IsAssigned() const;

	private:
		static CInputManager m_instance;	//!< デバイス入力管理 インスタンス

	private:
		IInput* m_pInput;	//!< デバイス入力
	};

}	// namespace ng

#endif	// __NG_APP_INPUT_MANAGER_H__
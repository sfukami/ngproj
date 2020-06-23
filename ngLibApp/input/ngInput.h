/*!
* @file		ngInput.h
* @brief	デバイス入力 インターフェース
* @date		2020-06-23
* @author	s.fukami
*/

#ifndef __NG_APP_INPUT_H__
#define __NG_APP_INPUT_H__

namespace ng
{
	class IKeyboard;
	enum class eKeyCode : u32;
	enum class eMouseCode : u32;
	enum class eInputState : u32;
}

namespace ng
{
	/*!
	* @brief					デバイス入力 インターフェース
	*/
	class NG_DECL IInput
	{
	public:
		/*!
		* @brief					更新
		*/
		virtual void Update() = 0;

		/*!
		* @brief					キーボード入力状態チェック
		* @param code				入力コード
		* @param state				チェックする入力状態
		*/
		virtual bool CheckKeyboardInput(
			eKeyCode code,
			eInputState state
			) const = 0;

		/*!
		* @brief					マウス入力状態チェック
		* @param code				入力コード
		* @param state				チェックする入力状態
		*/
		virtual bool CheckMouseInput(
			eMouseCode code,
			eInputState state
			) const = 0;
	};

}	// namespace ng

#endif	// __NG_APP_INPUT_H__
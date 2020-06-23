/*!
* @file		ngDIMouse.h
* @brief	DirectInput マウス入力
* @date		2019-08-10
* @author	s.fukami
*/

#ifndef __NG_APP_DI_MOUSE_H__
#define __NG_APP_DI_MOUSE_H__

#include "../ngInputCode.h"
#include "../ngInputState.h"
#include "ngLibCore/geometry/point/ngPoint.h"

struct IDirectInput8;
struct IDirectInputDevice8;

namespace ng
{
	/*!
	* @brief					DirectInputマウス入力
	*/
	class NG_DECL CDIMouse
	{
	public:
		CDIMouse();
		~CDIMouse();

		/*!
		* @brief					セットアップ
		* @param pIDirectInput8		DirectInput8 インターフェース
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
		* @brief					マウス入力状態チェック
		* @param code				入力コード
		* @param state				チェックする入力状態
		*/
		bool CheckInputState(
			eMouseCode code,
			eInputState state
			) const;

		/*!
		* @brief					クライアント座標におけるマウスカーソルの座標を取得
		* @return					マウスカーソルの座標
		*/
		Point GetCursorClientPos() const;

		/*!
		* @brief					マウスカーソルの相対的な移動量を取得
		* @return					マウスカーソルの移動量（ピクセル）
		*/
		Point GetMoveDelta() const;

		/*!
		* @brief					マウスホイールの相対的な変化量を取得
		* @return					マウスホイールの変化量
		*/
		s32 GetWheelDelta() const;

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
		/*! マウス入力状態 */
		struct MouseState
		{
			MouseState();
			BYTE GetCurr(eMouseCode code) const;
			BYTE GetPrev(eMouseCode code) const;
			BYTE GetFlag(const DIMOUSESTATE2& state, eMouseCode code) const;
			void Swap();

			DIMOUSESTATE2 state[2];
			DIMOUSESTATE2 *pCurrState, *pPrevState;
		};

	private:
		HWND m_hWnd;		//!< ウィンドウハンドル
		IDirectInputDevice8* m_pIDIDevice;	//!< DirectInput8デバイス インターフェース
		MouseState m_mouseState;		//!< マウス入力状態
	};

}	// namespace ng

#endif	// __NG_APP_DI_MOUSE_H__
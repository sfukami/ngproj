/*!
* @file		ngInputState.h
* @brief	入力状態定義
* @date		2019-08-08
* @author	s.fukami
*/

#ifndef __NG_APP_INPUT_STATE_H__
#define __NG_APP_INPUT_STATE_H__

namespace ng
{
	/*!
	* @brief					入力状態
	*/
	enum class eInputState : u32
	{
		NONE		= NG_BIT(0),	//!< 入力無し
		PRESSED		= NG_BIT(1),	//!< 押した瞬間
		RELEASED	= NG_BIT(2),	//!< 離した瞬間
		HELD		= NG_BIT(3),	//!< 押下中
	};
	NG_ENUM_BITFLAG_OP(eInputState);

}	// namespace ng

#endif	// __NG_APP_INPUT_STATE_H__
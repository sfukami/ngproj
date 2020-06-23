/*!
* @file		ngInputCode.h
* @brief	入力コード
* @date		2019-08-09
* @author	s.fukami
*/

#ifndef __NG_APP_INPUT_CODE_H__
#define __NG_APP_INPUT_CODE_H__

#include <dinput.h>

namespace ng
{
	/*!
	* @brief					入力コード キーボード
	*/
	enum class eKeyCode : u32
	{
		INVALID			= 0					,	// 無効な入力
		ESCAPE			= DIK_ESCAPE		,
		NUM_1			= DIK_1				,
		NUM_2			= DIK_2				,
		NUM_3			= DIK_3				,
		NUM_4			= DIK_4				,
		NUM_5			= DIK_5				,
		NUM_6			= DIK_6				,
		NUM_7			= DIK_7				,
		NUM_8			= DIK_8				,
		NUM_9			= DIK_9				,
		NUM_0			= DIK_0				,
		MINUS			= DIK_MINUS			,			/* - on main keyboard */
		EQUALS			= DIK_EQUALS		,
		BACK			= DIK_BACK			,			/* backspace */
		TAB				= DIK_TAB			,
		Q				= DIK_Q				,
		W				= DIK_W				,
		E				= DIK_E				,
		R				= DIK_R				,
		T				= DIK_T				,
		Y				= DIK_Y				,
		U				= DIK_U				,
		I				= DIK_I				,
		O				= DIK_O				,
		P				= DIK_P				,
		LBRACKET		= DIK_LBRACKET		,
		RBRACKET		= DIK_RBRACKET		,
		RETURN			= DIK_RETURN		,			/* Enter on main keyboard */
		LCONTROL		= DIK_LCONTROL		,
		A				= DIK_A				,
		S				= DIK_S				,
		D				= DIK_D				,
		F				= DIK_F				,
		G				= DIK_G				,
		H				= DIK_H				,
		J				= DIK_J				,
		K				= DIK_K				,
		L				= DIK_L				,
		SEMICOLON		= DIK_SEMICOLON		,
		APOSTROPHE		= DIK_APOSTROPHE	,
		GRAVE			= DIK_GRAVE			,			/* accent grave */
		LSHIFT			= DIK_LSHIFT		,
		BACKSLASH		= DIK_BACKSLASH		,
		Z				= DIK_Z				,
		X				= DIK_X				,
		C				= DIK_C				,
		V				= DIK_V				,
		B				= DIK_B				,
		N				= DIK_N				,
		M				= DIK_M				,
		COMMA			= DIK_COMMA			,
		PERIOD			= DIK_PERIOD		,			/* . on main keyboard */
		SLASH			= DIK_SLASH			,			/* / on main keyboard */
		RSHIFT			= DIK_RSHIFT		,
		MULTIPLY		= DIK_MULTIPLY		,			/* * on numeric keypad */
		LMENU			= DIK_LMENU			,			/* left Alt */
		SPACE			= DIK_SPACE			,
		CAPITAL			= DIK_CAPITAL		,
		F1				= DIK_F1			,
		F2				= DIK_F2			,
		F3				= DIK_F3			,
		F4				= DIK_F4			,
		F5				= DIK_F5			,
		F6				= DIK_F6			,
		F7				= DIK_F7			,
		F8				= DIK_F8			,
		F9				= DIK_F9			,
		F10				= DIK_F10			,
		NUMLOCK			= DIK_NUMLOCK		,
		SCROLL			= DIK_SCROLL		,			/* Scroll Lock */
		NUMPAD7			= DIK_NUMPAD7		,
		NUMPAD8			= DIK_NUMPAD8		,
		NUMPAD9			= DIK_NUMPAD9		,
		SUBTRACT		= DIK_SUBTRACT		,			/* - on numeric keypad */
		NUMPAD4			= DIK_NUMPAD4		,
		NUMPAD5			= DIK_NUMPAD5		,
		NUMPAD6			= DIK_NUMPAD6		,
		ADD				= DIK_ADD			,			/* + on numeric keypad */
		NUMPAD1			= DIK_NUMPAD1		,
		NUMPAD2			= DIK_NUMPAD2		,
		NUMPAD3			= DIK_NUMPAD3		,
		NUMPAD0			= DIK_NUMPAD0		,
		DECIMAL			= DIK_DECIMAL		,			/* . on numeric keypad */
		OEM_102			= DIK_OEM_102		,			/* <> or \| on RT 102-key keyboard (Non-U.S.) */
		F11				= DIK_F11			,
		F12				= DIK_F12			,
		F13				= DIK_F13			,			/*                     (NEC PC98) */
		F14				= DIK_F14			,			/*                     (NEC PC98) */
		F15				= DIK_F15			,			/*                     (NEC PC98) */
		KANA			= DIK_KANA			,			/* (Japanese keyboard)            */
		ABNT_C1			= DIK_ABNT_C1		,			/* /? on Brazilian keyboard	*/
		CONVERT			= DIK_CONVERT		,			/* (Japanese keyboard)            */
		NOCONVERT		= DIK_NOCONVERT		,			/* (Japanese keyboard)            */
		YEN				= DIK_YEN			,			/* (Japanese keyboard)            */
		ABNT_C2			= DIK_ABNT_C2		,			/* Numpad . on Brazilian keyboard */
		NUMPADEQUALS	= DIK_NUMPADEQUALS	,			/* = on numeric keypad (NEC PC98) */
		PREVTRACK		= DIK_PREVTRACK		,			/* Previous Track (DIK_CIRCUMFLEX on Japanese keyboard) */
		AT				= DIK_AT			,			/*                     (NEC PC98) */
		COLON			= DIK_COLON			,			/*                     (NEC PC98) */
		UNDERLINE		= DIK_UNDERLINE		,			/*                     (NEC PC98) */
		KANJI			= DIK_KANJI			,			/* (Japanese keyboard)            */
		STOP			= DIK_STOP			,			/*                     (NEC PC98) */
		AX				= DIK_AX			,			/*                     (Japan AX) */
		UNLABELED		= DIK_UNLABELED		,			/*                        (J3100) */
		NEXTTRACK		= DIK_NEXTTRACK		,			/* Next Track */
		NUMPADENTER		= DIK_NUMPADENTER	,			/* Enter on numeric keypad */
		RCONTROL		= DIK_RCONTROL		,
		MUTE			= DIK_MUTE			,			/* Mute */
		CALCULATOR		= DIK_CALCULATOR	,			/* Calculator */
		PLAYPAUSE		= DIK_PLAYPAUSE		,			/* Play / Pause */
		MEDIASTOP		= DIK_MEDIASTOP		,			/* Media Stop */
		VOLUMEDOWN		= DIK_VOLUMEDOWN	,			/* Volume - */
		VOLUMEUP		= DIK_VOLUMEUP		,			/* Volume + */
		WEBHOME			= DIK_WEBHOME		,			/* Web home */
		NUMPADCOMMA		= DIK_NUMPADCOMMA	,			/* , on numeric keypad (NEC PC98) */
		DIVIDE			= DIK_DIVIDE		,			/* / on numeric keypad */
		SYSRQ			= DIK_SYSRQ			,
		RMENU			= DIK_RMENU			,			/* right Alt */
		PAUSE			= DIK_PAUSE			,			/* Pause */
		HOME			= DIK_HOME			,			/* Home on arrow keypad */
		UP				= DIK_UP			,			/* UpArrow on arrow keypad */
		PRIOR			= DIK_PRIOR			,			/* PgUp on arrow keypad */
		LEFT			= DIK_LEFT			,			/* LeftArrow on arrow keypad */
		RIGHT			= DIK_RIGHT			,			/* RightArrow on arrow keypad */
		END				= DIK_END			,			/* End on arrow keypad */
		DOWN			= DIK_DOWN			,			/* DownArrow on arrow keypad */
		NEXT			= DIK_NEXT			,			/* PgDn on arrow keypad */
		INSERT			= DIK_INSERT		,			/* Insert on arrow keypad */
		DEL				= DIK_DELETE		,			/* Delete on arrow keypad */
		// ここから255を超える
	//	LWIN			= DIK_LWIN			,			/* Left Windows key */
	//	RWIN			= DIK_RWIN			,			/* Right Windows key */
	//	APPS			= DIK_APPS			,			/* AppMenu key */
	//	POWER			= DIK_POWER			,			/* System Power */
	//	SLEEP			= DIK_SLEEP			,			/* System Sleep */
	//	WAKE			= DIK_WAKE			,			/* System Wake */
	//	WEBSEARCH		= DIK_WEBSEARCH		,			/* Web Search */
	//	WEBFAVORITES	= DIK_WEBFAVORITES	,			/* Web Favorites */
	//	WEBREFRESH		= DIK_WEBREFRESH	,			/* Web Refresh */
	//	WEBSTOP			= DIK_WEBSTOP		,			/* Web Stop */
	//	WEBFORWARD		= DIK_WEBFORWARD	,			/* Web Forward */
	//	WEBBACK			= DIK_WEBBACK		,			/* Web Back */
	//	MYCOMPUTER		= DIK_MYCOMPUTER	,			/* My Computer */
	//	MAIL			= DIK_MAIL			,			/* Mail */
	//	MEDIASELECT		= DIK_MEDIASELECT	,			/* Media Select */
	};

	/*!
	* @brief					入力コード マウス
	*/
	enum class eMouseCode : u32
	{
		LEFT		= 0,	// 左クリック
		RIGHT,				// 右クリック
		CENTER,				// 中央クリック
		BACK,				// 戻るボタン
		FOWARD,				// 進むボタン
		OPTION_0,			// その他
		OPTION_1,			// 〃
		OPTION_2,			// 〃
	};

}	// namespace ng

#endif	// __NG_APP_INPUT_CODE_H__
/*!
* @file		ngMsgBoxMacro.h
* @brief	メッセージボックスマクロ
* @date		2018-10-19
* @author	s.fukami
*/

#ifndef __NG_CORE_MSG_BOX_MACRO_H__
#define __NG_CORE_MSG_BOX_MACRO_H__

/*!
* @brief					メッセージボックス表示
* @param _message			メッセージ
* @param _caption			タイトル
* @param _style				スタイル
* @return					選択結果
*/
#ifdef UNICODE
	#define NG_MSGBOX(_message, _caption, _style)		ng::_MsgBoxW(_message, _caption, _style)
#else
	#define NG_MSGBOX(_message, _caption, _style)		ng::_MsgBoxA(_message, _caption, _style)
#endif	// UNICODE

namespace ng
{
	int _MsgBoxA(LPCSTR message, LPCSTR caption, UINT style);
	int _MsgBoxW(LPCWSTR message, LPCWSTR caption, UINT style);

}	// namespace ng

#endif	// __NG_CORE_MSG_BOX_MACRO_H__

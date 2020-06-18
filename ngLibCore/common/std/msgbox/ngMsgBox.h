/*!
* @file		ngMsgBox.h
* @brief	メッセージボックス
* @date		2018-10-19
* @author	s.fukami
*/

#ifndef __NG_CORE_MSG_BOX_H__
#define __NG_CORE_MSG_BOX_H__

namespace ng
{
	/*!
	* @brief					メッセージボックス表示
	* @param _message			メッセージ
	* @param _caption			タイトル
	* @param _style				スタイル
	* @return					選択結果
	*/
	NG_DECL int MsgBoxA(LPCSTR message, LPCSTR caption, UINT style);
	NG_DECL int MsgBoxW(LPCWSTR message, LPCWSTR caption, UINT style);

#ifdef __cplusplus
	// for C++
	NG_INLINE int MsgBox(LPCTSTR message, LPCTSTR caption, UINT style)
	{
	#ifdef UNICODE
		return MsgBoxW(message, caption, style);
	#else
		return MsgBoxA(message, caption, style);
	#endif	// UNICODE
	}
#else
	// for C
	#ifdef UNICODE
		#define MsgBox		MsgBoxW
	#else
		#define MsgBox		MsgBoxA
	#endif	// UNICODE
#endif	// __cplusplus

}	// namespace ng

#endif	// __NG_CORE_MSG_BOX_H__

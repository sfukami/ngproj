/*!
* @file		ngErrMacro.h
* @brief	エラーマクロ定義
* @date		2018-10-22
* @author	s.fukami
*/

#ifndef __NG_CORE_ERR_MACRO_H__
#define __NG_CORE_ERR_MACRO_H__

#include "ngLibCore/common/std/msgbox/ngMsgBoxMacro.h"

/*!
* @brief					エラー メッセージボックス
* @param _message			メッセージ
*/
#define NG_EMSGBOX(_message)		NG_MSGBOX(_message, _T("ErrorMessage"), MB_ICONEXCLAMATION|MB_OK)

#endif	// __NG_CORE_ERR_MACRO_H__

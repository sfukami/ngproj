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
* @brief					関数戻り値 成功判定
* @param _retCode			Enum定義 NG_ERRCODE
*/
#define NG_SUCCEEDED(_retCode)		((_retCode) >= 0)

/*!
* @brief					関数戻り値 失敗判定
*/
#define NG_FAILED(_retCode)			( ! NG_SUCCEEDED(_retCode))

/*!
* @brief					エラー メッセージボックス
* @param _message			メッセージ
*/
#define NG_EMSGBOX(_message)		NG_MSGBOX(_message, _T("ErrorMessage"), MB_ICONEXCLAMATION|MB_OK)

#endif	// __NG_CORE_ERR_MACRO_H__

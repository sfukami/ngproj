/*!
* @file		ngDebug.h
* @brief	デバッグ機能
* @date		2016-08-22
* @author	s.fukami
*/

#ifndef __NG_CORE_DEBUG_H__
#define __NG_CORE_DEBUG_H__

#include <Windows.h>

namespace ng
{
	/*!
	* @brief					ブレークポイント設定
	*/
	NG_DECL void SetBreakPoint();

	/*!
	* @brief					ハードウェアブレークポイント設定
	*/
	NG_DECL void SetHardwareBreakPoint(DWORD address);

	/*!
	* @brief					ハードウェアブレークポイント削除
	*/
	NG_DECL void ClearHardwareBreakPoint();

}	// namespace ng

#endif	// __NG_CORE_DEBUG_H__

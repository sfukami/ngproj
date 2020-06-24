/*!
* @file		ngDX12Macro.h
* @brief	DX12 マクロ
* @date		2020-06-24
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_MACRO_H__
#define __NG_GRAPHIC_DX12_MACRO_H__

#include "ngLibCore/dx/ngDXDebug.h"

/*!
* @brief					DX12デバッグレイヤー有効化
*/
#if defined(NG_DX12_DEBUG_LAYER_ENABLE)
	#define NG_DX12_ENABLE_DEBUG_LAYER()		(EnableDX12DebugLayer())
#else
	#define NG_DX12_ENABLE_DEBUG_LAYER()
#endif

/*!
* @brief					DX12ログ出力
* @param _category			カテゴリ
*/
#define NG_DX12LOG(_category, _msg, ...) \
	{ \
		NG_DPRINTF("NG_DX12LOG [%s] ", _category); \
		NG_DPRINTF(_msg, __VA_ARGS__); NG_DPRINTF_S("\n"); \
	}

#endif	// __NG_GRAPHIC_DX12_MACRO_H__
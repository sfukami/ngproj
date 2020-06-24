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

#endif	// __NG_GRAPHIC_DX12_MACRO_H__
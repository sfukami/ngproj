/*!
* @file		ngDXMacro.h
* @brief	DirectX 汎用的なマクロ定義
* @date		2017-08-29
* @author	s.fukami
*/

#ifndef __NG_DX_MACRO_H__
#define __NG_DX_MACRO_H__

/*!
* @brief					インターフェース解放
*/
#define NG_SAFE_RELEASE(_p) \
	{ \
		if(_p != nullptr) { \
			_p->Release(); \
			_p = nullptr; \
		} \
	}

/*!
* @brief					ログ出力
*/
#define NG_DXLOG(_msg, ...) \
	{ \
		NG_DPRINTF("[NG_DXLOG] "); NG_DPRINTF(_msg, __VA_ARGS__); NG_DPRINTF_S("\n"); \
	}

#endif	// __NG_DX_MACRO_H__
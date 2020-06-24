/*!
* @file		ngDXError.h
* @brief	DirectX 関数戻り値 エラーコード
* @date		2017-09-11
* @author	s.fukami
*/

#ifndef __NG_DX_ERROR_H__
#define __NG_DX_ERROR_H__

/*!
* @brief					DirectX エラーログ出力
*/
#ifdef NG_DEBUG
	#define NG_DXERRLOG(_category, _hr, _func, _msg, ...) \
		{ \
			NG_DPRINTF("(!)DXERRLOG [%s] func:%s() returned [%s](%s)\n", _category, \
				NG_TO_STRING(_func), DXErrorCodeToString(_hr), DXErrorCodeToDescription(_hr)); \
			NG_DPRINTF("\tmsg:"); NG_DPRINTF(_msg, __VA_ARGS__); NG_DPRINTF_S("\n"); \
		}
#else
	#define NG_DXERRLOG(_hr, _func, _msg, ...)
#endif

namespace ng
{
	/*!
	* @brief					NG エラーコード 文字列変換
	* @param code				エラーコード
	*/
	NG_DECL const char* DXErrorCodeToString(HRESULT hr);

	/*!
	* @brief					NG エラーコード 説明取得
	* @param code				エラーコード
	*/
	NG_DECL const char* DXErrorCodeToDescription(HRESULT hr);

}	// namespace ng

#endif	// __NG_DX_ERROR_H__
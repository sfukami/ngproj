/*!
* @file		ngErrCode.h
* @brief	関数戻り値 エラーコード
* @date		2017-08-09
* @author	s.fukami
*/

#ifndef __NG_CORE_RET_CODE_H__
#define __NG_CORE_RET_CODE_H__

#include <WinError.h>

//! NG エラーコード
#define NG_ERRCODE		HRESULT
//! NG エラーコード 重要度
#define NG_ERRCODE_SEVERITY		(1)
//! NG エラーコード 種類
#define NG_ERRCODE_FACILITY		(0x870)
//! NG エラーコード作成
#define NG_MAKE_NG_ERRCODE(_code) \
	MAKE_HRESULT(NG_ERRCODE_SEVERITY, NG_ERRCODE_FACILITY, _code)

/*!
* @brief					関数戻り値 成功判定
* @param _retCode			Enum定義 NG_ERRCODE
*/
#define NG_SUCCEEDED(_retCode)		((_retCode) >= 0)

/*!
* @brief					関数戻り値 失敗判定
*/
#define NG_FAILED(_retCode)			( ! NG_SUCCEEDED(_retCode))

namespace ng
{
	/*!
	* @brief					関数戻り値定義。NG エラーコード
	* @note						HRESULT と互換
	* 							【参考】https://msdn.microsoft.com/en-us/library/windows/desktop/aa378137(v=vs.85).aspx
	* 							成否判定はマクロ NG_SUCCEEDED(), NG_FAILED() を使用する
	*/
	enum eErrCode
	{
		eNG_S_OK		= S_OK,		//!< 成功
		eNG_S_FALSE		= S_FALSE,	//!< 成功
		eNG_E_FAIL		= E_FAIL,	//!< 失敗

		eNG_E_UNKNOWN			= NG_MAKE_NG_ERRCODE(1),	//!< 不明なエラー
		eNG_E_INVALIDMEMORY		= NG_MAKE_NG_ERRCODE(2),	//!< メモリが不正である
		eNG_E_CAPACITYLACK		= NG_MAKE_NG_ERRCODE(3),	//!< 指定した容量が不足している
		eNG_E_LEAK				= NG_MAKE_NG_ERRCODE(4),	//!< 未解放エラー
		eNG_E_BUFFOVERFLOW		= NG_MAKE_NG_ERRCODE(5),	//!< バッファオーバーフロー
		eNG_E_INITFAILED		= NG_MAKE_NG_ERRCODE(6),	//!< 初期化失敗
	};

	/*!
	* @brief					NG エラーコード 文字列変換
	* @param code				エラーコード
	* @retval nullptr			該当なし
	*/
	NG_DECL const char* ErrorCodeToString(NG_ERRCODE code);

	/*!
	* @brief					NG エラーコード 説明取得
	* @param code				エラーコード
	* @retval nullptr			該当なし
	*/
	NG_DECL const char* ErrorCodeToDescription(NG_ERRCODE code);

}	// namespace ng

#endif	// __NG_CORE_RET_CODE_H__

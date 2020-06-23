/*!
* @file		ngErrCode.cpp
* @brief	関数戻り値 エラーコード
* @date		2017-08-09
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "ngErrCode.h"

namespace ng
{
	//! NG エラーコード 詳細
	struct Detail
	{
		NG_ERRCODE code;
		const char* str;
		const char* desc;
	};

	//! NG エラーコード 詳細定義
	#define MAKE_DETAIL(_code, _desc) \
		_code, #_code, _desc

	//! NG エラーコード -> 詳細変換テーブル
	static const Detail g_errCodeDetailTable[] = {
		MAKE_DETAIL(eNG_S_OK,				"Operation successful"),
		MAKE_DETAIL(eNG_S_FALSE,			"Operation aborted"),
		MAKE_DETAIL(E_ACCESSDENIED,			"General access denied error"),
		MAKE_DETAIL(eNG_E_FAIL,				"Unspecified failure"),
		MAKE_DETAIL(E_HANDLE,				"Handle that is not valid"),
		MAKE_DETAIL(E_INVALIDARG,			"One or more arguments are not valid"),
		MAKE_DETAIL(E_NOINTERFACE,			"No such interface supported"),
		MAKE_DETAIL(E_NOTIMPL,				"Not implemented"),
		MAKE_DETAIL(E_OUTOFMEMORY,			"Failed to allocate necessary memory"),
		MAKE_DETAIL(E_POINTER,				"Pointer that is not valid"),
		MAKE_DETAIL(E_UNEXPECTED,			"Unexpected failure"),
		MAKE_DETAIL(eNG_E_INDEFINITE,		"(NG ErrCode) 不定"),
		MAKE_DETAIL(eNG_E_UNKNOWN,			"(NG ErrCode) 不明なエラー"),
		MAKE_DETAIL(eNG_E_INVALIDMEMORY,	"(NG ErrCode) 無効なメモリ領域"),
		MAKE_DETAIL(eNG_E_CAPACITYLACK,		"(NG ErrCode) 指定サイズが不足"),
		MAKE_DETAIL(eNG_E_LEAK,				"(NG ErrCode) 未解放エラー"),
		MAKE_DETAIL(eNG_E_BUFFOVERFLOW,		"(NG ErrCode) バッファオーバーフロー"),
		MAKE_DETAIL(eNG_E_INITFAILED,		"(NG ErrCode) 初期化失敗"),
	};

	static const Detail* GetDetail(NG_ERRCODE code);

	NG_DECL const char* ErrorCodeToString(NG_ERRCODE code)
	{
		const Detail* pDetail = GetDetail(code);

		if(pDetail != nullptr) {
			return pDetail->str;
		}

		return nullptr;
	}

	NG_DECL const char* ErrorCodeToDescription(NG_ERRCODE code)
	{
		const Detail* pDetail = GetDetail(code);

		if(pDetail != nullptr) {
			return pDetail->desc;
		}

		return nullptr;
	}

	/*!
	* @brief					NG エラーコード 詳細取得
	* @param code				エラーコード
	*/
	const Detail* GetDetail(NG_ERRCODE code)
	{
		for(int i = 0; i < NG_ARRAY_SIZE(g_errCodeDetailTable); i++)
		{
			const Detail& pair = g_errCodeDetailTable[i];
			if(pair.code == code) {
				return &pair;
			}
		}

		return nullptr;
	}

}	// namespace ng

/*!
* @file		ngDbgMacro.cpp
* @brief	デバッグマクロ定義
* @date		2016-08-22
* @author	s.fukami
*/

#include "ngDbgMacro.h"
#include "../error/ngError.h"

namespace ng
{
	/*!
	* @brief					Win32API エラーコード詳細 デバッグ表示
	*/
	void _DPrintLastErrMsg()
	{
		TCHAR buf[512];
		DWORD ret = ng::GetLastErrMsg(buf, NG_ARRAY_SIZE(buf));
		DPrintf(_T("err:%d, desc:%ls\n"), ret, buf);
	}

	/*!
	* @brief					Win32API エラーコード詳細 メッセージボックス表示
	*/
	void _DMsgBoxLastErrMsg()
	{
		// TODO: NG_MSGBOX で可変引数対応がいいか
		TCHAR buf[512];
		TCHAR buf2[512];
		DWORD ret = ng::GetLastErrMsg(buf, NG_ARRAY_SIZE(buf));
		::wsprintf(buf2, _T("err:%d, desc:%s\n"), ret, buf);
		NG_DMSGBOX(buf2);
	}

}	// namespace ng
/*!
* @file		testSetup.cpp
* @brief	セットアップ
* @date		2020-06-19
* @author	s.fukami
*/

#include "testSetup.h"
#include "ngLibCore/io/stream/ngOutputStream.h"

namespace test
{
	/*!
	* 文字列出力（デバッグ用）の出力ストリーム
	*/
	class CLogStream : public ng::IOutputStream
	{
	public:
		void Write(const char* pMessage) { Logger::WriteMessage(pMessage); }
		void Write(const wchar_t* pMessage) { Logger::WriteMessage(pMessage); }
	};

	void Setup()
	{
		static CLogStream g_logStrm;
		static CLogStream g_logStrmDbg;

		ng::SetPrintOutputStream(&g_logStrm);
		ng::SetDebugPrintOutputStream(&g_logStrmDbg);
	}

}	// namespace test
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

	static CLogStream g_logStream;

	void Setup()
	{
		ng::SetDebugPrintOutputStream(&g_logStream);
	}

}	// namespace test
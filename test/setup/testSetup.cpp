/*!
* @file		testSetup.cpp
* @brief	�Z�b�g�A�b�v
* @date		2020-06-19
* @author	s.fukami
*/

#include "testSetup.h"
#include "ngLibCore/io/stream/ngOutputStream.h"

namespace test
{
	/*!
	* ������o�́i�f�o�b�O�p�j�̏o�̓X�g���[��
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
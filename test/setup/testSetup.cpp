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

	static CLogStream g_logStream;

	void Setup()
	{
		ng::SetDebugPrintOutputStream(&g_logStream);
	}

}	// namespace test
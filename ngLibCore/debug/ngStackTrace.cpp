/*!
* @file		ngStackTrace.cpp
* @brief	スタックトレース
* @date		2018-03-18
* @author	s.fukami
*/

#include <windows.h>
#include <imagehlp.h>
#include "ngLibCore/common/ngCommon.h"
#include "ngStackTrace.h"

#pragma comment(lib, "imagehlp.lib")

namespace ng
{
	NG_DECL void PrintStackTrace()
	{
		#define FRAME_SIZE_MAX	(128)

		HANDLE process = ::GetCurrentProcess();

		::SymInitialize(process, NULL, TRUE);

		void* frames[ FRAME_SIZE_MAX ];
		USHORT frameNum = ::CaptureStackBackTrace(0, FRAME_SIZE_MAX, frames, NULL);

		char buf[ sizeof(SYMBOL_INFO) + 256 * sizeof(char) ];

		SYMBOL_INFO* pSymbol = NG_PLACEMENT_NEW(buf) SYMBOL_INFO;
		pSymbol->MaxNameLen = 255;
		pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);

		DPrintf("### StackTrace ###\n");

		for(USHORT i = 0; i < frameNum; i++)
		{
			::SymFromAddr(process, (DWORD64)frames[i], 0, pSymbol);
			DPrintf("[%3d] (%p) - %s\n", i, reinterpret_cast<void*>(pSymbol->Address), pSymbol->Name);
		}

		#undef FRAME_SIZE_MAX
	}

}	// namespace ng
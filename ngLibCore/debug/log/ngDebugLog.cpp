/*!
* @file		ngDebugLog.cpp
* @brief	デバッグログ出力
* @date		2018-10-21
* @author	s.fukami
*/

#include <time.h>
#include "ngLibCore/common/ngCommon.h"
#include "ngDebugLog.h"

namespace ng
{
	CDebugLog::CDebugLog()
	{
	}
	CDebugLog::~CDebugLog()
	{
	}

	NG_ERRCODE CDebugLog::Open(const char* pFilename)
	{
		NG_ERRCODE ret = eNG_E_FAIL;

		if(NG_SUCCEEDED(ret = m_file.Open(pFilename, "w"))) {
			NG_DPRINTF("Debug log file open succeeded. file:%s\n", pFilename);
		} else {
			NG_ERRLOG(ret, "Debug log file open failed. file:%s", pFilename);
		}

		return ret;
	}

	void CDebugLog::Write(const char* pStr)
	{
		struct tm newTime;
		if(_getLocalTime(&newTime) == 0) {
			char buf[32];
			::asctime_s(buf, sizeof(buf), &newTime);
			m_file.Write("[%.19s] %s\n", buf, pStr);
			/*
			m_file.Write(
				"[%d02d月 %02d日 - %02d:%02d:%02d] %s", 
				newTime->tm_mon + 1, newTime->tm_mday, newTime->tm_hour, newTime->tm_min, newTime->tm_sec, pStr
				);
			*/
		} else {
			m_file.Write(pStr);
		}
	}
	void CDebugLog::Write(const wchar_t* pStr)
	{
		struct tm newTime;
		if(_getLocalTime(&newTime) == 0) {
			wchar_t buf[32];
			::_wasctime_s(buf, sizeof(buf), &newTime);
			m_file.Write(L"[%.19s] %s\n", buf, pStr);
		} else {
			m_file.Write(pStr);
		}
	}

	void CDebugLog::Close()
	{
		m_file.Close();
	}

	errno_t CDebugLog::_getLocalTime(struct tm* pTime)
	{
		__time64_t longTime;
		::_time64(&longTime);

		return ::_localtime64_s(pTime, &longTime);
	}

}	// namespace ng
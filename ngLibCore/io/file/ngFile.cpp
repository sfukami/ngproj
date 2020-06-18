/*!
* @brief	ファイル入出力
* @file		ngFile.cpp
* @date		2018-10-15
* @author	s.fukami
*/

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "ngLibCore/common/ngCommon.h"
#include "ngFile.h"

namespace ng
{
	CFile::CFile()
		: m_fp(nullptr)
	{
	}

	CFile::~CFile()
	{
		Close();
	}

	NG_ERRCODE CFile::Open(const char* pFilename, const char* mode)
	{
		Close();

		errno_t err = ::fopen_s(&m_fp, pFilename, mode);

		if(err != 0) {
			NG_ERRCODE ret = eNG_E_FAIL;
			NG_ERRLOG(ret, "ファイルオープン失敗. file:%s, mode:%s", pFilename, mode);
			NG_DPRINT_LASTERRMSG();
			return ret;
		}

		return eNG_S_OK;
	}
	NG_ERRCODE CFile::Open(const wchar_t* pFilename, const wchar_t* mode)
	{
		Close();

		errno_t err = ::_wfopen_s(&m_fp, pFilename, mode);

		if(err != 0) {
			NG_ERRCODE ret = eNG_E_FAIL;
			NG_ERRLOG(ret, L"ファイルオープン失敗. file:%s, mode:%s", pFilename, mode);
			NG_DPRINT_LASTERRMSG();
			return ret;
		}

		return eNG_S_OK;
	}

	NG_ERRCODE CFile::ReOpen(const char* pFilename, const char* mode, FILE* stream)
	{
		Close();
		
		errno_t err = ::freopen_s(&m_fp, pFilename, mode, stream);

		if(err != 0) {
			NG_ERRCODE ret = eNG_E_FAIL;
			NG_ERRLOG(ret, "新たなファイルオープンに失敗. file:%s, mode:%s", pFilename, mode);
			NG_DPRINT_LASTERRMSG();
			return ret;
		}

		return eNG_S_OK;
	}
	NG_ERRCODE CFile::ReOpen(const wchar_t* pFilename, const wchar_t* mode, FILE* stream)
	{
		Close();
		
		errno_t err = ::_wfreopen_s(&m_fp, pFilename, mode, stream);

		if(err != 0) {
			NG_ERRCODE ret = eNG_E_FAIL;
			NG_ERRLOG(ret, L"新たなファイルオープンに失敗. file:%s, mode:%s", pFilename, mode);
			NG_DPRINT_LASTERRMSG();
			return ret;
		}

		return eNG_S_OK;
	}

	void CFile::Close()
	{
		if(IsOpen()) {
			::fclose(m_fp);
			m_fp = nullptr;
		}
	}

	size_type CFile::Read(void* pDst, size_type size, size_type num)
	{
		if(!IsOpen()) {
			return 0;
		}

		return ::fread(pDst, size, num, m_fp);
	}

	void CFile::Write(const char* format, ...)
	{
		if(!IsOpen()) {
			return;
		}

		va_list args;

		va_start(args, format);
		::vfprintf(m_fp, format, args);
		va_end(args);

		::fflush(m_fp);
	}
	void CFile::Write(const wchar_t* format, ...)
	{
		if(!IsOpen()) {
			return;
		}

		va_list args;

		va_start(args, format);
		::vfwprintf(m_fp, format, args);
		va_end(args);

		::fflush(m_fp);
	}

	NG_ERRCODE CFile::Seek(long offset, int origin)
	{
		NG_ERRCODE ret = eNG_E_FAIL;

		if(!IsOpen()) {
			return ret;
		}

		if(::fseek(m_fp, offset, origin) == 0) {
			ret = eNG_S_OK;
		} else {
			NG_ERRLOG(ret, "ファイルポインタの移動に失敗");
			NG_DPRINT_LASTERRMSG();
			return ret;
		}

		return ret;
	}

	void CFile::Rewind()
	{
		if(!IsOpen()) {
			return;
		}

		::rewind(m_fp);
	}

}	// namespace ng
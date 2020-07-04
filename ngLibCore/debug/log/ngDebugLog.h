/*!
* @file		ngDebugLog.h
* @brief	デバッグログ出力
* @date		2018-10-21
* @author	s.fukami
*/

#ifndef __NG_CORE_DEBUG_LOG_H__
#define __NG_CORE_DEBUG_LOG_H__

#include "ngLibCore/io/file/ngFile.h"

namespace ng
{
	/*!
	* デバッグログ出力
	*/
	class NG_DECL CDebugLog
	{
	public:
		CDebugLog();
		~CDebugLog();

		/*!
		* @brief					ログ出力先ファイルオープン
		* @param pFilename			ログ出力先ファイル名
		* @return					NG エラーコード
		*/
		NG_ERRCODE Open(const char* pFilename);

		/*!
		* @brief					ログ書き込み
		* @param pStr				
		*/
		void Write(const char* pStr);
		void Write(const wchar_t* pStr);

		/*!
		* @brief					ログ出力先ファイルクローズ
		*/
		void Close();

		/*! ファイルをオープンしているか */
		bool IsOpen() const { return m_file.IsOpen(); }

	private:
		/*!
		* @brief					現在時刻取得
		* @param tm					現在時刻格納先
		*/
		errno_t _getLocalTime(struct tm* pTime);

	private:
		CFile m_file;	//!< ファイル入出力
	};

}	// namespace ng

#endif	// __NG_CORE_DEBUG_LOG_H__
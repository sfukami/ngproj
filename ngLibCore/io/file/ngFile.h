/*!
* @file		ngFile.h
* @brief	ファイル入出力
* @date		2018-10-15
* @author	s.fukami
*/

#ifndef __NG_CORE_FILE_H__
#define __NG_CORE_FILE_H__

#include <stdio.h>

namespace ng
{
	/*!
	* ファイル入出力
	*/
	class NG_DECL CFile
	{
	public:
		CFile();
		~CFile();

		/*!
		* @brief					ファイルオープン
		* @param pFilename			ファイル名
		* @param mode				モード
		* @return					NG エラーコード
		*/
		NG_ERRCODE Open(const char* pFilename, const char* mode);
		NG_ERRCODE Open(const wchar_t* pFilename, const wchar_t* mode);

		/*!
		* @brief					再度ファイルオープンする
		* @param pFilename			ファイル名
		* @param mode				モード
		* @param stream				ファイルポインタの格納先
		* @return					NG エラーコード
		*/
		NG_ERRCODE ReOpen(const char* pFilename, const char* mode, FILE* stream);
		NG_ERRCODE ReOpen(const wchar_t* pFilename, const wchar_t* mode, FILE* stream);

		/*!
		* @brief					ファイルクローズ
		*/
		void Close();

		/*!
		* @brief					ファイルから指定バイト数読み込み
		* @param pDst				読み込み値の格納先
		* @param size				読み込むバイト数
		* @param num				読み込むデータの数
		* @return					読み込んだデータの数
		*/
		size_type Read(void* pDst, size_type size, size_type num = 1);

		/*!
		* @brief					ファイルの全データを読み込み
		* @param pDst				読み込み値の格納先
		* @return					成否
		*/
		bool ReadAll(void* pDst);

		/*!
		* @brief					ファイルへ書き込み
		* @param format				文字列の書式
		* @param ...				書き込む文字列（可変長）
		*/
		void Write(const char* format, ...);
		void Write(const wchar_t* format, ...);

		/*!
		* @brief					ファイルポインタを移動する
		* @param offset				オフセット
		* @param origin				原点位置の種類
		* @return					NG エラーコード
		*/
		NG_ERRCODE Seek(long offset, int origin);

		/*!
		* @brief					読み書き位置を取得する
		* @param pPos				読み書き位置の格納先
		*/
		NG_ERRCODE Tell(long* pPos);

		/*!
		* @brief					ファイルポインタを先頭に戻す
		*/
		void Rewind();

		/*! ファイルをオープンしているか */
		bool IsOpen() const { return (m_fp != nullptr); }

		/*! ファイルサイズ取得 */
		size_type GetFileSize();

	private:
		FILE* m_fp;	//!< ファイルポインタ
	};

}	// namespace ng

#endif	// __NG_CORE_FILE_H__
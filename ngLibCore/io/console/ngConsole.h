/*!
* @file		ngConsole.h
* @brief	コンソール
* @date		2018-10-15
* @author	s.fukami
*/

#ifndef __NG_CORE_CONSOLE_H__
#define __NG_CORE_CONSOLE_H__

#include "ngLibCore/traits/ngSingleton.h"
#include "../file/ngFile.h"

namespace ng
{
	/*!
	* コンソール
	*/
	class NG_DECL CConsole : public CSingleton<CConsole>
	{
		NG_SINGLETON(CConsole);

	private:
		CConsole();
		~CConsole();

	public:
		/*!
		* @brief					コンソール起動
		* @param isCloseMenu		閉じるボタン有効か
		* @return					成否
		*/
		bool Boot(bool isCloseMenu);

		/*!
		* @brief					コンソール終了
		* @return					成否
		*/
		bool Shutdown();

		/*!
		* @brief					コンソール一時停止
		*/
		void Pause();

		/*! コンソール起動中か */
		bool IsBoot() const { return m_isBoot; }

	private:
		static CConsole m_instance;	//!< コンソール インスタンス

		CFile m_stdIn;		//!< 標準入力
		CFile m_stdOut;		//!< 標準出力
		CFile m_stdErr;		//!< 標準エラー出力

		bool m_isBoot;		//!< コンソール起動中か
	};

}	// namespace ng

#endif	// __NG_CORE_CONSOLE_H__
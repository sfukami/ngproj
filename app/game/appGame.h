/*!
* @file		appGame.h
* @brief	ゲームメイン
* @date		2016-08-22
* @author	s.fukami
*/

#ifndef __APP_GAME_H__
#define __APP_GAME_H__

#include <Windows.h>
#include "ngLibApp/window/ngWindow.h"

namespace app
{
	class CGame
	{
	public:
		CGame();
		virtual ~CGame();

		/*!
		* @brief					初期化
		* @param hInst				インスタンスハンドル
		* @return					成否
		*/
		bool Initialize(HINSTANCE hInst);

		/*!
		* @brief					メインループ
		* @return					リターンコード
		*/
		int MainLoop();

		/*!
		* @brief					終了処理
		*/
		void Finalize();

	private:
		ng::CWindow m_window;	//!< ウィンドウ
	};

}	// namespace app

#endif	// __APP_GAME_H__

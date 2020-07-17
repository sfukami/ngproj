/*!
* @file		appApplication.h
* @brief	アプリケーション
* @date		2016-08-22
* @author	s.fukami
*/

#ifndef __APP_APPLICATION_H__
#define __APP_APPLICATION_H__

#include <Windows.h>
#include "ngLibApp/window/ngWindow.h"
#include "../memory/appApplicationMemory.h"
#include "../input/appInput.h"
#include "../graphic/appGraphic.h"
#include "../scene/appSceneManager.h"
#include "../tool/gui/appToolGUI.h"

namespace app
{
	/*!
	* @brief					アプリケーション
	*/
	class CApplication
	{
	public:
		CApplication();
		~CApplication();

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
		/*! 更新処理 */
		void _update();

		/*! 描画処理 */
		void _render();

	private:
		ng::CWindow m_window;	//!< ウィンドウ
		CApplicationMemory m_appMem;	//!< アプリケーションメモリ
		CInput m_input;			//!< 入力
		CGraphic m_graphic;		//!< グラフィック
		CSceneManager m_sceneMngr;	//!< シーン管理
		CToolGUI m_toolGUI;		//!< ツールGUI
	};

}	// namespace app

#endif	// __APP_APPLICATION_H__
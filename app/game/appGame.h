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
#include "../memory/appApplicationMemory.h"
#include "../input/appInput.h"
#include "../graphic/appGraphic.h"
#include "../scene/appSceneManager.h"

namespace app
{
	/*!
	* @brief					ゲームメイン
	*/
	class CGame
	{
		friend class GameModule;

	public:
		CGame();
		~CGame();

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
		ng::CWindow m_window;		//!< ウィンドウ
		CApplicationMemory m_memory;	//!< アプリケーションメモリ
		CInput m_input;				//!< 入力
		CGraphic m_graphic;			//!< グラフィック
		CSceneManager m_sceneMngr;	//!< シーン管理
	};

}	// namespace app

#endif	// __APP_GAME_H__

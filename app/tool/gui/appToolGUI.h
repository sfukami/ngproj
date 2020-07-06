/*!
* @file		appToolGUI.h
* @brief	ツールGUI
* @date		2020-07-06
* @author	s.fukami
*/

#ifndef __APP_TOOL_GUI_H__
#define __APP_TOOL_GUI_H__

#include "ngLibApp/ui/imgui/ngImGuiDX12.h"

namespace app
{
	class CGraphic;
}

namespace app
{
	/*!
	* @brief					ツールGUI
	*/
	class CToolGUI
	{
	public:
		CToolGUI();
		~CToolGUI();

		/*!
		* @brief					初期化
		* @param hWnd				ウィンドウハンドル
		* @param graphic			appグラフィック
		* @return					成否
		*/
		bool Initialize(
			HWND hWnd,
			CGraphic& graphic
			);

		/*!
		* @brief					終了処理
		*/
		void Finalize();

		/*!
		* @brief					描画
		*/
		void Render();

		/*!
		* @brief					描画前処理
		*/
		void BeginRender();

		/*!
		* @brief					描画後処理
		*/
		void EndRender();

		/*! 初期化済みか */
		bool IsInit() const;

	public:
		/*!
		* @brief					ウィンドウプロシージャ
		* @note						ウィンドウプロシージャ内で呼び出す。キーボード、マウスを用いる場合は必須
		*/
		static LRESULT WinProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		ng::CImGuiDX12 m_imGui;		//!< ImGuiラッパー
		bool m_isInit;		//!< 初期化済みか
	};

}	// namespace app

#endif	// __APP_TOOL_GUI_H__
/*!
* @file		appGraphic.h
* @brief	アプリケーショングラフィック
* @date		2020-08-24
* @author	s.fukami
*/

#ifndef __APP_GRAPHIC_H__
#define __APP_GRAPHIC_H__

#include <Windows.h>
#include "ngLibGraphic/graphic/dx12/ngDX12Graphic.h"

namespace app
{
	/*!
	* @brief					アプリケーショングラフィック
	*/
	class CGraphic
	{
	public:
		CGraphic();
		~CGraphic();

		/*!
		* @brief					初期化
		* @param hWnd				ウィンドウハンドル
		* @param clientWidth		クライアント領域幅
		* @param clientHeight		クライアント領域高さ
		* @param isFullScreen		フルスクリーンか
		* @return					成否
		*/
		bool Initialize(
			HWND hWnd,
			unsigned int clientWidth,
			unsigned int clientHeight,
			bool isFullScreen
			);

		/*!
		* @brief					終了処理
		*/
		void Finalize();

		/*!
		* @brief					描画
		*/
		void Render();

	private:
		ng::CDX12Graphic m_dx12Graphic;	//!< DX12グラフィック
	};

}	// namespace app

#endif	// __APP_GRAPHIC_H__
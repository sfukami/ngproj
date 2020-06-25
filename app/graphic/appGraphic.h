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
//test
#include "pipeline/test/appGraphicPipelineClearBuffer.h"

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
		/*!
		* @brief					パイプライン実行
		*/
		void _executePipeline();

		/*!
		* @brief					パイプライン実行 事前処理
		*/
		void _preprocessPipeline();

		/*!
		* @brief					パイプライン実行 事後処理
		*/
		void _postprocessPipeline();

		/*! 初期化済みか */
		bool _isInit() const;

	private:
		bool m_isInit;	//!< 初期化済みか
		ng::CDX12Graphic m_dx12Graphic;	//!< DX12グラフィック
		
		// test
		CGraphicPipelineClearBuffer m_pipeline;	//!< グラフィックパイプラインテスト
	};

}	// namespace app

#endif	// __APP_GRAPHIC_H__
/*!
* @file		appGraphicPipelineClearBuffer.h
* @brief	グラフィックパイプライン バッファクリア
* @date		2020-06-24
* @author	s.fukami
*/

#ifndef __APP_GRAPHIC_PIPELINE_CLEAR_BUFFER_H__
#define __APP_GRAPHIC_PIPELINE_CLEAR_BUFFER_H__

#include "../appGraphicPipeline.h"
#include "ngLibGraphic/graphic/dx12/viewport/ngDX12Viewport.h"
#include "ngLibGraphic/graphic/dx12/scissor/ngDX12Scissor.h"

namespace app
{
	/*!
	* @brief					グラフィックパイプライン バッファクリア
	*/
	class CGraphicPipelineClearBuffer : public CGraphicPipeline
	{
	public:
		CGraphicPipelineClearBuffer();
		~CGraphicPipelineClearBuffer();

		/*!
		* @brief					初期化
		* @return					成否
		*/
		bool Initialize();

		/*!
		* @brief					終了処理
		*/
		void Finalize();

		/*!
		* @brief					実行
		*/
		void Execute();
		
	private:
		ng::CDX12Viewport m_viewport;	//!< DX12ビューポート
		ng::CDX12Scissor m_scissor;		//!< DX12シザー矩形
	};

}	// namespace app

#endif	// __APP_GRAPHIC_PIPELINE_CLEAR_BUFFER_H__
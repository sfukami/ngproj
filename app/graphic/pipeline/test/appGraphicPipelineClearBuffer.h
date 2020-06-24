/*!
* @file		appGraphicPipelineClearBuffer.h
* @brief	グラフィックパイプライン バッファクリア
* @date		2020-08-24
* @author	s.fukami
*/

#ifndef __APP_GRAPHIC_PIPELINE_CLEAR_BUFFER_H__
#define __APP_GRAPHIC_PIPELINE_CLEAR_BUFFER_H__

#include "../appGraphicPipeline.h"

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
		* @brief					描画
		*/
		void Render();
		
	private:
		
	};

}	// namespace app

#endif	// __APP_GRAPHIC_PIPELINE_CLEAR_BUFFER_H__
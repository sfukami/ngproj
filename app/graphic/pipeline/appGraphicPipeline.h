/*!
* @file		appGraphicPipeline.h
* @brief	グラフィックパイプライン 基底クラス
* @date		2020-08-24
* @author	s.fukami
*/

#ifndef __APP_GRAPHIC_PIPELINE_H__
#define __APP_GRAPHIC_PIPELINE_H__

namespace app
{
	/*!
	* @brief					グラフィックパイプライン 基底クラス
	*/
	class CGraphicPipeline
	{
	public:
		CGraphicPipeline();
		virtual ~CGraphicPipeline();

		/*!
		* @brief					初期化
		* @return					成否
		*/
		virtual bool Initialize();

		/*!
		* @brief					終了処理
		*/
		virtual void Finalize();

		/*!
		* @brief					描画
		*/
		virtual void Render();
	};

}	// namespace app

#endif	// __APP_GRAPHIC_PIPELINE_H__
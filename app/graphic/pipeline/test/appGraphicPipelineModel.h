﻿/*!
* @file		appGraphicPipelineModel.h
* @brief	グラフィックパイプライン モデル描画
* @date		2020-06-24
* @author	s.fukami
*/

#ifndef __APP_GRAPHIC_PIPELINE_MODEL_H__
#define __APP_GRAPHIC_PIPELINE_MODEL_H__

#include "../appGraphicPipeline.h"
#include "ngLibGraphic/graphic/dx12/viewport/ngDX12Viewport.h"
#include "ngLibGraphic/graphic/dx12/scissor/ngDX12Scissor.h"
#include "ngLibGraphic/camera/ngCamera.h"
#include "ngLibGraphic/projection/ngProjection.h"
#include "app/graphic/render/model/appModelRender.h"

namespace app
{
	/*!
	* @brief					グラフィックパイプライン モデル描画
	*/
	class CGraphicPipelineModel : public CGraphicPipeline
	{
	public:
		CGraphicPipelineModel();
		~CGraphicPipelineModel();

	private:
		/*!
		* @brief					初期化
		* @return					成否
		*/
		bool _initialize();

		/*!
		* @brief					終了処理
		*/
		void _finalize();

		/*!
		* @brief					実行
		*/
		void _execute();
		
	private:
		ng::CDX12Viewport m_viewport;	//!< DX12ビューポート
		ng::CDX12Scissor m_scissor;		//!< DX12シザー矩形
		ng::CCamera m_camera;		//!< カメラ
		ng::CProjection m_proj;		//!< プロジェクション
		CModelRender m_model;		//!< モデル
	};

}	// namespace app

#endif	// __APP_GRAPHIC_PIPELINE_MODEL_H__
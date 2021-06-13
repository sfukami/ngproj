/*!
* @file		appGraphicPipelineModel.h
* @brief	グラフィックパイプライン モデル描画
* @date		2020-06-24
* @author	s.fukami
*/

#ifndef __APP_GRAPHIC_PIPELINE_MODEL_H__
#define __APP_GRAPHIC_PIPELINE_MODEL_H__

#include "../appGraphicPipeline.h"
#include "ngLibGraphic/graphic/dx12/shader/ngDX12Shader.h"
#include "ngLibGraphic/graphic/dx12/rootsign/ngDX12RootSignature.h"
#include "ngLibGraphic/graphic/dx12/pipeline/ngDX12PipelineState.h"
#include "ngLibGraphic/graphic/dx12/descriptor/ngDX12DescriptorHeap.h"
#include "ngLibGraphic/graphic/dx12/shader/ngDX12ConstantBuffer.h"
#include "ngLibGraphic/graphic/dx12/viewport/ngDX12Viewport.h"
#include "ngLibGraphic/graphic/dx12/scissor/ngDX12Scissor.h"
#include "ngLibGraphic/camera/ngCamera.h"
#include "ngLibGraphic/projection/ngProjection.h"
#include "app/graphic/model/appModel.h"

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
		ng::CDX12Shader m_vs;			//!< DX12頂点シェーダー
		ng::CDX12Shader m_ps;			//!< DX12ピクセルシェーダー
		ng::CDX12RootSignature m_rootSign;	//!< DX12ルートシグネチャ
		ng::CDX12PipelineState m_pipelineState;	//!< DX12パイプラインステート
		ng::CDX12DescriptorHeap m_descHeap;	//!< DX12ディスクリプタヒープ
		ng::CDX12ConstantBuffer m_constBuf;	//!< DX12コンスタントバッファ
		ng::CDX12Viewport m_viewport;	//!< DX12ビューポート
		ng::CDX12Scissor m_scissor;		//!< DX12シザー矩形
		ng::CCamera m_camera;		//!< カメラ
		ng::CProjection m_proj;		//!< プロジェクション
		CModel m_model;			//!< モデル
	};

}	// namespace app

#endif	// __APP_GRAPHIC_PIPELINE_MODEL_H__
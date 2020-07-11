/*!
* @file		appGraphicPipelineShape.h
* @brief	グラフィックパイプライン シェイプ描画
* @date		2020-07-08
* @author	s.fukami
*/

#ifndef __APP_GRAPHIC_PIPELINE_SHAPE_H__
#define __APP_GRAPHIC_PIPELINE_SHAPE_H__

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
// shape
#include "ngLibGraphic/graphic/dx12/polygon/shape/ngDX12ShapeSquare.h"
#include "ngLibGraphic/graphic/dx12/polygon/shape/ngDX12ShapeBox.h"

namespace app
{
	/*!
	* @brief					グラフィックパイプライン シェイプ描画
	*/
	class CGraphicPipelineShape : public CGraphicPipeline
	{
	public:
		CGraphicPipelineShape();
		~CGraphicPipelineShape();

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
		
		/*! ワールド変換行列更新 */
		void _updateWorldMatrix();

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

		// shape
		ng::CDX12ShapeSquare m_square;	//!< DX12ポリゴン 矩形
		ng::CDX12ShapeBox m_box;	//!< DX12ポリゴン ボックス
	};

}	// namespace app

#endif	// __APP_GRAPHIC_PIPELINE_SHAPE_H__
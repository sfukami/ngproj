/*!
* @file		appGraphicPipelinePolygon.h
* @brief	グラフィックパイプライン ポリゴン描画
* @date		2020-06-24
* @author	s.fukami
*/

#ifndef __APP_GRAPHIC_PIPELINE_POLYGON_H__
#define __APP_GRAPHIC_PIPELINE_POLYGON_H__

#include "../appGraphicPipeline.h"
#include "ngLibGraphic/graphic/dx12/shader/ngDX12Shader.h"
#include "ngLibGraphic/graphic/dx12/polygon/ngDX12Polygon.h"
#include "ngLibGraphic/graphic/dx12/rootsign/ngDX12RootSignature.h"
#include "ngLibGraphic/graphic/dx12/pipeline/ngDX12PipelineState.h"
#include "ngLibGraphic/graphic/dx12/descriptor/ngDX12DescriptorHeap.h"
#include "ngLibGraphic/graphic/dx12/shader/ngDX12ConstantBuffer.h"
#include "ngLibGraphic/graphic/dx12/viewport/ngDX12Viewport.h"
#include "ngLibGraphic/graphic/dx12/scissor/ngDX12Scissor.h"

namespace app
{
	/*!
	* @brief					グラフィックパイプライン ポリゴン描画
	*/
	class CGraphicPipelinePolygon : public CGraphicPipeline
	{
	public:
		CGraphicPipelinePolygon();
		~CGraphicPipelinePolygon();

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
		ng::CDX12Shader m_vs;			//!< DX12頂点シェーダー
		ng::CDX12Shader m_ps;			//!< DX12ピクセルシェーダー
		ng::CDX12Polygon m_polygon;		//!< DX12ポリゴン
		ng::CDX12RootSignature m_rootSign;	//!< DX12ルートシグネチャ
		ng::CDX12PipelineState m_pipelineState;	//!< DX12パイプラインステート
		ng::CDX12DescriptorHeap m_descHeap;	//!< DX12ディスクリプタヒープ
		ng::CDX12ConstantBuffer m_constBuf;	//!< DX12コンスタントバッファ
		ng::CDX12Viewport m_viewport;	//!< DX12ビューポート
		ng::CDX12Scissor m_scissor;		//!< DX12シザー矩形
	};

}	// namespace app

#endif	// __APP_GRAPHIC_PIPELINE_POLYGON_H__
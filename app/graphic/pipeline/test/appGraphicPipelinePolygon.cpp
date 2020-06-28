/*!
* @file		appGraphicPipelinePolygon.cpp
* @brief	グラフィックパイプライン ポリゴン描画
* @date		2020-06-24
* @author	s.fukami
*/

#include <DirectXMath.h>
#include "ngLibCore/common/ngCommon.h"
#include "ngLibGraphic/graphic/dx12/ngDX12.h"
#include "ngLibCore/geometry/matrix/ngMatrix4x4.h"
//#include "ngLibCore/color/ngColor.h"
#include "appGraphicPipelinePolygon.h"

using namespace DirectX;

namespace app
{
	//! シェーダーパラメータ
	struct ShaderParam
	{
		ShaderParam()
		//	: color(1,1,1,1)
		{ }
		ng::Matrix4 matWVP;
		//ColorF color;
	};

	CGraphicPipelinePolygon::CGraphicPipelinePolygon()
	{
	}
	CGraphicPipelinePolygon::~CGraphicPipelinePolygon()
	{
	}

	bool CGraphicPipelinePolygon::Initialize()
	{
		const unsigned int clientWidth = 640;
		const unsigned int clientHeight = 480;

		m_viewport.Initialize(0.0f, 0.0f, (float)clientWidth, (float)clientHeight, 0.0f, 1.0f);
		m_scissor.Initialize(0, 0, (LONG)clientWidth, (LONG)clientHeight);

		ng::CDX12Device* pDX12Device = ng::DX12Util::GetDevice();
		NG_ASSERT(pDX12Device != nullptr);

		// ルートシグネチャ生成
		{
			D3D12_DESCRIPTOR_RANGE descriptorRange = {};
			descriptorRange.NumDescriptors = 1;
			descriptorRange.BaseShaderRegister = 0;
			descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
			descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

			D3D12_ROOT_PARAMETER rootParam = {};
			rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
			rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
			rootParam.DescriptorTable.NumDescriptorRanges = 1;
			rootParam.DescriptorTable.pDescriptorRanges = &descriptorRange;

			D3D12_STATIC_SAMPLER_DESC samplerDesc = {};
			//samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
			samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
			samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			samplerDesc.MipLODBias = 0.0f;
			samplerDesc.MaxAnisotropy = 16;
			samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
			samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
			samplerDesc.MinLOD = 0.0f;
			samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
			samplerDesc.ShaderRegister = 0;
			samplerDesc.RegisterSpace = 0;
			samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

			CD3DX12_ROOT_SIGNATURE_DESC rootSignDesc;
			rootSignDesc.Init(
				1, &rootParam,
				1, &samplerDesc,
				D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT
				);

			NG_ERRCODE err = m_rootSign.Create(*pDX12Device, rootSignDesc);
			if(NG_FAILED(err)) {
				NG_ERRLOG_C("GraphicPipelinePolygon", err, "DX12ルートシグネチャの生成に失敗しました.");
				return false;
			}
		}

		// ディスクリプタヒープ生成
		{
			NG_ERRCODE err = m_descHeap.Create(
				*pDX12Device,
				D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
				1,
				D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE
				);
			if(NG_FAILED(err)) {
				NG_ERRLOG_C("GraphicPipelinePolygon", err, "DX12ディスクリプタヒープの生成に失敗しました.");
				return false;
			}
		}

		// コンスタントバッファ生成
		{
			NG_ERRCODE err = m_constBuf.Create(
				*pDX12Device,
				nullptr, sizeof(ShaderParam)
				);
			if(NG_FAILED(err)) {
				NG_ERRLOG_C("GraphicPipelinePolygon", err, "DX12コンスタントバッファの生成に失敗しました.");
				return false;
			}

			// リソースビュー生成
			m_constBuf.CreateResourceView(
				*pDX12Device, m_descHeap, 0
				);
		}

		// シェーダー生成
		{
			NG_ERRCODE err = NG_ERRCODE_DEFAULT;
			if(NG_FAILED(err = m_vs.Create(
				L"resource/shader/simple.hlsl",
				"VSMain",
				"vs_5_0",
				0, true
				))) {
				NG_ERRLOG_C("GraphicPipelinePolygon", err, "DX12頂点シェーダーの生成に失敗しました.");
				return false;
			}
			if(NG_FAILED(err = m_ps.Create(
				L"resource/shader/simple.hlsl",
				"PSMain",
				"ps_5_0",
				0, true
				))) {
				NG_ERRLOG_C("GraphicPipelinePolygon", err, "DX12ピクセルシェーダーの生成に失敗しました.");
				return false;
			}
		}

		// ポリゴン生成
		{
			float aspectRatio = clientWidth / (float)clientHeight;
			struct Vertex
			{
				XMFLOAT3	position;
				XMFLOAT2	uv;
			};
			const Vertex squareVertices[] = {
				{{-0.25f,  0.25f*aspectRatio, 0.0f}, {0.0f, 0.0f}},	// 0
				{{ 0.25f,  0.25f*aspectRatio, 0.0f}, {1.0f, 0.0f}},	// 1
				{{-0.25f, -0.25f*aspectRatio, 0.0f}, {0.0f, 1.0f}},	// 2
				{{ 0.25f, -0.25f*aspectRatio, 0.0f}, {1.0f, 1.0f}}	// 3
			};

			const ng::u32 squareIndices[] = {
				0, 1, 2,
				2, 1, 3,
			};

			NG_ERRCODE err = m_polygon.Create(
				*pDX12Device,
				squareVertices,
				sizeof(squareVertices),
				sizeof(Vertex),
				D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
				squareIndices,
				sizeof(squareIndices)
				);
			if(NG_FAILED(err)) {
				NG_ERRLOG_C("GraphicPipelinePolygon", err, "DX12ポリゴンの生成に失敗しました.");
				return false;
			}
		}

		// パイプラインステート生成
		{
			ng::CDX12PipelineStateDesc stateDesc;

			// ルートシグネチャ設定
			stateDesc.SetRootSignature(m_rootSign);

			// シェーダー設定
			stateDesc.SetVertexShader(m_vs);
			stateDesc.SetPixelShader(m_ps);

			// 頂点入力レイアウト設定
			D3D12_INPUT_ELEMENT_DESC inputElemDescs[] = {
				{"POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT,	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
				{"COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D12_APPEND_ALIGNED_ELEMENT,	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0}
			};
			stateDesc.InputLayout = {inputElemDescs, _countof(inputElemDescs)};

			stateDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
			//stateDesc.RasterizerState.FrontCounterClockwise = true;
			stateDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
			stateDesc.DepthStencilState.DepthEnable = FALSE;
			stateDesc.DepthStencilState.StencilEnable = FALSE;
			stateDesc.SampleMask = UINT_MAX;
			stateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
			stateDesc.NumRenderTargets = 1;
			stateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
			stateDesc.SampleDesc.Count = 1;

			NG_ERRCODE err = m_pipelineState.Create(*pDX12Device, stateDesc);
			if(NG_FAILED(err)) {
				NG_ERRLOG_C("GraphicPipelinePolygon", err, "DX12パイプラインステートの生成に失敗しました.");
				return false;
			}
		}

		return true;
	}

	void CGraphicPipelinePolygon::Finalize()
	{
		m_vs.Destroy();
		m_ps.Destroy();
		m_polygon.Destroy();

		m_constBuf.Destroy();
		m_descHeap.Destroy();

		m_pipelineState.Destroy();
		m_rootSign.Destroy();
	}

	void CGraphicPipelinePolygon::Execute()
	{
		// コマンドリストリセット
		ng::CDX12CommandList* pCmdList = ng::DX12Util::GetCommandList(0);
		pCmdList->Reset(m_pipelineState);

		// ルートシグネチャ設定
		pCmdList->SetRootSignature(m_rootSign);

		// ビューポート設定
		pCmdList->SetViewport(m_viewport);
		// シザー矩形設定
		pCmdList->SetScissorRect(m_scissor);

		// バックバッファをレンダリングターゲットとして使用
		ng::CDX12RenderTarget* pRTBackBuffer = ng::DX12Util::GetRenderTargetOfCurrentBackBuffer();
		ng::CDX12DepthStencil* pDS = ng::DX12Util::GetDepthStencil(ng::eDX12DepthStencilId::ID_01);
		ng::DX12Util::SetRenderTarget(pCmdList, pRTBackBuffer, pDS);

		// バックポリゴン描画
		const float clearColor[4] = {0.0f, 0.0f, 0.5f, 1.0f};
		ng::DX12Util::ClearRenderTarget(pCmdList, pRTBackBuffer, clearColor, pDS);

		/*
		// メッシュ描画
		{
			ng::Matrix4 matWorld, matView, matProj, matWVP;
			matWorld = g_matWorld;
			//ng::MatrixOp::Translation(matWorld, 0, 0, 0);
			matView = m_camera.GetViewMatrix();
			matProj = m_proj.GetProjMatrix();

			ng::MatrixOp::Multiply(matWVP, matView, matProj);
			ng::MatrixOp::Multiply(matWVP, matWorld, matWVP);
			ng::MatrixOp::Transpose(matWVP, matWVP);

			// シェーダーパラメータ設定
			m_shdImpl.SetColor(ng::ColorF(ng::eColorCode::RED));
			m_shdImpl.SetWVPMatrix(matWVP);
			m_shdImpl.UpdateConstantBuffer();

			// ディスクリプタヒープ設定
			pCmdList->SetDescriptorHeap(m_descHeap);
			// コンスタントバッファのディスクリプタテーブルを設定
			pCmdList->SetGraphicsRootDescriptorTable(0, m_descHeap.GetGPUDescriptorHandle(0));

			m_meshBox.Render(*pCmdList);
		}
		*/
		// ポリゴン描画
		{
			// シェーダーパラメータ設定
			ShaderParam shdPrm;
			//shdPrm.matWVP = mat;
			//shdPrm.color = color;
			m_constBuf.CopyData(&shdPrm, sizeof(ShaderParam));

			// ディスクリプタヒープ設定
			pCmdList->SetDescriptorHeap(m_descHeap);
			// コンスタントバッファのディスクリプタテーブルを設定
			pCmdList->SetGraphicsRootDescriptorTable(0, m_descHeap.GetGPUDescriptorHandle(0));

			m_polygon.Render(*pCmdList);
		}

		ng::DX12Util::SetRenderTargetToPresent(pCmdList, pRTBackBuffer);

		// コマンドの記録を終了
		pCmdList->Close();
	}

}	// namespace app
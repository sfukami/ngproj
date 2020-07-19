/*!
* @file		appGraphicPipelineShape.cpp
* @brief	グラフィックパイプライン シェイプ描画
* @date		2020-07-08
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "ngLibCore/math/ngMath.h"
#include "ngLibGraphic/graphic/dx12/ngDX12.h"
#include "ngLibCore/geometry/matrix/ngMatrix4x4.h"
#include "ngLibCore/geometry/matrix/ngMatrixOp.h"
#include "ngLibCore/color/ngColor.h"
#include "appGraphicPipelineShape.h"
#include "app/graphic/appGraphicUtil.h"
#include "../../../input/appInputModule.h"

namespace app
{
	static ng::Matrix4 g_matWorld = ng::Matrix4::IDENTITY;

	//! シェーダーパラメータ
	struct ShaderParam
	{
		ShaderParam()
			: color(1,1,1,1)
		{ ng::MatrixOp::Identity(matWVP); }
		ng::Matrix4 matWVP;
		ng::Color color;
	};

	CGraphicPipelineShape::CGraphicPipelineShape()
	{
	}
	CGraphicPipelineShape::~CGraphicPipelineShape()
	{
	}

	bool CGraphicPipelineShape::_initialize()
	{
		const unsigned int clientWidth = 640;
		const unsigned int clientHeight = 480;

		ng::CDX12Device* pDX12Device = ng::DX12Util::GetDevice();
		NG_ASSERT(pDX12Device != nullptr);

		// ルートシグネチャ生成
		{
			CD3DX12_DESCRIPTOR_RANGE CBRange(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);

			CD3DX12_ROOT_PARAMETER rootParams[1];
			rootParams[0].InitAsDescriptorTable(1, &CBRange, D3D12_SHADER_VISIBILITY_ALL);

			CD3DX12_STATIC_SAMPLER_DESC samplerDesc;
			samplerDesc.Init(
				0, D3D12_FILTER_MIN_MAG_MIP_POINT
				);

			CD3DX12_ROOT_SIGNATURE_DESC rootSignDesc;
			rootSignDesc.Init(
				NG_ARRAY_SIZE(rootParams), rootParams,
				1, &samplerDesc,
				D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT
				);

			NG_ERRCODE err = m_rootSign.Create(*pDX12Device, rootSignDesc);
			if(NG_FAILED(err)) {
				NG_ERRLOG_C("GraphicPipelineShape", err, "DX12ルートシグネチャの生成に失敗しました.");
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
				NG_ERRLOG_C("GraphicPipelineShape", err, "DX12ディスクリプタヒープの生成に失敗しました.");
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
				NG_ERRLOG_C("GraphicPipelineShape", err, "DX12コンスタントバッファの生成に失敗しました.");
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
				NG_ERRLOG_C("GraphicPipelineShape", err, "DX12頂点シェーダーの生成に失敗しました.");
				return false;
			}
			if(NG_FAILED(err = m_ps.Create(
				L"resource/shader/simple.hlsl",
				"PSMain",
				"ps_5_0",
				0, true
				))) {
				NG_ERRLOG_C("GraphicPipelineShape", err, "DX12ピクセルシェーダーの生成に失敗しました.");
				return false;
			}
		}

		// DX12ポリゴン 矩形生成
		{
			NG_ERRCODE err = m_square.Create(*pDX12Device, 1.f, 1.f, false);
			if(NG_FAILED(err)) {
				NG_ERRLOG_C("GraphicPipelineShape", err, "DX12ポリゴン 矩形の生成に失敗しました.");
				return false;
			}
		}

		// DX12ポリゴン ボックス生成
		{
			NG_ERRCODE err = m_box.Create(*pDX12Device, 1.f, 1.f, 1.f);
			if(NG_FAILED(err)) {
				NG_ERRLOG_C("GraphicPipelineShape", err, "DX12ポリゴン ボックスの生成に失敗しました.");
				return false;
			}
		}

		// パイプラインステート生成
		{
			ng::CDX12PipelineStateDesc stateDesc;
			stateDesc.Initialize();

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

			// 深度ステンシル
			stateDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
			stateDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;

			// レンダーターゲット
			stateDesc.NumRenderTargets = 1;
			stateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;

			// その他
			stateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
			stateDesc.SampleDesc = {1,0};

			NG_ERRCODE err = m_pipelineState.Create(*pDX12Device, stateDesc);
			if(NG_FAILED(err)) {
				NG_ERRLOG_C("GraphicPipelineShape", err, "DX12パイプラインステートの生成に失敗しました.");
				return false;
			}
		}

		// カメラ
		{
			m_camera.SetPos(ng::Vector3(0.f, 0.f, -3.f));
			m_camera.SetAtPos(ng::Vector3::ZERO);
			m_camera.SetUpVec(ng::Vector3::AXIS_Y);
			m_camera.CalcViewMatrix();
		}

		// プロジェクション
		{
			m_proj.SetWidth(clientWidth);
			m_proj.SetHeight(clientHeight);
			m_proj.SetNear(0.1f);
			m_proj.SetFar(100.f);
			m_proj.SetFOV(ng::DegreeToRadian(60.f));
			m_proj.CalcProjMatrix();
		}

		m_viewport.Initialize(0.0f, 0.0f, (float)clientWidth, (float)clientHeight, 0.0f, 1.0f);
		m_scissor.Initialize(0, 0, (LONG)clientWidth, (LONG)clientHeight);

		return true;
	}

	void CGraphicPipelineShape::_finalize()
	{
		m_vs.Destroy();
		m_ps.Destroy();

		m_square.Destroy();
		m_box.Destroy();

		m_constBuf.Destroy();
		m_descHeap.Destroy();

		m_pipelineState.Destroy();
		m_rootSign.Destroy();
	}

	void CGraphicPipelineShape::_execute()
	{
		// コマンドリストリセット
		ng::CDX12CommandList* pCmdList = GraphicUtil::GetDX12CommandList(eGraphicCommandListId::MAIN);
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

		// ポリゴン描画
		{
			// ワールド変換行列更新
			_updateWorldMatrix();

			// シェーダーパラメータ設定
			ng::Matrix4 matWorld, matView, matProj, matWVP;

			matWorld = g_matWorld;
			matView = m_camera.GetViewMatrix();
			matProj = m_proj.GetProjMatrix();

			ng::MatrixOp::Multiply(matWVP, matView, matProj);
			ng::MatrixOp::Multiply(matWVP, matWorld, matWVP);
			ng::MatrixOp::Transpose(matWVP, matWVP);

			ShaderParam shdPrm;
			shdPrm.matWVP = matWVP;
			shdPrm.color = ng::Color(0,1,0);
			m_constBuf.CopyData(&shdPrm, sizeof(ShaderParam));

			// ディスクリプタヒープ設定
			pCmdList->SetDescriptorHeap(m_descHeap);
			// コンスタントバッファのディスクリプタテーブルを設定
			pCmdList->SetGraphicsRootDescriptorTable(0, m_descHeap.GetGPUDescriptorHandle(0));

			//m_square.Render(*pCmdList);
			m_box.Render(*pCmdList);
		}

		ng::DX12Util::SetRenderTargetToPresent(pCmdList, pRTBackBuffer);

		// コマンドの記録を終了
		pCmdList->Close();
	}

	void CGraphicPipelineShape::_updateWorldMatrix()
	{
		static float yaw=0, pitch=0, roll=0;

		ng::Point move = CInputModule::GetMoveDelta();
		yaw -= (float)move.x * 0.01f;
		pitch += (float)move.y * 0.01f;

		ng::MatrixOp::RotationYawPitchRoll(g_matWorld, yaw, pitch, roll);
	}

}	// namespace app
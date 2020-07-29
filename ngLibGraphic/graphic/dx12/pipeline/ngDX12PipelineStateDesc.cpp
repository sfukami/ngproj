/*!
* @file		ngDX12GraphicPipelineStateDesc.cpp
* @brief	DX12グラフィックパイプラインステート記述子
* @date		2019-03-24
* @author	s.fukami
*/

#include <d3dx12.h>
#include "ngLibCore/common/ngCommon.h"
#include "../rootsign/ngDX12RootSignature.h"
#include "../shader/ngDX12Shader.h"
#include "ngDX12PipelineStateDesc.h"

namespace ng
{
	CDX12PipelineStateDesc::CDX12PipelineStateDesc()
		: D3D12_GRAPHICS_PIPELINE_STATE_DESC()
	{
	}
	CDX12PipelineStateDesc::~CDX12PipelineStateDesc()
	{
	}

	void CDX12PipelineStateDesc::Initialize()
	{
		// ラスタライズ
		RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);

		// ブレンド
		BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);

		// 深度ステンシル
		DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
		DSVFormat = DXGI_FORMAT_D32_FLOAT;

		// レンダーターゲット
		NumRenderTargets = 1;
		RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;

		// サンプリング
		SampleMask = UINT_MAX;
		SampleDesc = {1,0};
	}

	void CDX12PipelineStateDesc::SetRootSignature(CDX12RootSignature& signature)
	{
		pRootSignature = signature.Interface();
	}

	void CDX12PipelineStateDesc::SetVertexShader(CDX12Shader& shader)
	{
		D3D12_SHADER_BYTECODE bytecode;
		getShaderBytecode(&bytecode, shader);

		VS = bytecode;
	}

	void CDX12PipelineStateDesc::SetPixelShader(CDX12Shader& shader)
	{
		D3D12_SHADER_BYTECODE bytecode;
		getShaderBytecode(&bytecode, shader);

		PS = bytecode;
	}

	void CDX12PipelineStateDesc::SetDomainShader(CDX12Shader& shader)
	{
		D3D12_SHADER_BYTECODE bytecode;
		getShaderBytecode(&bytecode, shader);

		DS = bytecode;
	}

	void CDX12PipelineStateDesc::SetHullShader(CDX12Shader& shader)
	{
		D3D12_SHADER_BYTECODE bytecode;
		getShaderBytecode(&bytecode, shader);

		HS = bytecode;
	}

	void CDX12PipelineStateDesc::SetGeometryShader(CDX12Shader& shader)
	{
		D3D12_SHADER_BYTECODE bytecode;
		getShaderBytecode(&bytecode, shader);

		GS = bytecode;
	}

	void CDX12PipelineStateDesc::getShaderBytecode(D3D12_SHADER_BYTECODE* pDst, CDX12Shader& shader)
	{
		NG_ASSERT(pDst != nullptr);

		ID3DBlob* pBlob = shader.Interface();
		NG_ASSERT(pBlob != nullptr);

		pDst->pShaderBytecode = pBlob->GetBufferPointer();
		pDst->BytecodeLength = pBlob->GetBufferSize();
	}

}	// namespace ng
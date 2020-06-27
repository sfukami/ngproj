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
#include "ngDX12GraphicPipelineStateDesc.h"

namespace ng
{
	CDX12GraphicPipelineStateDesc::CDX12GraphicPipelineStateDesc()
		: D3D12_GRAPHICS_PIPELINE_STATE_DESC()
	{
	}
	CDX12GraphicPipelineStateDesc::~CDX12GraphicPipelineStateDesc()
	{
	}

	void CDX12GraphicPipelineStateDesc::Initialize()
	{
		RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
		BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);

		SampleMask = UINT_MAX;
		SampleDesc.Count = 1;
	}

	void CDX12GraphicPipelineStateDesc::SetRootSignature(CDX12RootSignature& signature)
	{
		pRootSignature = signature.Interface();
	}

	void CDX12GraphicPipelineStateDesc::SetVertexShader(CDX12Shader& shader)
	{
		D3D12_SHADER_BYTECODE bytecode;
		getShaderBytecode(&bytecode, shader);

		VS = bytecode;
	}

	void CDX12GraphicPipelineStateDesc::SetPixelShader(CDX12Shader& shader)
	{
		D3D12_SHADER_BYTECODE bytecode;
		getShaderBytecode(&bytecode, shader);

		PS = bytecode;
	}

	void CDX12GraphicPipelineStateDesc::SetDomainShader(CDX12Shader& shader)
	{
		D3D12_SHADER_BYTECODE bytecode;
		getShaderBytecode(&bytecode, shader);

		DS = bytecode;
	}

	void CDX12GraphicPipelineStateDesc::SetHullShader(CDX12Shader& shader)
	{
		D3D12_SHADER_BYTECODE bytecode;
		getShaderBytecode(&bytecode, shader);

		HS = bytecode;
	}

	void CDX12GraphicPipelineStateDesc::SetGeometryShader(CDX12Shader& shader)
	{
		D3D12_SHADER_BYTECODE bytecode;
		getShaderBytecode(&bytecode, shader);

		GS = bytecode;
	}

	void CDX12GraphicPipelineStateDesc::getShaderBytecode(D3D12_SHADER_BYTECODE* pDst, CDX12Shader& shader)
	{
		NG_ASSERT(pDst != nullptr);

		ID3DBlob* pBlob = shader.Interface();
		NG_ASSERT(pBlob != nullptr);

		pDst->pShaderBytecode = pBlob->GetBufferPointer();
		pDst->BytecodeLength = pBlob->GetBufferSize();
	}

}	// namespace ng
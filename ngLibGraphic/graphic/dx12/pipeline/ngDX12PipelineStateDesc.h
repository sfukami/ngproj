/*!
* @file		ngDX12PipelineStateDesc.h
* @brief	DX12グラフィックパイプラインステート記述子
* @date		2019-03-24
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_PIPELINE_STATE_DESC_H__
#define __NG_GRAPHIC_DX12_PIPELINE_STATE_DESC_H__

#include <d3d12.h>

namespace ng
{
	class CDX12RootSignature;
	class CDX12Shader;
}

namespace ng
{
	/*!
	* @brief					DX12グラフィックパイプラインステート 記述子
	*/
	class NG_DECL CDX12PipelineStateDesc : public D3D12_GRAPHICS_PIPELINE_STATE_DESC
	{
	public:
		CDX12PipelineStateDesc();
		~CDX12PipelineStateDesc();

		/*!
		* @brief					初期化
		*							デフォルト値に設定
		*/
		void Initialize();

		/*!
		* @brief					ルートシグネチャ設定
		*/
		void SetRootSignature(CDX12RootSignature& signature);

		/*!
		* @brief					各シェーダーリソース設定
		*/
		void SetVertexShader(CDX12Shader& shader);
		void SetPixelShader(CDX12Shader& shader);
		void SetDomainShader(CDX12Shader& shader);
		void SetHullShader(CDX12Shader& shader);
		void SetGeometryShader(CDX12Shader& shader);

	private:
		void getShaderBytecode(D3D12_SHADER_BYTECODE* pDst, CDX12Shader& shader);
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_PIPELINE_STATE_DESC_H__
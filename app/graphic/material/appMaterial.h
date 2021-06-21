/*!
* @file		appMaterial.h
* @brief	マテリアル
* @date		2020-07-22
* @author	s.fukami
*/

#ifndef __APP_MATERIAL_H__
#define __APP_MATERIAL_H__

#include "ngLibCore/memory/pointer/ngSharedPtr.h"
#include "ngLibCore/memory/pointer/ngWeakPtr.h"
#include "ngLibGraphic/graphic/dx12/descriptor/ngDX12DescriptorHeap.h"
#include "ngLibApp/resource/ngResourceHandle.h"
#include "../texture/appTexture.h"
#include "../shader/appShader.h"

namespace ng
{
	class IResourceHandle;
	class CDX12Device;
	class CDX12CommandList;
	class CDX12RootSignature;
	class CDX12PipelineState;
	enum class eVertexLayout : u32;
}
namespace app
{
	struct ShaderFormat;
	class CShaderEffect;
}

namespace app
{
	/*!
	* @brief					マテリアル
	*/
	class CMaterial
	{
		friend class CMaterialBuilder;

	public:
		CMaterial();
		~CMaterial();

		/*!
		* @brief					生成
		* @param device				DX12デバイス
		* @return					成否
		*/
		bool Create(ng::CDX12Device& device);

		/*!
		* @brief					破棄
		*/
		void Destroy();

		/*!
		* @brief					DX12ルートシグネチャをコマンドリストへ設定
		* @param commandList		DX12コマンドリスト
		*/
		void BindRootSignature(ng::CDX12CommandList& commandList);

		/*!
		* @brief					DX12パイプラインステートをコマンドリストへ設定
		* @param commandList		DX12コマンドリスト
		*/
		void BindPipelineState(ng::CDX12CommandList& commandList);

		/*!
		* @brief					リソースをバインド
		* @param commandList		DX12コマンドリスト
		*/
		void BindResource(ng::CDX12CommandList& commandList);
		
		/*! ディフューズマップ取得 */
		ng::CWeakPtr<CTexture> GetDiffuseMap() const;

		/*! DX12ルートシグネチャ取得 */
		ng::CWeakPtr<ng::CDX12RootSignature> GetRootSignature() const;

		/*! DX12パイプラインステート */
		ng::CWeakPtr<ng::CDX12PipelineState> GetPipelineState() const;

		/*! シェーダーエフェクト取得 */
		ng::CWeakPtr<CShaderEffect> GetShaderEffect() const;

	private:
		void SetDiffuseMap(const ng::CResourceHandle<CTexture>& handle);
		void SetVertexShader(const ng::CResourceHandle<CShader>& handle);
		void SetPixelShader(const ng::CResourceHandle<CShader>& handle);
		void SetRootSignature(const ng::CWeakPtr<ng::CDX12RootSignature>& ptr);
		void SetPipelineState(const ng::CWeakPtr<ng::CDX12PipelineState>& ptr);
		void SetShaderEffect(const ng::CSharedPtr<CShaderEffect>& ptr);

	private:
		ng::CResourceHandle<CTexture> m_diffuseMap;		//!< ディフューズマップ
		ng::CResourceHandle<CShader> m_vertexShader;	//!< 頂点シェーダー
		ng::CResourceHandle<CShader> m_pixelShader;		//!< ピクセルシェーダー
		ng::CWeakPtr<ng::CDX12RootSignature> m_rootSignature;	//!< DX12ルートシグネチャ
		ng::CWeakPtr<ng::CDX12PipelineState> m_pipelineState;	//!< DX12パイプラインステート
		ng::CSharedPtr<CShaderEffect> m_shaderEffect;	//!< シェーダーエフェクト

		ng::CDX12DescriptorHeap m_descHeap;	//!< DX12ディスクリプタヒープ
	};

}	// namespace app

#endif	// __APP_MATERIAL_H__
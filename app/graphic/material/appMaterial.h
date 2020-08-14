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
#include "ngLibApp/resource/ngResource.h"
#include "ngLibApp/resource/ngResourceHandle.h"
#include "../texture/appTexture.h"
#include "../shader/appShader.h"

namespace ng
{
	class IResourceHandle;
	class CDX12CommandList;
	class CDX12RootSignature;
	class CDX12PipelineState;
	enum class eVertexLayout : u32;
}
namespace app
{
	struct MaterialData;
	struct ShaderData;
	class CShaderEffect;
}

namespace app
{
	/*!
	* @brief					マテリアル
	*/
	class CMaterial : public ng::IResource
	{
	public:
		CMaterial();
		~CMaterial();

		/*!
		* @brief					リソース構築
		* @param pBinary			リソースバイナリ
		* @param size				リソースバイナリのサイズ
		* @param pBuildParam		ビルドパラメータ
		* @return					成否
		*/
		bool Build(const void* pBinary, ng::size_type size, const void* pBuildParam);

		/*!
		* @brief					破棄
		*/
		void Destroy();

		/*!
		* @brief					コンスタントバッファ更新
		*/
		void UpdateConstantBuffer();

		/*!
		* @brief					リソースをバインド
		* @param commandList		DX12コマンドリスト
		*/
		void BindResource(ng::CDX12CommandList& commandList);

		/*!
		* @brief					DX12ルートシグネチャをコマンドリストへ設定
		* @param commandList		DX12コマンドリスト
		*/
		void SetRootSignature(ng::CDX12CommandList& commandList);
		
		/*!
		* @brief					DX12パイプラインステートをコマンドリストへ設定
		* @param commandList		DX12コマンドリスト
		*/
		void SetPipelineState(ng::CDX12CommandList& commandList);

		/*! ディフューズマップ取得 */
		ng::CWeakPtr<CTexture> GetDiffuseMap() const;

		/*! シェーダーエフェクト取得 */
		ng::CWeakPtr<CShaderEffect> GetShaderEffect() const;

		/*! DX12ルートシグネチャ取得 */
		ng::CWeakPtr<ng::CDX12RootSignature> GetRootSignature() const;

		/*! DX12パイプラインステート */
		ng::CWeakPtr<ng::CDX12PipelineState> GetPipelineState() const;

	private:
		/*!
		* @brief					マテリアル構築
		* @param data				マテリアルデータ
		* @return					成否
		*/
		bool _build(const MaterialData& data);

		/*! リソース読み込み */
		bool _loadResource(const char* filePath, const void* pBuildParam, ng::IResourceHandle& handle);
		/*! シェーダーリソース読み込み */
		bool _loadShaderResource(const ShaderData& shaderData, ng::IResourceHandle& handle);
		/*! DX12ルートシグネチャ取得 */
		bool _findRootSignature(const char* name);
		/*! DX12パイプラインステート生成 */
		bool _createPipelineState(const char* name, ng::eVertexLayout vertexLayout);
		/*! シェーダーエフェクト生成 */
		bool _createShaderEffect(const char* name);

	private:
		ng::CResourceHandle<CTexture> m_diffuseMap;		//!< ディフューズマップ
		ng::CResourceHandle<CShader> m_vertexShader;	//!< 頂点シェーダー
		ng::CResourceHandle<CShader> m_pixelShader;		//!< ピクセルシェーダー

		ng::CWeakPtr<ng::CDX12RootSignature> m_rootSignature;	//!< DX12ルートシグネチャ
		ng::CWeakPtr<ng::CDX12PipelineState> m_pipelineState;	//!< DX12パイプラインステート
		ng::CSharedPtr<CShaderEffect> m_shaderEffect;	//!< シェーダーエフェクト
	};

}	// namespace app

#endif	// __APP_MATERIAL_H__
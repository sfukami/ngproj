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
		* @brief					ディフューズマップ取得
		* @param dstPtr				ディフューズマップの格納先
		* @return					成否。リソースが無効な場合はfalse
		*/
		bool GetDiffuseMap(ng::CWeakPtr<CTexture>& dstPtr) const;

		/*!
		* @brief					シェーダーエフェクト取得
		* @param dstPtr				シェーダーエフェクトの格納先
		* @return					成否。リソースが無効な場合はfalse
		*/
		bool GetShaderEffect(ng::CWeakPtr<CShaderEffect>& dstPtr) const;

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
		/*! DX12パイプラインステート取得 */
		bool _findPipelineState(const char* name, ng::eVertexLayout vertexLayout);
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
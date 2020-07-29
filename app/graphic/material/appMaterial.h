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
#include "ngLibApp/resource/ngResourceHandle.h"
#include "../texture/appTexture.h"
#include "../shader/appShader.h"

namespace ng
{
	class IResourceHandle;
	class CDX12RootSignature;
	class CDX12PipelineState;
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
	class CMaterial
	{
	public:
		CMaterial();
		~CMaterial();

		/*!
		* @brief					マテリアル構築
		* @param data				マテリアルデータ
		* @return					成否
		*/
		bool Build(const MaterialData& data);

		/*!
		* @brief					破棄
		*/
		void Destroy();

	private:
		/*! リソース読み込み */
		bool _loadResource(const char* filePath, const void* pBuildParam, ng::IResourceHandle& handle);
		/*! シェーダーリソース読み込み */
		bool _loadShaderResource(const ShaderData& shaderData, ng::IResourceHandle& handle);

	private:
		ng::CResourceHandle<CTexture> m_diffuseMap;		//!< ディフューズマップ
		ng::CResourceHandle<CShader> m_vertexShader;	//!< 頂点シェーダー
		ng::CResourceHandle<CShader> m_pixelShader;		//!< ピクセルシェーダー

		ng::CWeakPtr<ng::CDX12RootSignature> m_rootSign;	//!< DX12ルートシグネチャ
		ng::CWeakPtr<ng::CDX12PipelineState> m_plState;		//!< DX12パイプラインステート
		ng::CSharedPtr<CShaderEffect> m_shEff;	//!< シェーダーエフェクト
	};

}	// namespace app

#endif	// __APP_MATERIAL_H__
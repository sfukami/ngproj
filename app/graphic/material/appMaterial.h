/*!
* @file		appMaterial.h
* @brief	マテリアル
* @date		2020-07-22
* @author	s.fukami
*/

#ifndef __APP_MATERIAL_H__
#define __APP_MATERIAL_H__

#include "ngLibApp/resource/ngResourceHandle.h"
#include "app/graphic/texture/appTexture.h"
#include "app/graphic/shader/appShader.h"

namespace ng
{
	class IResourceHandle;
}
namespace app
{
	struct MaterialData;
	struct ShaderData;
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
	};

}	// namespace app

#endif	// __APP_MATERIAL_H__
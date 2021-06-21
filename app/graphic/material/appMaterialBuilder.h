/*!
* @file		appMaterialBuilder.h
* @brief	マテリアルビルダー
* @date		2021-06-14
* @author	s.fukami
*/

#ifndef __APP_MATERIAL_BUILDER_H__
#define __APP_MATERIAL_BUILDER_H__

#include "app/resource/appResourceModule.h"

namespace ng
{
	class IResourceHandle;
	template <class T> class CSharedPtr;
	template <class T> class CWeakPtr;
	class CDX12RootSignature;
	class CDX12PipelineState;
	class CDX12PipelineStateDesc;
	enum class eVertexLayout : u32;
}
namespace app
{
	struct MaterialFormat;
	struct TextureFormat;
	struct ShaderFormat;
	class CMaterial;
	class CShader;
	class CShaderEffect;
}

namespace app
{
	/*!
	* @brief					マテリアルビルダー
	*/
	class CMaterialBuilder
	{
	public:
		CMaterialBuilder();
		~CMaterialBuilder();

		/*!
		* @brief					マテリアル生成
		* @param data				マテリアルフォーマット
		* @param pDst				格納先のマテリアル
		* @return					成否
		*/
		bool Build(const MaterialFormat& format, CMaterial* pDst) const;

	private:
		/*! テクスチャリソース読み込み */
		bool _loadTextureResource(const char* matName, const TextureFormat& format, ng::IResourceHandle& handle) const;
		/*! シェーダーリソース読み込み */
		bool _loadShaderResource(const char* matName, const ShaderFormat& format, ng::IResourceHandle& handle) const;

		/*! DX12ルートシグネチャ取得 */
		bool _findRootSignature(const char* name, ng::CWeakPtr<ng::CDX12RootSignature>& dstPtr) const;
		/*! DX12パイプラインステート生成 */
		bool _createPipelineState(
			const char* name, const ng::CDX12PipelineStateDesc& desc, ng::CWeakPtr<ng::CDX12PipelineState>& dstPtr
			) const;
		/*! シェーダーエフェクト生成 */
		bool _createShaderEffect(const char* name, ng::CSharedPtr<CShaderEffect>& dstPtr) const;

		/*! リソースメモリタイプ取得 */
		eResourceMemoryType _getResourceMemoryType() const;
	};

}	// namespace app

#endif	// __APP_MATERIAL_BUILDER_H__
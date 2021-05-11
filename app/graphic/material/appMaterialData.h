/*!
* @file		appMaterialData.h
* @brief	マテリアルデータ
* @date		2021-05-11
* @author	s.fukami
*/

#ifndef __APP_MATERIAL_DATA_H__
#define __APP_MATERIAL_DATA_H__

#include "ngLibApp/resource/ngResource.h"
#include "appMaterialFormat.h"

namespace ng
{
	enum class eVertexLayout : u32;
}

namespace app
{
	/*!
	* @brief					マテリアルデータ
	*/
	class CMaterialData : public ng::IResource
	{
	public:
		CMaterialData();
		~CMaterialData();

		/*!
		* @brief					リソース構築
		* @param pBinary			リソースバイナリ
		* @param size				リソースバイナリのサイズ
		* @param pBuildParam		ビルドパラメータ
		* @return					成否
		*/
		bool Build(const void* pBinary, ng::size_type size, const void* pBuildParam);

		/*!
		* @brief					マテリアルフォーマット設定
		*/
		void SetFormat(const MaterialFormat& matFormat);

		/*!
		* @brief					マテリアル名設定
		*/
		void SetMaterialName(const char* name);
		/*!
		* @brief					ルートシグネチャ名設定
		*/
		void SetRootSignatureName(const char* name);
		/*!
		* @brief					パイプラインステート名設定
		*/
		void SetPipelineStateName(const char* name);
		/*!
		* @brief					シェーダーエフェクト名設定
		*/
		void SetShaderEffectName(const char* name);

		/*!
		* @brief					頂点レイアウト設定
		*/
		void SetVertexLayout(ng::eVertexLayout vertexLayout);

		/*!
		* @brief					頂点シェーダー ファイルパス設定
		*/
		void SetVSFilePath(const char* filePath);
		/*!
		* @brief					頂点シェーダー エントリポイント設定
		*/
		void SetVSEntryPoint(const char* entryPoint);
		/*!
		* @brief					頂点シェーダー ビルドターゲット設定
		*/
		void SetVSTarget(const char* target);

		/*!
		* @brief					ピクセルシェーダー ファイルパス設定
		*/
		void SetPSFilePath(const char* filePath);
		/*!
		* @brief					ピクセルシェーダー エントリポイント設定
		*/
		void SetPSEntryPoint(const char* entryPoint);
		/*!
		* @brief					ピクセルシェーダー ビルドターゲット設定
		*/
		void SetPSTarget(const char* target);

		/*!
		* @brief					ディフューズマップ ファイルパス設定
		*/
		void SetDiffuseMapFilePath(const char* filePath);

		/*!
		* @brief					マテリアルフォーマット取得
		*/
		const MaterialFormat& GetFormat() const;

	private:
		/*! 各シェーダー設定関数 */
		void _setShaderFilePath(ShaderFormat* pShaderFormat, const char* filePath);
		void _setShaderEntryPoint(ShaderFormat* pShaderFormat, const char* entryPoint);
		void _setShaderTarget(ShaderFormat* pShaderFormat, const char* target);

		/*! テクスチャ設定関数 */
		void _setTextureFilePath(TextureFormat* pTextureFormat, const char* filePath);

	private:
		MaterialFormat m_matFormat;	//!< マテリアルフォーマット
	};

}	// namespace app

#endif	// __APP_MATERIAL_DATA_H__
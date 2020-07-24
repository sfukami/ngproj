/*!
* @file		appMaterialFormat.h
* @brief	マテリアルフォーマット
* @date		2020-07-22
* @author	s.fukami
*/

#ifndef __APP_MATERIAL_FORMAT_H__
#define __APP_MATERIAL_FORMAT_H__

namespace app
{
	/*!
	* @brief					テクスチャデータ
	*/
	struct TextureData
	{
		TextureData();
		void SetFilePath(const char* _filePath);

		char filePath[256];	//!< ファイルパス
		void* pBinary;		//!< バイナリへの参照
	};

	/*!
	* @brief					シェーダーデータ
	*/
	struct ShaderData
	{
		ShaderData();
		void SetFilePath(const char* _filePath);
		void SetEntryPoint(const char* _entryPoint);
		void SetTarget(const char* _target);

		char filePath[256];		//!< ファイルパス
		char entryPoint[32];	//!< エントリポイント
		char target[8];		//!< ビルドターゲット
		void* pBinary;		//!< バイナリへの参照
	};

	/*!
	* @brief					マテリアルデータ
	*/
	struct MaterialData
	{
		MaterialData();

		// テクスチャデータ
		TextureData diffuseMap;	//!< ディフューズマップ

		// シェーダーデータ
		ShaderData vertexShader;	//!< 頂点シェーダー
		ShaderData pixelShader;		//!< ピクセルシェーダー
	};

}	// namespace app

#endif	//__APP_MATERIAL_FORMAT_H__

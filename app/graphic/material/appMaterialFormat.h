/*!
* @file		appMaterialFormat.h
* @brief	マテリアルフォーマット
* @date		2020-07-22
* @author	s.fukami
*/

#ifndef __APP_MATERIAL_FORMAT_H__
#define __APP_MATERIAL_FORMAT_H__

#include "ngLibGraphic/graphic/dx12/polygon/ngDX12VertexLayout.h"

namespace app
{
	/*!
	* @brief					テクスチャフォーマット
	*/
	struct TextureFormat
	{
		TextureFormat();
		void SetFilePath(const char* _filePath);
		void SetName(const char* _name);

		union {
			char filePath[256];		//!< ファイルパス
			char name[256];		//!< 名称
		};
		const void* pBinary;	//!< バイナリへの参照
		ng::u32 size;	//!< バイナリのサイズ（バイト）
	};

	/*!
	* @brief					シェーダーフォーマット
	*/
	struct ShaderFormat
	{
		ShaderFormat();
		void SetFilePath(const char* _filePath);
		void SetEntryPoint(const char* _entryPoint);
		void SetTarget(const char* _target);

		char filePath[256];		//!< ファイルパス
		char entryPoint[32];	//!< エントリポイント
		char target[8];		//!< ビルドターゲット
		const void* pBinary;	//!< バイナリへの参照
		ng::u32 size;	//!< バイナリのサイズ（バイト）
	};

	/*!
	* @brief					マテリアルフォーマット
	*/
	struct MaterialFormat
	{
		MaterialFormat();
		void SetMaterialName(const char* _name);
		void SetRootSignatureName(const char* _name);
		void SetPipelineStateName(const char* _name);
		void SetShaderEffectName(const char* _name);

		char name[32];		//!< マテリアル名

		char rootSignatureName[32];	//!< ルートシグネチャ名
		char pipelineStateName[32];	//!< パイプラインステート名
		char shaderEffectName[32];	//!< シェーダーエフェクト名
		
		ng::eVertexLayout vertexLayout;	//!< 頂点レイアウト
		
		// テクスチャデータ
		TextureFormat diffuseMap;	//!< ディフューズマップ

		// シェーダーデータ
		ShaderFormat vertexShader;	//!< 頂点シェーダー
		ShaderFormat pixelShader;	//!< ピクセルシェーダー
	};

}	// namespace app

#endif	//__APP_MATERIAL_FORMAT_H__

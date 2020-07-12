/*!
* @file		ngDX12TextureLoader.h
* @brief	DX12テクスチャローダー
* @date		2019-08-13
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_TEXTURE_LOADER_H__
#define __NG_GRAPHIC_DX12_TEXTURE_LOADER_H__

#include <DXGIFormat.h>
#include "ngDX12TextureLoaderFlag.h"

namespace DirectX
{
	class ScratchImage;
}
namespace ng
{
	class CDX12Device;
	class CDX12Texture;
	enum class NG_WIC_FLAGS : u32;
	enum class NG_DDS_FLAGS : u32;
}

namespace ng
{
	/*!
	* @brief					DX12テクスチャローダー
	* 
	* ScratchImageクラス や フラグ に関して
	* 	https://github.com/microsoft/DirectXTex/wiki/WIC-I-O-Functions
	*/
	class NG_DECL CDX12TextureLoader
	{
	public:
		CDX12TextureLoader();
		~CDX12TextureLoader();

		/*!
		* @brief					ファイルより画像(bmp, jpg, png等)を読み込み
		* @param device				DX12デバイス
		* @param dstTex				生成したDX12テクスチャの格納先
		* @param pFileName			ファイル名
		* @param flags				フラグ : https://github.com/microsoft/DirectXTex/wiki/WIC-I-O-Functions
		* @param index				画像データのインデックス
		* @return					NG エラーコード
		*/
		NG_ERRCODE LoadTextureWICFromFile(
			CDX12Device& device,
			CDX12Texture& dstTex,
			const wchar_t* pFileName,
			NG_WIC_FLAGS flags = NG_WIC_FLAGS::NONE,
			u32 index = 0
			) const;

		/*!
		* @brief					ファイルより画像(dds)を読み込み
		* @param device				DX12デバイス
		* @param dstTex				生成したDX12テクスチャの格納先
		* @param pFileName			ファイル名
		* @param flags				フラグ
		* @param index				画像データのインデックス
		* @return					NG エラーコード
		*/
		NG_ERRCODE LoadTextureDDSFromFile(
			CDX12Device& device,
			CDX12Texture& dstTex,
			const wchar_t* pFileName,
			NG_DDS_FLAGS flags = NG_DDS_FLAGS::NONE,
			u32 index = 0
			) const;

		/*!
		* @brief					システムメモリより画像(bmp, jpg, png等)を読み込み
		* @param device				DX12デバイス
		* @param dstTex				生成したDX12テクスチャの格納先
		* @param pSource			画像データへのアドレス
		* @param size				画像データのサイズ
		* @param flags				フラグ : https://github.com/microsoft/DirectXTex/wiki/WIC-I-O-Functions
		* @param index				画像データのインデックス
		* @return					NG エラーコード
		*/
		NG_ERRCODE LoadTextureWICFromMemory(
			CDX12Device& device,
			CDX12Texture& dstTex,
			const void* pSource,
			size_type size,
			NG_WIC_FLAGS flags = NG_WIC_FLAGS::NONE,
			u32 index = 0
			) const;

		/*!
		* @brief					システムメモリより画像(dds)を読み込み
		* @param device				DX12デバイス
		* @param dstTex				生成したDX12テクスチャの格納先
		* @param pSource			画像データへのアドレス
		* @param size				画像データのサイズ
		* @param flags				フラグ
		* @param index				画像データのインデックス
		* @return					NG エラーコード
		*/
		NG_ERRCODE LoadTextureDDSFromMemory(
			CDX12Device& device,
			CDX12Texture& dstTex,
			const void* pSource,
			size_type size,
			NG_DDS_FLAGS flags = NG_DDS_FLAGS::NONE,
			u32 index = 0
			) const;

	private:
		/*! DX12テクスチャ生成 */
		NG_ERRCODE _createDX12Texture(
			CDX12Device& device,
			CDX12Texture& dstTex,
			DirectX::ScratchImage& scratchImage,
			u32 index
			) const;

		/*! テクスチャ読み込み(WIC) */
		NG_ERRCODE _loadTextureFromFile(
			const wchar_t* pFileName,
			DirectX::ScratchImage& scratchImage,
			NG_WIC_FLAGS flags
			) const;

		/*! テクスチャ読み込み(DDS) */
		NG_ERRCODE _loadTextureFromFile(
			const wchar_t* pFileName,
			DirectX::ScratchImage& scratchImage,
			NG_DDS_FLAGS flags
			) const;

		/*! テクスチャ読み込み(WIC) */
		NG_ERRCODE _loadTextureFromMemory(
			const void* pSource,
			size_type size,
			DirectX::ScratchImage& scratchImage,
			NG_WIC_FLAGS flags
			) const;

		/*! テクスチャ読み込み(DDS) */
		NG_ERRCODE _loadTextureFromMemory(
			const void* pSource,
			size_type size,
			DirectX::ScratchImage& scratchImage,
			NG_DDS_FLAGS flags
			) const;
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_TEXTURE_LOADER_H__
/*!
* @file		ngDX12TextureLoader.cpp
* @brief	DX12テクスチャローダー
* @date		2019-08-13
* @author	s.fukami
*/

#include <DirectXTex.h>
#include "ngLibCore/common/ngCommon.h"
#include "../common/ngDX12Common.h"
#include "ngDX12TextureLoader.h"
#include "../texture/ngDX12Texture.h"

namespace ng
{
	CDX12TextureLoader::CDX12TextureLoader()
	{
	}
	CDX12TextureLoader::~CDX12TextureLoader()
	{
	}

	NG_ERRCODE CDX12TextureLoader::LoadTextureWICFromMemory(
		CDX12Device& device,
		CDX12Texture& dstTex,
		const void* pSource,
		size_type size,
		NG_WIC_FLAGS flags,
		u32 index
		)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		DirectX::ScratchImage scratchImage;

		// 画像読み込み
		if(NG_FAILED(ret = _loadTextureFromMemory(
			pSource, size, scratchImage, flags
			))) {
			return ret;
		}

		// DX12テクスチャ生成
		if(NG_FAILED(ret = _createDX12Texture(
			device, dstTex, scratchImage, index
			))) {
			return ret;
		}

		return ret;
	}

	NG_ERRCODE CDX12TextureLoader::LoadTextureDDSFromMemory(
		CDX12Device& device,
		CDX12Texture& dstTex,
		const void* pSource,
		size_type size,
		NG_DDS_FLAGS flags,
		u32 index
		)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		DirectX::ScratchImage scratchImage;

		// 画像読み込み
		if(NG_FAILED(ret = _loadTextureFromMemory(
			pSource, size, scratchImage, flags
			))) {
			return ret;
		}

		// DX12テクスチャ生成
		if(NG_FAILED(ret = _createDX12Texture(
			device, dstTex, scratchImage, index
			))) {
			return ret;
		}

		return ret;
	}

	NG_ERRCODE CDX12TextureLoader::_createDX12Texture(
		CDX12Device& device,
		CDX12Texture& dstTex,
		DirectX::ScratchImage& scratchImage,
		u32 index
		)
	{
		// 指定インデックスの画像が存在するか
		size_t imageNum = scratchImage.GetImageCount();
		if(index >= imageNum) {
			return eNG_E_FAIL;
		}

		const DirectX::Image* pImages = scratchImage.GetImages();
		const DirectX::Image& srcImage = pImages[index];

		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// DX12テクスチャ生成
		if(NG_FAILED(ret = dstTex.Create(
			device,
			srcImage.pixels,
			static_cast<u32>(srcImage.width),
			static_cast<u32>(srcImage.height)
			))) {
			NG_ERRLOG_C("DX12TextureLoader", ret, "DX12テクスチャの生成に失敗しました.");
			return ret;
		}

		return ret;
	}

	NG_ERRCODE CDX12TextureLoader::_loadTextureFromMemory(
		const void* pSource,
		size_type size,
		DirectX::ScratchImage& scratchImage,
		NG_WIC_FLAGS flags
		) const
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		if(NG_FAILED(ret = DirectX::LoadFromWICMemory(
			pSource, size, static_cast<DirectX::WIC_FLAGS>(flags), nullptr, scratchImage
			))) {
			NG_DXERRLOG("DX12TextureLoader", ret, DirectX::LoadFromWICMemory, "画像の読み込みに失敗しました.");
			return ret;
		}

		return ret;
	}

	NG_ERRCODE CDX12TextureLoader::_loadTextureFromMemory(
		const void* pSource,
		size_type size,
		DirectX::ScratchImage& scratchImage,
		NG_DDS_FLAGS flags
		) const
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		if(NG_FAILED(ret = DirectX::LoadFromDDSMemory(
			pSource, size, static_cast<DirectX::DDS_FLAGS>(flags), nullptr, scratchImage
			))) {
			NG_DXERRLOG("DX12TextureLoader", ret, DirectX::LoadFromDDSMemory, "画像の読み込みに失敗しました.");
			return ret;
		}

		return ret;
	}

}	// namespace ng
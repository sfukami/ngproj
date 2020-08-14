/*!
* @file		appTexture.cpp
* @brief	テクスチャ
* @date		2020-07-21
* @author	s.fukami
*/

#include "ngLibGraphic/graphic/dx12/ngDX12Util.h"
#include "ngLibGraphic/graphic/dx12/texture/ngDX12TextureLoader.h"
#include "appTexture.h"

namespace app
{
	CTexture::CTexture()
	{
	}
	CTexture::~CTexture()
	{
		Destroy();
	}

	bool CTexture::Build(const void* pBinary, ng::size_type size, const void* pBuildParam)
	{
		NG_ERRCODE err = NG_ERRCODE_DEFAULT;
		ng::CDX12TextureLoader loader;

		ng::CDX12Device* pDX12Device = ng::DX12Util::GetDevice();
		NG_ASSERT_NOT_NULL(pDX12Device);

		// DX12テクスチャ生成
		if(NG_FAILED(err = loader.LoadTextureWICFromMemory(
			*pDX12Device,
			m_texture,
			pBinary, size
			))) {
			NG_ERRLOG_C("Texture", err, "テクスチャの生成に失敗しました.");
			return false;
		}

		return true;
	}

	void CTexture::Destroy()
	{
		m_texture.Destroy();
	}

	ng::CDX12Texture& CTexture::GetTexture()
	{
		return m_texture;
	}
	const ng::CDX12Texture& CTexture::GetTexture() const
	{
		return m_texture;
	}

}	// namespace app
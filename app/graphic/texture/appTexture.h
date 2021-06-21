/*!
* @file		appTexture.h
* @brief	テクスチャ
* @date		2020-07-21
* @author	s.fukami
*/

#ifndef __APP_TEXTURE_H__
#define __APP_TEXTURE_H__

#include "ngLibApp/resource/ngResource.h"
#include "ngLibGraphic/graphic/dx12/texture/ngDX12Texture.h"

namespace app
{
	/*!
	* @brief					テクスチャ
	*/
	class CTexture : public ng::IResource
	{
	public:
		CTexture();
		~CTexture();

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
		* @brief					リソースタイプ取得
		*/
		int GetResourceType() const;
		
		/*!
		* @brief					DX12テクスチャ取得
		*/
		ng::CDX12Texture& GetTexture();
		const ng::CDX12Texture& GetTexture() const;

	private:
		ng::CDX12Texture m_texture;	//!< DX12テクスチャ
	};

}	// namespace app
#endif	// __APP_TEXTURE_H__
/*!
* @file		ngDX12Texture.h
* @brief	DX12テクスチャ
* @date		2019-07-31
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_TEXTURE_H__
#define __NG_GRAPHIC_DX12_TEXTURE_H__

#include <DXGIFormat.h>
#include "../resource/ngDX12Resource.h"

namespace ng
{
	class CDX12Device;
	class CDX12DescriptorHeap;
}

namespace ng
{
	/*!
	* @brief					DX12テクスチャ
	*/
	class NG_DECL CDX12Texture
	{
	public:
		CDX12Texture();
		~CDX12Texture();

		/*!
		* @brief					DX12テクスチャ生成
		* @param device				DX12デバイス
		* @param pTexData			テクスチャデータ
		* @param width				テクスチャの幅
		* @param height				テクスチャの高さ
		* @param format				DXGIフォーマット
		* @return					NG エラーコード
		*/
		NG_ERRCODE Create(
			CDX12Device& device,
			const void* pTexData,
			u32 width,
			u32 height,
			DXGI_FORMAT format
			);

		/*!
		* @brief					リソースビュー生成
		* @param device				DX12デバイス
		* @param heap				DX12ディスクリプタヒープ
		* @param heapIdx			ディスクリプタヒープ内のインデックス
		*/
		void CreateResourceView(
			CDX12Device& device,
			CDX12DescriptorHeap& heap,
			u32 heapIdx
			);

		/*!
		* @brief					破棄
		*/
		void Destroy();

		/*!
		* @brief					有効か
		*/
		bool IsValid() const;

		/*!
		* @brief					DX12リソース取得
		*/
		CDX12Resource& GetResource();
		const CDX12Resource& GetResource() const;

	private:
		CDX12Resource m_resource;	//!< DX12リソース
		DXGI_FORMAT m_format;	//!< DXGIフォーマット
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_TEXTURE_H__
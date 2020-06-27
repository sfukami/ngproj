/*!
* @file		ngDX12IndexBuffer.h
* @brief	DX12インデックスバッファ
* @date		2019-07-25
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_INDEX_BUFFER_H__
#define __NG_GRAPHIC_DX12_INDEX_BUFFER_H__

#include <d3d12.h>
#include "../resource/ngDX12Resource.h"

namespace ng
{
	class CDX12Device;
}

namespace ng
{
	/*!
	* @brief					DX12インデックスバッファ
	*/
	class NG_DECL CDX12IndexBuffer
	{
	public:
		CDX12IndexBuffer();
		~CDX12IndexBuffer();

		/*!
		* @brief					DX12インデックスバッファ生成
		* @param device				DX12デバイス
		* @param pIndices			インデックスデータ
		* @param size				インデックスデータサイズ
		* @return					NG エラーコード
		*/
		NG_ERRCODE Create(
			CDX12Device& device,
			const void* pIndices,
			u32 size
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

		/*!
		* @brief					インデックスバッファビュー記述を取得
		*/
		const D3D12_INDEX_BUFFER_VIEW& GetIndexBufferView() const;

		/*!
		* @brief					インデックス数取得
		*/
		u32 GetIndexNum() const;

	private:
		CDX12Resource m_resource;	//!< DX12リソース
		D3D12_INDEX_BUFFER_VIEW m_view;	//!< インデックスバッファビュー記述
		u32 m_indexNum;		//!< インデックス数
	};
	
}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_INDEX_BUFFER_H__
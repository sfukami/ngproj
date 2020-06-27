/*!
* @file		ngDX12VertexBuffer.h
* @brief	DX12頂点バッファ
* @date		2018-01-20
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_VERTEX_BUFFER_H__
#define __NG_GRAPHIC_DX12_VERTEX_BUFFER_H__

#include <d3d12.h>
#include "../resource/ngDX12Resource.h"

namespace ng
{
	class CDX12Device;
}

namespace ng
{
	/*!
	* @brief					DX12頂点バッファ
	*/
	class NG_DECL CDX12VertexBuffer
	{
	public:
		CDX12VertexBuffer();
		~CDX12VertexBuffer();

		/*!
		* @brief					DX12頂点バッファ生成
		* @param device				DX12デバイス
		* @param pVertices			頂点データ
		* @param size				頂点データサイズ
		* @param stride				頂点データ間隔のサイズ
		* @return					NG エラーコード
		*/
		NG_ERRCODE Create(
			CDX12Device& device,
			const void* pVertices,
			u32 size,
			u32 stride
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
		* @brief					頂点バッファビュー記述を取得
		*/
		const D3D12_VERTEX_BUFFER_VIEW& GetVertexBufferView() const;
		
		/*!
		* @brief					頂点数取得
		*/
		u32 GetVertexNum() const;

	private:
		CDX12Resource m_resource;	//!< DX12リソース
		D3D12_VERTEX_BUFFER_VIEW m_view;	//!< 頂点バッファビュー記述
		u32 m_vertexNum;		//!< 頂点数
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_VERTEX_BUFFER_H__
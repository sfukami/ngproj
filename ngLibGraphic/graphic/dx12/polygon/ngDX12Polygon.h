/*!
* @file		ngDX12Polygon.h
* @brief	DX12ポリゴン
* @date		2018-07-27
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_POLYGON_H__
#define __NG_GRAPHIC_DX12_POLYGON_H__

#include <d3dcommon.h>
#include "../primitive/ngDX12VertexBuffer.h"
#include "../primitive/ngDX12IndexBuffer.h"

namespace ng
{
	class CDX12Device;
	class CDX12CommandList;
}

namespace ng
{
	/*!
	* @brief					DX12ポリゴン
	*/
	class NG_DECL CDX12Polygon
	{
	public:
		CDX12Polygon();
		~CDX12Polygon();

		/*!
		* @brief					DX12頂点バッファ生成
		* @param device				DX12デバイス
		* @param pVertices			頂点データ
		* @param vertexDataSize		頂点データサイズ
		* @param vertexStride		頂点データ間隔のサイズ
		* @param primitiveTopology	プリミティブトポロジ
		* @param pIndices			インデックスデータ
		* @param indexDataSize		インデックスデータサイズ
		* @return					NG エラーコード
		*/
		NG_ERRCODE Create(
			CDX12Device& device,
			const void* pVertices,
			u32 vertexDataSize,
			u32 vertexStride,
			D3D_PRIMITIVE_TOPOLOGY primitiveTopology,
			const u32* pIndices = nullptr,
			u32 indexDataSize = 0
			);

		/*!
		* @brief					描画
		* @param commandList		DX12コマンドリスト
		*/
		void Render(
			CDX12CommandList& commandList
			) const;

		/*!
		* @brief					破棄
		*/
		void Destroy();

		/*!
		* @brief					有効か
		*/
		bool IsValid() const;
		
	private:
		D3D_PRIMITIVE_TOPOLOGY m_primitiveTopology;	//!< プリミティブトポロジ
		CDX12VertexBuffer m_vb;	//!< DX12頂点バッファ
		CDX12IndexBuffer m_ib;	//!< DX12インデックスバッファ
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_POLYGON_H__
﻿/*!
* @file		ngDX12MeshSquare.h
* @brief	DX12ポリゴン 矩形
* @date		2018-07-27
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_SHAPE_SQUARE_H__
#define __NG_GRAPHIC_DX12_SHAPE_SQUARE_H__

#include "../ngDX12Polygon.h"

namespace ng
{
	class CDX12Device;
	class CDX12CommandList;
	struct DX12VertexLayout;
}

namespace ng
{
	/*!
	* @brief					DX12ポリゴン 矩形
	*/
	class NG_DECL CDX12ShapeSquare
	{
	public:
		CDX12ShapeSquare();
		~CDX12ShapeSquare();

		/*!
		* @brief					DX12ポリゴン 矩形を生成
		* @param device				DX12デバイス
		* @param width				幅
		* @param height				高さ
		* @@param isSprite			スプライトか
		* @return					NG エラーコード
		*/
		NG_ERRCODE Create(
			CDX12Device& device
			, float width
			, float height
			, bool isSprite
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
		
		/*! 頂点レイアウト取得 */
		const DX12VertexLayout& GetVertexLayout() const;

	private:
		/*! DX12ポリゴン生成 */
		NG_ERRCODE _createPolygon(CDX12Device& device, const void* pVertices, u32 vertexDataSize, u32 vertexStride);

	private:
		CDX12Polygon m_polygon;	//!< DX12ポリゴン
		bool m_isSprite;	//!< スプライトか
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_SHAPE_SQUARE_H__
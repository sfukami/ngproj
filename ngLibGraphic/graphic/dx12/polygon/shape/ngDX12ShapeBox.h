/*!
* @file		ngDX12ShapeBox.h
* @brief	DX12ポリゴン ボックス
* @date		2018-07-28
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_SHAPE_BOX_H__
#define __NG_GRAPHIC_DX12_SHAPE_BOX_H__

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
	* @brief					DX12ポリゴン ボックス
	*/
	class NG_DECL CDX12ShapeBox
	{
	public:
		CDX12ShapeBox();
		~CDX12ShapeBox();

		/*!
		* @brief					DX12ポリゴン生成
		* @param device				DX12デバイス
		* @param width				幅
		* @param height				高さ
		* @param depth				奥行
		* @return					NG エラーコード
		*/
		NG_ERRCODE Create(
			CDX12Device& device
			, float width
			, float height
			, float depth
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

		/*! 頂点レイアウト取得 */
		const DX12VertexLayout* GetVertexLayout() const;

	private:
		CDX12Polygon m_polygon;	//!< DX12ポリゴン
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_SHAPE_BOX_H__
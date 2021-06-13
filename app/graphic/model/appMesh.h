/*!
* @file		appMesh.h
* @brief	メッシュ
* @date		2021-06-13
* @author	s.fukami
*/

#ifndef __APP_MESH_H__
#define __APP_MESH_H__

#include "ngLibCore/container/list/intrusive/ngIntrusiveListNode.h"
#include "ngLibGraphic/graphic/dx12/polygon/ngDX12Polygon.h"

namespace ng
{
	class CDX12CommandList;
}

namespace app
{
	/*!
	* @brief					メッシュ
	*/
	class CMesh : public ng::CIntrusiveListNode<CMesh>
	{
	public:
		CMesh();
		~CMesh();

		/*!
		* @brief					メッシュ生成
		* @param pVertices			頂点データ
		* @param verticesSize		頂点データサイズ
		* @param pIndices			インデックスデータ
		* @param indicesSize		インデックスデータサイズ
		* @return					成否
		*/
		bool Create(const void* pVertices, ng::u32 verticesSize, const ng::u32* pIndices, ng::u32 indicesSize);

		/*!
		* @brief					破棄
		*/
		void Destroy();

		/*!
		* @brief					描画
		* @param commandList		DX12コマンドリスト
		*/
		void Render(
			ng::CDX12CommandList& commandList
			) const;

	private:
		ng::CDX12Polygon m_polygon;	//!< DX12ポリゴン
	};

}	// namespace app

#endif	// __APP_MESH_H__
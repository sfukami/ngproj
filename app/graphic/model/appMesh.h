/*!
* @file		appMesh.h
* @brief	メッシュ
* @date		2021-06-13
* @author	s.fukami
*/

#ifndef __APP_MESH_H__
#define __APP_MESH_H__

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
	class CMesh
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
		* @param materialIndex		マテリアルのインデックス
		* @return					成否
		*/
		bool Create(
			const void* pVertices, ng::u32 verticesSize, const ng::u32* pIndices, ng::u32 indicesSize, ng::u32 materialIndex
			);

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

		/*! マテリアルのインデックスを取得 */
		ng::u32 GetMaterialIndex() const;
		
	private:
		ng::CDX12Polygon m_polygon;	//!< DX12ポリゴン
		ng::u32 m_materialIndex;	//!< マテリアルのインデックス
	};

}	// namespace app

#endif	// __APP_MESH_H__
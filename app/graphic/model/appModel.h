/*!
* @file		appModel.h
* @brief	モデル
* @date		2021-06-13
* @author	s.fukami
*/

#ifndef __APP_MODEL_H__
#define __APP_MODEL_H__

#include "ngLibCore/container/list/ngIntrusiveList.h"
#include "ngLibApp/resource/ngResource.h"
#include "appMesh.h"

namespace ng
{
	class CDX12CommandList;
}

namespace app
{
	/*!
	* @brief					モデル
	*/
	class CModel : public ng::IResource
	{
	public:
		CModel();
		~CModel();

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
		* @brief					描画
		* @param commandList		DX12コマンドリスト
		*/
		void Render(
			ng::CDX12CommandList& commandList
			) const;

	private:
		/*! メッシュ生成 */
		CMesh* _createMesh(const void* pVertices, ng::u32 verticesSize, const ng::u32* pIndices, ng::u32 indicesSize);
		/*! メッシュ破棄 */
		void _deleteMesh(CMesh* pMesh);

	private:
		using MeshList = ng::CIntrusiveList<CMesh>;	//!< メッシュのリスト

	private:
		MeshList m_meshList;	//!< メッシュのリスト
	};

}	// namespace app

#endif	// __APP_MODEL_H__
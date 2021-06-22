/*!
* @file		appModel.h
* @brief	モデル
* @date		2021-06-13
* @author	s.fukami
*/

#ifndef __APP_MODEL_H__
#define __APP_MODEL_H__

#include "ngLibCore/container//array/ngFixedArray.h"
#include "ngLibApp/resource/ngResource.h"

namespace app
{
	class CMesh;
	class CMaterial;
	struct MaterialFormat;
	struct ShaderParam;
}

namespace app
{
	/*!
	* @brief					モデル
	*/
	class CModel : public ng::IResource
	{
	public:
		using MeshArray = ng::CFixedArray<CMesh*>;	//!< メッシュの配列
		using MaterialArray = ng::CFixedArray<CMaterial*>;	//!< マテリアルの配列

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
		* @brief					メッシュの配列を取得
		*/
		MeshArray& GetMeshArray();
		const MeshArray& GetMeshArray() const;

		/*!
		* @brief					マテリアルの配列を取得
		*/
		MaterialArray& GetMaterialArray();
		const MaterialArray& GetMaterialArray() const;

		/*!
		* @brief					リソースタイプ取得
		*/
		int GetResourceType() const;

	private:
		/*! メッシュ生成 */
		CMesh* _createMesh(
			const void* pVertices, ng::u32 verticesSize, const ng::u32* pIndices, ng::u32 indicesSize, ng::u32 materialIndex
			);
		/*! メッシュ破棄 */
		void _deleteMesh(CMesh*& pMesh);
		/*! マテリアル生成 */
		CMaterial* _createMaterial(const MaterialFormat& format);
		/*! マテリアル破棄 */
		void _deleteMaterial(CMaterial*& pMaterial);
		
		/*! マテリアルフォーマットを取得 */
		void _getMaterialFormat(MaterialFormat* pDst);

	private:
		MeshArray m_meshArr;	//!< メッシュの配列
		MaterialArray m_matArr;	//!< マテリアルの配列
	};

}	// namespace app

#endif	// __APP_MODEL_H__
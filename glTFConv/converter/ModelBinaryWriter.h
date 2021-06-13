/*!
* @file		ModelBinaryWriter.h
* @brief	中間モデル形式 バイナリ出力
* @date		2021-06-11
* @author	s.fukami
*/

#ifndef __GLTFCONV_MODEL_BINARY_WRITER_H__
#define __GLTFCONV_MODEL_BINARY_WRITER_H__

#include "../model/ModelFormat.h"
#include "../model/BinaryFormat.h"

namespace glTFConv
{
	/*!
	* @brief					中間モデル形式 バイナリ出力
	*/
	class CModelBinaryWriter
	{
	public:
		CModelBinaryWriter();
		~CModelBinaryWriter();

		/*!
		* @brief					ファイル出力
		* @param pFilePath			出力先ファイルの絶対パス
		* @param modelFormat		中間モデル形式
		* @return					成否
		*/
		bool Write(const char* pFilePath, const ModelFormat& modelFormat) const;

	private:
		/*! メッシュの情報を書き込む */
		size_t _writeMeshInfo(BinaryFormat::MeshHeader* pMeshHeader, const ModelFormat::Mesh& mesh) const;
		/*! プリミティブの情報を書き込む */
		size_t _writePrimitiveInfo(BinaryFormat::IndexHeader* pIndexHeader, const ModelFormat::Primitive& primitive) const;
	};

}	// namespace glTFConv

#endif	// __GLTFCONV_MODEL_BINARY_WRITER_H__
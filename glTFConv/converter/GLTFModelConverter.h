/*!
* @file		GLTFModelConverter.h
* @brief	glTFモデル変換
* @date		2021-06-07
* @author	s.fukami
*/

#ifndef __GLTFCONV_GLTFMODEL_CONVERTER_H__
#define __GLTFCONV_GLTFMODEL_CONVERTER_H__

namespace glTFConv
{
	/*!
	* @brief					glTFモデルコンバータ
	*/
	class CGLTFModelConverter
	{
	public:
		CGLTFModelConverter();
		~CGLTFModelConverter();

		/*!
		* @brief					モデル変換
		* @param pFilePath			変換元ファイルの絶対パス
		* @return					成否
		*/
		bool Convert(const char* pFilePath);

	private:
	};

}	// namespace glTFConv

#endif	// __GLTFCONV_GLTFMODEL_CONVERTER_H__
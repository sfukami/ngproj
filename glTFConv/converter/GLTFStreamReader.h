/*!
* @file		GLTFStreamReader.h
* @brief	glTFファイル読み込み
* @date		2021-06-07
* @author	s.fukami
*/

#ifndef __GLTFCONV_GLTFSTREAM_READER_H__
#define __GLTFCONV_GLTFSTREAM_READER_H__

namespace Microsoft::glTF
{
	class Document;
	class GLTFResourceReader;
}

namespace glTFConv
{
	/*!
	* @brief					glTFファイル読み込みストリーム
	*/
	class CGLTFStreamReader
	{
	public:
		CGLTFStreamReader();
		~CGLTFStreamReader();
		
		/*!
		* @brief					glTFファイル読み込み
		* @param pFilePath			glTFファイルの絶対パス
		* @return					成否
		*/
		bool Read(const char* pFilePath);

	private:
		/*! Documentの情報を表示 */
		void _printDocumentInfo(
			const Microsoft::glTF::Document& document
			);
		/*! リソースの情報を表示 */
		void _printResourceInfo(
			const Microsoft::glTF::Document& document, const Microsoft::glTF::GLTFResourceReader& resourceReader
			);
	};

}	// namespace glTFConv

#endif	// __GLTFCONV_GLTFSTREAM_READER_H__
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
	struct ModelFormat;
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
		* @param pOutput			出力先の中間モデル形式
		* @return					成否
		*/
		bool Read(const char* pFilePath, ModelFormat* pOutput) const;

	private:
		/*! 中間モデル形式へ変換 */
		void _toModelFormat(
			const Microsoft::glTF::Document& document, const Microsoft::glTF::GLTFResourceReader& resourceReader, ModelFormat* pOutput
			) const;
		/*! Documentの情報を表示 */
		void _printDocumentInfo(
			const Microsoft::glTF::Document& document
			) const;
		/*! リソースの情報を表示 */
		void _printResourceInfo(
			const Microsoft::glTF::Document& document, const Microsoft::glTF::GLTFResourceReader& resourceReader
			) const;
		/*! 中間モデル形式の情報を表示 */
		void _printModelFormat(const ModelFormat* pModelFormat) const;
	};

}	// namespace glTFConv

#endif	// __GLTFCONV_GLTFSTREAM_READER_H__
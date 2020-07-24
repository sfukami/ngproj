/*!
* @file		ngDX12ShaderLoader.h
* @brief	DX12シェーダーローダー
* @date		2020-07-23
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_SHADER_LOADER_H__
#define __NG_GRAPHIC_SHADER_LOADER_H__

namespace ng
{
	class IMemoryAllocator;
	class CDX12Shader;
}

namespace ng
{
	/*!
	* @brief					DX12シェーダーローダー
	*/
	class NG_DECL CDX12ShaderLoader
	{
	public:
		CDX12ShaderLoader();
		~CDX12ShaderLoader();

		/*!
		* @brief					シェーダーファイルをコンパイルして読み込み
		* @param dst				生成したDX12シェーダーの格納先
		* @param pFilename			ファイル名
		* @param pEntryPoint		エントリポイント
		* @param pTarget			ビルドターゲット
		* @param flags				コンパイルフラグ
		* @param isDebugCompile		デバッグコンパイルオプションが有効か
		*							NG_DEBUG 未定義時は無視される
		* @return					NG エラーコード
		*/
		NG_ERRCODE LoadShaderFromFile(
			CDX12Shader& dst,
			const wchar_t* pFileName,
			const char* pEntryPoint,
			const char* pTarget,
			u32 flags,
			bool isDebugCompile
			) const;

		/*!
		* @brief					シェーダーデータをコンパイルして読み込み
		* @param dst				生成したDX12シェーダーの格納先
		* @param pSrcData			データ
		* @param dataSize			データのサイズ
		* @param pEntryPoint		エントリポイント
		* @param pTarget			ビルドターゲット
		* @param flags				コンパイルフラグ
		* @param isDebugCompile		デバッグコンパイルオプションが有効か
		*							NG_DEBUG 未定義時は無視される
		* @return					NG エラーコード
		*/
		NG_ERRCODE LoadShaderFromMemory(
			CDX12Shader& dst,
			const void* pSrcData,
			size_type dataSize,
			const wchar_t* pFileName,
			const char* pEntryPoint,
			const char* pTarget,
			u32 flags,
			bool isDebugCompile
			) const;

		/*!
		* @brief					コンパイル済みのシェーダーファイルを読み込み
		* @param alloc				バッファに用いるメモリアロケータ
		* @param dst				生成したDX12シェーダーの格納先
		* @param pFilename			ファイル名
		* @return					NG エラーコード
		*/
		NG_ERRCODE LoadShaderFromFileCompiled(
			IMemoryAllocator& alloc,
			CDX12Shader& dst,
			const wchar_t* pFileName
			) const;

		/*!
		* @brief					コンパイル済みのシェーダーファイルを読み込み
		* @param dst				生成したDX12シェーダーの格納先
		* @param pSrcData			データ
		* @param dataSize			データのサイズ
		* @return					NG エラーコード
		*/
		NG_ERRCODE LoadShaderFromMemoryCompiled(
			CDX12Shader& dst,
			const void* pSrcData,
			size_type dataSize
			) const;
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_SHADER_LOADER_H__
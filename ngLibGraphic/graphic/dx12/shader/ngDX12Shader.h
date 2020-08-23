/*!
* @file		ngDX12Shader.h
* @brief	DX12シェーダー
* @date		2017-09-25
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_SHADER_H__
#define __NG_GRAPHIC_DX12_SHADER_H__

struct ID3D10Blob;	// ID3DBlob

namespace ng
{
	/*!
	* @brief					DX12シェーダー
	*/
	class NG_DECL CDX12Shader
	{
	public:
		CDX12Shader();
		~CDX12Shader();

		/*!
		* @brief					DX12シェーダー生成
		* @param pCompiled			コンパイル済みのシェーダーデータ
		* @param dataSize			シェーダーデータのサイズ
		* @return					NG エラーコード
		*/
		NG_ERRCODE Create(
			const void* pCompiled,
			size_type dataSize
			);

		/*!
		* @brief					DX12シェーダー生成
		* @param pBlob				DX12ブロブ
		* @return					NG エラーコード
		*/
		NG_ERRCODE Create(
			ID3D10Blob* pBlob
			);

		/*!
		* @brief					破棄
		*/
		void Destroy();
		
		/*!
		* @brief					有効か
		*/
		bool IsValid() const;

		/*!
		* @brief					DX12ブロブ インターフェース取得
		*/
		ID3D10Blob* Interface();
		const ID3D10Blob* Interface() const;

	private:
		ID3D10Blob* m_pIBlob;	//!< DX12ブロブ インターフェース
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_SHADER_H__
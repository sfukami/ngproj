/*!
* @file		ngDX12ConstantBuffer.h
* @brief	DX12コンスタントバッファ
* @date		2019-08-03
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_CONSTANT_BUFFER_H__
#define __NG_GRAPHIC_DX12_CONSTANT_BUFFER_H__

#include "../resource/ngDX12Resource.h"

namespace ng
{
	class CDX12Device;
	class CDX12DescriptorHeap;
}

namespace ng
{
	/*!
	* @brief					DX12コンスタントバッファ
	*/
	class NG_DECL CDX12ConstantBuffer
	{
	public:
		CDX12ConstantBuffer();
		~CDX12ConstantBuffer();

		/*!
		* @brief					DX12コンスタントバッファ生成
		* @param device				DX12デバイス
		* @param pData				データ
		* @param size				データサイズ
		* @return					NG エラーコード
		*/
		NG_ERRCODE Create(
			CDX12Device& device,
			const void* pData,
			u32 size
			);

		/*!
		* @brief					リソースビュー生成
		* @param heap				DX12ディスクリプタヒープ
		* @param heapIdx			ディスクリプタヒープ内のインデックス
		*/
		void CreateResourceView(
			CDX12Device& device,
			CDX12DescriptorHeap& heap,
			u32 heapIdx
			);
		
		/*!
		* @brief					コンスタントバッファへデータコピー
		* @return					NG エラーコード
		*/
		NG_ERRCODE CopyData(
			const void* pData,
			u32 size
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
		* @brief					DX12リソース取得
		*/
		CDX12Resource& GetResource();
		const CDX12Resource& GetResource() const;

		/*!
		* @brief					コンスタントバッファのサイズを取得
		*/
		const u32 GetBufferSize() const;

	private:
		CDX12Resource m_resource;	//!< DX12リソース
		u32 m_bufSize;		//!< コンスタントバッファのサイズ
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_CONSTANT_BUFFER_H__
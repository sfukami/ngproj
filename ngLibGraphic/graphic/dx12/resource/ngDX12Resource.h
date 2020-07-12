/*!
* @file		ngDX12Resource.h
* @brief	DX12リソース
* @date		2019-08-03
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_RESOURCE_H__
#define __NG_GRAPHIC_DX12_RESOURCE_H__

#include <d3d12.h>
#include <DXGIFormat.h>

struct ID3D12Resource;

namespace ng
{
	class CDX12Device;
}

namespace ng
{
	/*!
	* @brief					DX12リソース
	*/
	class NG_DECL CDX12Resource
	{
	public:
		CDX12Resource();
		~CDX12Resource();

		/*!
		* @brief					プリミティブ描画用バッファ DX12リソース生成
		* @param device				DX12デバイス
		* @param pData				データ
		* @param size				データサイズ
		* @return					NG エラーコード
		*/
		NG_ERRCODE CreatePrimitiveBuffer(
			CDX12Device& device,
			const void* pData,
			u32 size
			);

		/*!
		* @brief					テクスチャ用バッファ DX12リソース生成
		* @param device				DX12デバイス
		* @param pTexData			テクスチャデータ
		* @param width				テクスチャの幅
		* @param height				テクスチャの高さ
		* @param format				DXGIフォーマット
		* @return					NG エラーコード
		*/
		NG_ERRCODE CreateTextureBuffer(
			CDX12Device& device,
			const void* pTexData,
			u32 width,
			u32 height,
			DXGI_FORMAT format
			);

		/*!
		* @brief					DX12リソース生成
		* @param device				DX12デバイス
		* @param heapProp			ヒーププロパティ記述子
		* @param resDesc			リソース記述子
		* @param resState			リソースステート
		* @param pClearValue		クリア方法（レンダーターゲット、深度ステンシルのみ）
		* @return					NG エラーコード
		*/
		NG_ERRCODE Create(
			CDX12Device& device,
			const D3D12_HEAP_PROPERTIES& heapProp,
			const D3D12_RESOURCE_DESC& resDesc,
			D3D12_RESOURCE_STATES resState = D3D12_RESOURCE_STATE_GENERIC_READ,
			const D3D12_CLEAR_VALUE* pClearValue = nullptr
			);

		/*!
		* @brief					DX12リソース生成及びデータコピー
		* @param device				DX12デバイス
		* @param pData				データ
		* @param size				データサイズ
		* @return					NG エラーコード
		*/
		NG_ERRCODE CreateAndCopyData(
			CDX12Device& device,
			const D3D12_HEAP_PROPERTIES& heapProp,
			const D3D12_RESOURCE_DESC& resDesc,
			const void* pData,
			u32 size
			);

		/*!
		* @brief					リソースバッファへデータコピー
		* @param pData				データ
		* @param size				データサイズ
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
		* @brief					DX12リソース インターフェース取得
		*/
		ID3D12Resource* Interface();
		const ID3D12Resource* Interface() const;

	private:
		ID3D12Resource* m_pIResource;	//!< DX12リソース インターフェース
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_RESOURCE_H__
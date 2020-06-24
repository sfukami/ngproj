/*!
* @file		ngDX12RenderTarget.h
* @brief	DX12レンダーターゲット
* @date		2017-09-19
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_RENDER_TARGET_TARGET_H__
#define __NG_GRAPHIC_DX12_RENDER_TARGET_TARGET_H__

#include "../../descriptor/ngDX12DescriptorHeap.h"

struct ID3D12Resource;

namespace ng
{
	class CDX12Device;
	class CDX12SwapChain;
	class CDX12CommandList;
	class CDX12ResourceBarrierTransition;
}

namespace ng
{
	/*!
	* @brief					DX12レンダーターゲット
	*/
	class NG_DECL CDX12RenderTarget
	{
	public:
		CDX12RenderTarget();
		~CDX12RenderTarget();

		/*!
		* @brief					DX12レンダーターゲット生成
		* @param device				DX12デバイス
		* @param swapChain			DX12スワップチェイン
		* @param bufferIndex		バックバッファのインデックス
		* @return					NG エラーコード
		*/
		NG_ERRCODE Create(CDX12Device& device, CDX12SwapChain& swapChain, u32 bufferIndex);

		//TODO: テクスチャ用の生成

		/*!
		* @brief					レンダーターゲット設定のためのリソースバリア取得
		*/
		void GetResourceBarrierForSetRenderTarget(CDX12ResourceBarrierTransition* pDest);

		/*!
		* @brief					バックバッファ表示のためのリソースバリア取得
		*/
		void GetResourceBarrierForPresent(CDX12ResourceBarrierTransition* pDest);

		/*!
		* @brief					破棄
		*/
		void Destroy();
		
		/*!
		* @brief					CPUデスクリプタのハンドルを取得
		*/
		D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle();

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
		CDX12DescriptorHeap m_descriptorHeap;	//!< DX12ディスクリプタヒープ
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_RENDER_TARGET_TARGET_H__
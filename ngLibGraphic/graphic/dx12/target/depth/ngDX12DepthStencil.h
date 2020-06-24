/*!
* @file		ngDX12DepthStencil.h
* @brief	DX12深度ステンシル
* @date		2019-08-12
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_DEPTH_STENCIL_H__
#define __NG_GRAPHIC_DX12_DEPTH_STENCIL_H__

#include "../../resource/ngDX12Resource.h"
#include "../../descriptor/ngDX12DescriptorHeap.h"

namespace ng
{
	class CDX12Device;
}

namespace ng
{
	/*!
	* @brief					DX12深度ステンシル
	*/
	class NG_DECL CDX12DepthStencil
	{
	public:
		CDX12DepthStencil();
		~CDX12DepthStencil();

		/*!
		* @brief					DX12深度ステンシル生成
		* @param device				DX12デバイス
		* @param width				幅
		* @param height				高さ
		* @return					NG エラーコード
		*/
		NG_ERRCODE Create(
			CDX12Device& device,
			u32 width,
			u32 height
			);

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
		* @brief					DX12リソース取得
		*/
		CDX12Resource& GetResource();
		const CDX12Resource& GetResource() const;

	private:
		CDX12Resource m_resource;	//!< DX12リソース
		CDX12DescriptorHeap m_descHeap;	//!< DX12ディスクリプタヒープ
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_DEPTH_STENCIL_H__
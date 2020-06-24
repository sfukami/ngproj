/*!
* @file		ngDX12DescriptorHeap.h
* @brief	DX12ディスクリプタヒープ
* @date		2017-09-19
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_DESCRIPTOR_HEAP_H__
#define __NG_GRAPHIC_DX12_DESCRIPTOR_HEAP_H__

#include <d3d12.h>
#include <d3dx12.h>

struct ID3D12DescriptorHeap;

namespace ng
{
	class CDX12Device;
}

namespace ng
{
	/*!
	* @brief					DX12ディスクリプタヒープ
	*/
	class NG_DECL CDX12DescriptorHeap
	{
	public:
		CDX12DescriptorHeap();
		~CDX12DescriptorHeap();

		/*!
		* @brief					DX12ディスクリプタヒープ生成
		* @param device				DX12デバイス
		* @param type				ディスクリプタヒープのタイプ
		*							D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV : コンスタントバッファビュー、シェーダーリソースビュー、アンオーダードアクセスビュー
		*							D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER : サンプラー
		*							D3D12_DESCRIPTOR_HEAP_TYPE_RTV : レンダーターゲットビュー
		*							D3D12_DESCRIPTOR_HEAP_TYPE_DSV : 深度ステンシルビュー
		* @param descriptorNum		ディスクリプターの数
		* @param flags				オプション
		*							D3D12_DESCRIPTOR_HEAP_FLAG_NONE	: デフォルト
		*							D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : シェーダーから参照する場合に指定
		* @return					NG エラーコード
		*/
		NG_ERRCODE Create(
			CDX12Device& device,
			D3D12_DESCRIPTOR_HEAP_TYPE type,
			u32 descriptorNum,
			D3D12_DESCRIPTOR_HEAP_FLAGS flags
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
		* @brief					CPUディスクリプタヒープへのハンドルを取得
		*/
		D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandleForHeapStart() const;

		/*!
		* @brief					CPUディスクリプタヒープへのハンドルを取得
		* @param index				ディスクリプタヒープ内のインデックス
		*/
		CD3DX12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(int index) const;

		/*!
		* @brief					GPUディスクリプタヒープへのハンドルを取得
		*/
		D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandleForHeapStart() const;

		/*!
		* @brief					GPUディスクリプタヒープへのハンドルを取得
		* @param index				ディスクリプタヒープ内のインデックス
		*/
		CD3DX12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(int index) const;

		/*!
		* @brief					DX12ディスクリプタヒープ インターフェース取得
		*/
		ID3D12DescriptorHeap* Interface();
		const ID3D12DescriptorHeap* Interface() const;

	private:
		ID3D12DescriptorHeap* m_pIDescriptorHeap;	//!< DX12ディスクリプタヒープ インタフェース
		u32 m_incrementSize;	//!< ディスクリプタヒープハンドルのインクリメントサイズ
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_DESCRIPTOR_HEAP_H__
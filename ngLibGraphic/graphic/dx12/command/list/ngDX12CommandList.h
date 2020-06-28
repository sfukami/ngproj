/*!
* @file		ngDX12CommandList.h
* @brief	DX12コマンドリスト
* @date		2017-09-24
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_COMMAND_LIST_H__
#define __NG_GRAPHIC_DX12_COMMAND_LIST_H__

#include "../allocator/ngDX12CommandAllocator.h"

struct ID3D12GraphicsCommandList;
struct D3D12_GPU_DESCRIPTOR_HANDLE;

namespace ng
{
	class CDX12Device;
	class CDX12CommandAllocator;
	class CDX12RootSignature;
	class CDX12PipelineState;
	class CDX12ResourceBarrier;
	class CDX12DescriptorHeap;
	class CDX12Viewport;
	class CDX12Scissor;
}

namespace ng
{
	/*!
	* @brief					DX12コマンドリスト
	*/
	class NG_DECL CDX12CommandList
	{
	public:
		typedef ID3D12GraphicsCommandList DX12IfType;	//!< DX12インターフェースの型

	public:
		CDX12CommandList();
		~CDX12CommandList();

		/*!
		* @brief					DX12コマンドリスト生成
		* @param device				DX12デバイス
		* @param allocator			DX12コマンドアロケータ
		* @return					NG エラーコード
		*/
		NG_ERRCODE Create(
			CDX12Device& device,
			CDX12CommandAllocator& allocator
			);

		/*!
		* @brief					コマンドの記録を終了
		*/
		NG_ERRCODE Close();

		/*!
		* @brief					コマンドリストの状態をリセット
		* @param state				DX12パイプラインステート
		*/
		NG_ERRCODE Reset();
		NG_ERRCODE Reset(CDX12PipelineState& state);

		/*!
		* @brief					ルートシグネチャ設定
		*/
		void SetRootSignature(CDX12RootSignature& signature);
		
		/*!
		* @brief					ビューポート設定
		* @param ppViewports		ビューポートの配列
		* @param num				ビューポートの数[0,DX12_VIEWPORT_MAX_PER_PIPELINE]
		*/
		void SetViewports(const CDX12Viewport* ppViewports[], u32 num);
		void SetViewport(const CDX12Viewport& viewport);

		/*!
		* @brief					シザー矩形設定
		* @param ppViewports		シザー矩形の配列
		* @param num				シザー矩形の数[0,DX12_SCISSORRECT_MAX_PER_PIPELINE]
		*/
		void SetScissorRects(const CDX12Scissor* ppScissors[], u32 num);
		void SetScissorRect(const CDX12Scissor& scissor);

		/*!
		* @brief					リソースバリア設定
		* @param ppBarriers			リソースバリアの配列
		* @param num				リソースバリアの数
		*/
		void ResourceBarriers(const CDX12ResourceBarrier* ppBarriers[], u32 num);
		void ResourceBarrier(const CDX12ResourceBarrier& barrier);
		
		/*!
		* @brief					レンダーターゲット設定
		* @param pRTVDescriptorHndlsレンダーターゲットビューのデスクリプターハンドルの配列
		* @param RTVNum				レンダーターゲットビューのデスクリプターハンドルの数
		* @param pDSVDescriptorHndl	深度ステンシルビューのデスクリプターハンドル
		*/
		void SetRenderTargets(
			const D3D12_CPU_DESCRIPTOR_HANDLE pRTVDescriptorHndls[],
			u32 RTVNum,
			const D3D12_CPU_DESCRIPTOR_HANDLE* pDSVDescriptorHndl
			);
		void SetRenderTarget(
			const D3D12_CPU_DESCRIPTOR_HANDLE& RTVDescriptorHndl,
			const D3D12_CPU_DESCRIPTOR_HANDLE* pDSVDescriptorHndl
			);

		/*!
		* @brief					レンダーターゲットのクリア
		* @param RTVDescriptorHndl	レンダーターゲットビューのデスクリプターハンドル
		* @param colorRGBA			クリアカラー
		* @param pRect				クリアする矩形
		* @param rectNum			クリアする矩形の数
		*/
		void ClearRenderTarget(
			const D3D12_CPU_DESCRIPTOR_HANDLE& RTVDescriptorHndl,
			const float colorRGBA[4],
			const D3D12_RECT pRects[] = nullptr,
			u32 rectNum = 0
			);

		/*!
		* @brief					深度ステンシルのクリア
		* @param DSVDescriptorHndl	深度ステンシルビューのデスクリプターハンドル
		* @param flags				クリアフラグ。 D3D12_CLEAR_FLAG_DEPTH, D3D12_CLEAR_FLAG_STENCIL
		* @param depth				クリアに用いる深度値
		* @param stencil			クリアに用いるステンシルの値
		* @param pRect				クリアする矩形
		* @param rectNum			クリアする矩形の数
		*/
		void ClearDepthStencil(
			const D3D12_CPU_DESCRIPTOR_HANDLE& DSVDescriptorHndl,
			D3D12_CLEAR_FLAGS flags = D3D12_CLEAR_FLAG_DEPTH,
			float depth = 1.f,
			u8 stencil = 0,
			const D3D12_RECT pRects[] = nullptr,
			u32 rectNum = 0
			);

		/*!
		* @brief					ディスクリプタヒープ設定
		* @param ppDescriptorHeaps	DX12ディスクリプタヒープの配列
		* @param num				DX12ディスクリプタヒープの数[0,DX12_DESCRIPTOR_HEAP_MAX]
		*/
		void SetDescriptorHeaps(CDX12DescriptorHeap* const ppDescriptorHeaps[], u32 num);
		void SetDescriptorHeap(CDX12DescriptorHeap& descriptorHeap);

		/*!
		* @brief					ディスクリプタテーブルをルートシグネチャへ設定
		* @param index				バインド先のインデックス
		* @param handle				ベースとなるディスクリプタのGPUディスクリプタハンドル
		*/
		void SetGraphicsRootDescriptorTable(
			u32 index,
			const D3D12_GPU_DESCRIPTOR_HANDLE& handle
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
		* @brief					DX12コマンドリスト インターフェース取得
		*/
		DX12IfType* Interface();
		const DX12IfType* Interface() const;

	private:
		DX12IfType* m_pIList;	//!< DX12コマンドリスト インターフェース
		CDX12CommandAllocator* m_pCmdAlloc;	//!< 利用するDX12コマンドアロケータ
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_COMMAND_LIST_H__
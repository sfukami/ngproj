/*!
* @file		ngDX12Util.h
* @brief	DX12 ユーティリティ
* @date		2020-06-24
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_UTIL_H__
#define __NG_GRAPHIC_DX12_UTIL_H__

namespace ng
{
	class CDX12Graphic;
	class CDX12Device;
	class CDX12CommandAllocator;
	class CDX12CommandList;
	class CDX12CommandQueue;
	class CDX12SwapChain;
	class CDX12RenderTarget;
	class CDX12DepthStencil;
	enum class eDX12CommandQueueType : u32;
	enum class eDX12RenderTargetId : u32;
	enum class eDX12DepthStencilId : u32;
}

namespace ng
{
	/*!
	* @brief					DX12グラフィック取得
	*/
	NG_DECL CDX12Graphic* GetDX12Graphic();

	/*!
	* @brief					DX12デバイス取得
	*/
	NG_DECL CDX12Device* GetDX12Device();

	/*!
	* @brief					DX12コマンドアロケータ取得
	*/
	NG_DECL CDX12CommandAllocator* GetDX12CommandAllocator(u32 index);

	/*!
	* @brief					DX12コマンドリスト取得
	*/
	NG_DECL CDX12CommandList* GetDX12CommandList(u32 index);

	/*!
	* @brief					DX12コマンドキュー取得
	*/
	NG_DECL CDX12CommandQueue* GetDX12CommandQueue(eDX12CommandQueueType type);

	/*!
	* @brief					DX12スワップチェイン取得
	*/
	NG_DECL CDX12SwapChain* GetDX12SwapChain();

	/*!
	* @brief					DX12レンダーターゲット取得
	*/
	NG_DECL CDX12RenderTarget* GetDX12RenderTarget(eDX12RenderTargetId id);

	/*!
	* @brief					DX12深度ステンシル取得
	*/
	NG_DECL CDX12DepthStencil* GetDX12DepthStencil(eDX12DepthStencilId id);

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_UTIL_H__
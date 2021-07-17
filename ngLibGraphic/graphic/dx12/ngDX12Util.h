/*!
* @file		ngDX12Util.h
* @brief	DX12 ユーティリティ
* @date		2020-06-24
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_UTIL_H__
#define __NG_GRAPHIC_DX12_UTIL_H__

enum DXGI_FORMAT;

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
	namespace DX12Util
	{
		/*!
		* @brief					DX12グラフィック取得
		*/
		NG_DECL CDX12Graphic* GetGraphic();

		/*!
		* @brief					DX12デバイス取得
		*/
		NG_DECL CDX12Device* GetDevice();

		/*!
		* @brief					DX12コマンドアロケータ取得
		*/
		NG_DECL CDX12CommandAllocator* GetCommandAllocator(u32 index);

		/*!
		* @brief					DX12コマンドリスト取得
		*/
		NG_DECL CDX12CommandList* GetCommandList(u32 index);

		/*!
		* @brief					DX12コマンドキュー取得
		*/
		NG_DECL CDX12CommandQueue* GetCommandQueue(eDX12CommandQueueType type);

		/*!
		* @brief					DX12スワップチェイン取得
		*/
		NG_DECL CDX12SwapChain* GetSwapChain();

		/*!
		* @brief					DX12レンダーターゲット取得
		*/
		NG_DECL CDX12RenderTarget* GetRenderTarget(eDX12RenderTargetId id);

		/*!
		* @brief					DX12深度ステンシル取得
		*/
		NG_DECL CDX12DepthStencil* GetDepthStencil(eDX12DepthStencilId id);

		/*!
		* @brief					現在のバックバッファであるレンダーターゲットを取得
		*/
		NG_DECL CDX12RenderTarget* GetRenderTargetOfCurrentBackBuffer();

		/*!
		* @brief					全DX12コマンドアロケータのリセット
		*/
		NG_DECL void ResetAllCommandAllocator();

		/*!
		* @brief					全DX12コマンドリストの実行
		*/
		NG_DECL void ExecuteAllCommandList(eDX12CommandQueueType type);

		/*!
		* @brief					レンダーターゲットをコマンドリストへ設定
		*/
		NG_DECL void SetRenderTarget(CDX12CommandList* pCmdList, CDX12RenderTarget* pRT, CDX12DepthStencil* pDS = nullptr);

		/*!
		* @brief					レンダーターゲットをPresent可能な状態とするようにコマンドリストへ設定
		*/
		NG_DECL void SetRenderTargetToPresent(CDX12CommandList* pCmdList, CDX12RenderTarget* pRT);

		/*!
		* @brief					レンダーターゲットのバッファをクリア
		*/
		NG_DECL void ClearRenderTarget(CDX12CommandList* pCmdList, CDX12RenderTarget* pRT, const float rgba[4], CDX12DepthStencil* pDS = nullptr);

		/*!
		* @brief					DXGI_FORMAT の1ピクセルのビット数を取得
		*/
		NG_DECL size_type DXGIFormatToBitsPerPixel(DXGI_FORMAT format);

	}	// namespace DX12Util
}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_UTIL_H__
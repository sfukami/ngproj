/*!
* @file		ngDX12SwapChain.h
* @brief	DX12スワップチェイン
* @date		2017-09-18
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_SWAP_CHAIN_H__
#define __NG_GRAPHIC_DX12_SWAP_CHAIN_H__

#include <windows.h>
#include <DXGIFormat.h>
#include "../target/render/ngDX12RenderTarget.h"

struct IDXGISwapChain3;

namespace ng
{
	class CDX12Device;
	class CDX12CommandQueue;
}

namespace ng
{
	/*!
	* @brief					DX12スワップチェイン
	*/
	class NG_DECL CDX12SwapChain
	{
	public:
		/*! バックバッファレンダーターゲット */
		enum class eBackBufferRenderTarget : u32
		{
			TARGET_0,
			TARGET_1,
			TARGET_2,

			NUM
		};

	public:
		CDX12SwapChain();
		~CDX12SwapChain();

		/*!
		* @brief					DX12スワップチェイン生成
		* @param device				DX12デバイス
		* @param cmdQueue			DX12コマンドキュー
		* @param hWnd				ウィンドウハンドル
		* @param bufferCount		バッファの数
		* @param bufferWidth		バッファの幅
		* @param bufferHeight		バッファの高さ
		* @param format				DXGIフォーマット
		*							https://msdn.microsoft.com/en-us/library/windows/desktop/bb173059(v=vs.85).aspx
		* @param isFullscreen		フルスクリーンか
		*							Warpデバイスの場合は無効
		* @return					NG エラーコード
		*/
		NG_ERRCODE Create(
			CDX12Device& device,
			CDX12CommandQueue& cmdQueue,
			HWND hWnd,
			u32 bufferCount,
			u32 bufferWidth,
			u32 bufferHeight,
			DXGI_FORMAT format,
			bool isFullscreen
			);

		/*!
		* @brief					レンダリング結果の表示
		* @param syncInterval		垂直同期との同期方法
		* 							0 : 即座に表示され、同期されません。
		* 							1、2、3、4 : n 番目の垂直同期の後に表示を同期します。
		* @param flags				オプション
		* @return					NG エラーコード
		*/
		NG_ERRCODE Present(u32 syncInterval, u32 flags = 0);

		/*!
		* @brief					破棄
		*/
		void Destroy();

		/*!
		* @brief					現在のバックバッファのインデックスを取得
		*/
		u32 GetCurrentBackBufferIndex() const;

		/*!
		* @brief					現在のバックバッファのレンダーターゲットを取得
		*/
		CDX12RenderTarget& GetCurrentRenderTarget();
		const CDX12RenderTarget& GetCurrentRenderTarget() const;

		/*!
		* @brief					有効か
		*/
		bool IsValid() const;

		/*!
		* @brief					DX12スワップチェイン インターフェース取得
		*/
		IDXGISwapChain3* Interface();
		const IDXGISwapChain3* Interface() const;

		/*!
		* @brief					バックバッファの数を取得
		*/
		u32 GetBackBufferCount() const;

		/*!
		* @brief					バックバッファの幅を取得
		*/
		u32 GetBackBufferWidth() const;

		/*!
		* @brief					バックバッファの高さを取得
		*/
		u32 GetBackBufferHeight() const;

		/*!
		* @brief					バックバッファのフォーマットを取得
		*/
		DXGI_FORMAT GetBackBufferFormat() const;
		
	private:
		IDXGISwapChain3*	m_pISwapChain;	//!< DX12スワップチェイン インターフェース
		CDX12RenderTarget	m_rtvs[static_cast<u32>(eBackBufferRenderTarget::NUM)];	//!< レンダーターゲットビュー

		u32 m_bufferCount;	//!< バックバッファの数
		u32 m_bufferWidth;	//!< バックバッファの幅
		u32 m_bufferHeight;	//!< バックバッファの高さ
		DXGI_FORMAT m_bufferFormat;	//!< バックバッファのフォーマット
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_SWAP_CHAIN_H__
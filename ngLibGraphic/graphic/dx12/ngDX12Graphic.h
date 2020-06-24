/*!
* @file		ngDX12Graphic.h
* @brief	DX12グラフィックス
* @date		2017-08-23
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_GRAPHIC_H__
#define __NG_GRAPHIC_DX12_GRAPHIC_H__

#include "../ngGraphic.h"
#include "device/ngDX12Device.h"
#include "command/allocator/ngDX12CommandAllocatorManager.h"
#include "command/list/ngDX12CommandListManager.h"

namespace ng
{
	/*!
	* @brief					DirectX12グラフィック
	*/
	class NG_DECL CDX12Graphic : public IGraphic
	{
	public:
		//! 生成パラメータ
		struct CreateParam
		{
			CreateParam();

			HWND hWnd;		//!< ウィンドウハンドル
			u32 clientWidth;	//!< クライアント領域幅
			u32 clientHeight;	//!< クライアント領域高さ
			bool isFullscreen;	//!< フルスクリーンか
			CDX12Device::CreateParam deviceParam;	//!< DX12デバイス生成パラメータ
		};

	public:
		CDX12Graphic();
		~CDX12Graphic();

		/*!
		* @brief					DirectX12グラフィック生成
		* @param param				生成パラメータ
		* @return					NG エラーコード
		*/
		NG_ERRCODE Create(const CreateParam& param);

		/*!
		* @brief					描画
		*/
		void Render();

		/*!
		* @brief					破棄
		*/
		void Destroy();

		/*!
		* @brief					DX12デバイス取得
		*/
		CDX12Device& GetDevice();
		const CDX12Device& GetDevice() const;

		/*!
		* @brief					DX12コマンドアロケータマネージャ取得
		*/
		CDX12CommandAllocatorManager& GetCommandAllocatorMngr();
		const CDX12CommandAllocatorManager& GetCommandAllocatorMngr() const;
		
		/*!
		* @brief					DX12コマンドリストマネージャ取得
		*/
		CDX12CommandListManager& GetCommandListMngr();
		const CDX12CommandListManager& GetCommandListMngr() const;

	private:
		/*!
		* @brief					DX12コマンドアロケータ生成
		* @param device				DX12デバイス
		* @param type				コマンドリストのタイプ
		* @param index				DX12コマンドアロケータのインデックス [0, NG_DX12_COMMAND_ALLOCATOR_MAX-1]
		*/
		NG_ERRCODE _createCommandAllocator(CDX12Device& device, D3D12_COMMAND_LIST_TYPE type, u32 index);

		/*!
		* @brief					DX12コマンドリスト生成
		* @param device				DX12デバイス
		* @param cmdAllocIdx		DX12コマンドアロケータのインデックス [0, NG_DX12_COMMAND_ALLOCATOR_MAX-1]
		* @param cmdListIdx			DX12コマンドリストのインデックス [0, NG_DX12_COMMAND_LIST_MAX-1]
		*/
		NG_ERRCODE _createCommandList(CDX12Device& device, u32 cmdAllocIdx, u32 cmdListIdx);

	private:
		CDX12Device			m_device;	//!< DX12デバイス
		CDX12CommandListManager			m_cmdListMngr;	//!< DX12コマンドリストマネージャ
		CDX12CommandAllocatorManager	m_cmdAllocMngr;	//!< DX12コマンドアロケータマネージャ
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_GRAPHIC_H__
/*!
* @file		ngDX12CommandQueueManager.h
* @brief	DX12コマンドキューマネージャ
* @date		2018-02-18
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_COMMAND_QUEUE_MANAGER_H__
#define __NG_GRAPHIC_DX12_COMMAND_QUEUE_MANAGER_H__

#include "ngLibCore/container/array/ngFixedArray.h"
#include "ngDX12CommandQueueType.h"

namespace ng
{
	class CDX12Device;
	class CDX12CommandQueue;
}

namespace ng
{
	/*!
	* @brief					DX12コマンドキューマネージャ
	*/
	class NG_DECL CDX12CommandQueueManager
	{
	public:
		CDX12CommandQueueManager();
		~CDX12CommandQueueManager();

		/*!
		* @brief					初期化
		* @param device				DX12デバイス
		* @return					NG エラーコード
		*/
		NG_ERRCODE Initialize(CDX12Device& device);

		/*!
		* @brief					終了処理
		*/
		void Finalize();

		/*!
		* @brief					コマンドキュー取得
		* @param type				DX12コマンドキュータイプ
		*/
		CDX12CommandQueue* GetCommandQueue(eDX12CommandQueueType type);
		const CDX12CommandQueue* GetCommandQueue(eDX12CommandQueueType type) const;

	private:
		/*!
		* @brief					コマンドキュー生成
		* @param device				DX12デバイス
		* @param type				DX12コマンドキュータイプ
		* @return					NG エラーコード
		*/
		NG_ERRCODE _createCommandQueue(CDX12Device& device, eDX12CommandQueueType type);

		/*!
		* @brief					コマンドキュー削除
		* @param type				DX12コマンドキュータイプ
		*/
		void _deleteCommandQueue(eDX12CommandQueueType type);

	private:
		CFixedArray<CDX12CommandQueue*, static_cast<u32>(eDX12CommandQueueType::NUM)> m_queueArr;	//!< コマンドキュー配列
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_COMMAND_QUEUE_MANAGER_H__
/*!
* @file		ngDX12CommandQueue.h
* @brief	DX12コマンドキュー
* @date		2017-09-18
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_COMMAND_QUEUE_H__
#define __NG_GRAPHIC_DX12_COMMAND_QUEUE_H__

#include <Windows.h>
#include <d3d12.h>
#include "../../fence/ngDX12Fence.h"

struct ID3D12CommandQueue;

namespace ng
{
	class CDX12Device;
	class CDX12CommandList;
	class CDX12Fence;
}

namespace ng
{
	/*!
	* @brief					DX12コマンドキュー
	*/
	class NG_DECL CDX12CommandQueue
	{
	public:
		CDX12CommandQueue();
		~CDX12CommandQueue();

		/*!
		* @brief					DX12コマンドキュー生成
		* @param device				DX12デバイス
		* @param type				DX12コマンドリストのタイプ
		* @param priority			優先度
		* @return					NG エラーコード
		*/
		NG_ERRCODE Create(
			CDX12Device& device,
			D3D12_COMMAND_LIST_TYPE type,
			u32 priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL
			);

		/*!
		* @brief					コマンドリスト実行
		* @param ppCommandLists		DX12コマンドリストの配列
		* @param num				配列の要素数
		*/
		void ExecuteCommandLists(CDX12CommandList* ppCommandLists[], u32 num);
		void ExecuteCommandList(CDX12CommandList& commandList);

		/*!
		* @brief					フェンス待機
		*/
		void WaitForFence();

		/*!
		* @brief					破棄
		*/
		void Destroy();

		/*!
		* @brief					有効か
		*/
		bool IsValid() const;

		/*!
		* @brief					DX12コマンドキュー インターフェース取得
		*/
		ID3D12CommandQueue* Interface();
		const ID3D12CommandQueue* Interface() const;

	private:
		/*!
		* @brief					GPUに対しシグナル状態となるフェンス値を設定する
		* @param fence				DX12フェンス
		* @param value				フェンス値
		*/
		NG_ERRCODE _signal(CDX12Fence& fence, u64 value);

	private:
		ID3D12CommandQueue* m_pIQueue;	//!< DX12コマンドキュー インターフェース

		CDX12Fence m_fence;		//!< DX12フェンス
		u64 m_nextFenceValue;	//!< 次のフェンス値
		HANDLE m_fenceEvHndl;	//!< フェンス待機用イベントオブジェクトへのハンドル
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_COMMAND_QUEUE_H__
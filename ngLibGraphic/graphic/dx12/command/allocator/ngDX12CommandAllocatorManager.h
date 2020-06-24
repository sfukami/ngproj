/*!
* @file		ngDX12CommandAllocatorManager.h
* @brief	DX12コマンドアロケータマネージャ
* @date		2018-04-26
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_COMMAND_ALLOCATOR_MANAGER_H__
#define __NG_GRAPHIC_DX12_COMMAND_ALLOCATOR_MANAGER_H__

#include <d3d12.h>
#include "../../common/ngDX12Const.h"
#include "ngLibCore/container/array/ngFixedArray.h"

namespace ng
{
	class CDX12Device;
	class CDX12CommandAllocator;
}

namespace ng
{
	/*!
	* @brief					DX12コマンドアロケータマネージャ
	*/
	class NG_DECL CDX12CommandAllocatorManager
	{
	public:
		CDX12CommandAllocatorManager();
		~CDX12CommandAllocatorManager();

		/*!
		* @brief					DX12コマンドアロケータ生成
		* @param device				DX12デバイス
		* @param type				DX12コマンドリストのタイプ
		* @param index				インデックス [0, NG_DX12_COMMAND_ALLOCATOR_MAX-1]
		* @return					NG エラーコード
		*/
		NG_ERRCODE CreateCommandAllocator(
			CDX12Device& device,
			D3D12_COMMAND_LIST_TYPE type,
			u32 index
			);

		/*!
		* @brief					DX12コマンドアロケータ削除
		* @param index				インデックス [0, NG_DX12_COMMAND_ALLOCATOR_MAX-1]
		*/
		void DeleteCommandAllocator(u32 index);

		/*!
		* @brief					終了処理
		*/
		void Finalize();

		/*!
		* @brief					DX12コマンドアロケータ取得
		* @param index				インデックス [0, NG_DX12_COMMAND_ALLOCATOR_MAX-1]
		*/
		CDX12CommandAllocator* GetCommandAllocator(u32 index);
		const CDX12CommandAllocator* GetCommandAllocator(u32 index) const;

	private:
		CFixedArray<CDX12CommandAllocator*, NG_DX12_COMMAND_ALLOCATOR_MAX> m_cmdAllocs;	//!< DX12コマンドアロケータ配列
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_COMMAND_ALLOCATOR_MANAGER_H__
/*!
* @file		ngDX12CommandListManager.h
* @brief	DX12コマンドリストマネージャ
* @date		2018-04-26
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_COMMAND_LIST_MANAGER_H__
#define __NG_GRAPHIC_DX12_COMMAND_LIST_MANAGER_H__

#include "../../common/ngDX12Const.h"
#include "ngLibCore/container/array/ngFixedArray.h"

namespace ng
{
	class CDX12Device;
	class CDX12CommandList;
	class CDX12CommandAllocator;
}

namespace ng
{
	/*!
	* @brief					DX12コマンドリストマネージャ
	*/
	class NG_DECL CDX12CommandListManager
	{
	public:
		CDX12CommandListManager();
		~CDX12CommandListManager();

		/*!
		* @brief					DX12コマンドリスト生成
		* @param device				DX12デバイス
		* @param allocator			DX12コマンドアロケータ
		* @param index				インデックス [0, NG_DX12_COMMAND_LIST_MAX-1]
		* @return					NG エラーコード
		*/
		NG_ERRCODE CreateCommandList(
			CDX12Device& device,
			CDX12CommandAllocator& allocator,
			u32 index
			);

		/*!
		* @brief					DX12コマンドリスト削除
		* @param index				インデックス [0, NG_DX12_COMMAND_LIST_MAX-1]
		*/
		void DeleteCommandList(u32 index);

		/*!
		* @brief					終了処理
		*/
		void Finalize();

		/*!
		* @brief					DX12コマンドリスト取得
		* @param index				インデックス [0, NG_DX12_COMMAND_LIST_MAX-1]
		*/
		CDX12CommandList* GetCommandList(u32 index);
		const CDX12CommandList* GetCommandList(u32 index) const;

	private:
		CFixedArray<CDX12CommandList*, NG_DX12_COMMAND_LIST_MAX> m_cmdLists;	//!< コマンドリスト配列
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_COMMAND_LIST_MANAGER_H__
/*!
* @file		ngDX12CommandListManager.cpp
* @brief	DX12コマンドリストマネージャ
* @date		2018-04-26
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "../../common/ngDX12Common.h"
#include "ngDX12CommandListManager.h"
#include "ngDX12CommandList.h"

namespace ng
{
	CDX12CommandListManager::CDX12CommandListManager()
	{
	}

	CDX12CommandListManager::~CDX12CommandListManager()
	{
		Finalize();
	}

	NG_ERRCODE CDX12CommandListManager::CreateCommandList(
		CDX12Device& device,
		CDX12CommandAllocator& allocator,
		u32 index
		)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// DX12コマンドリスト生成
		CDX12CommandList* pList = NG_NEW(NG_SYSALLOC_GRAPHIC) CDX12CommandList();
		if(NG_FAILED(ret = pList->Create(device, allocator))) {
			return ret;
		}

		m_cmdLists[index] = pList;

		return ret;
	}

	void CDX12CommandListManager::DeleteCommandList(u32 index)
	{
		NG_ASSERT(index < NG_DX12_COMMAND_LIST_MAX);

		if(index >= NG_DX12_COMMAND_LIST_MAX) return;

		CDX12CommandList* pList = GetCommandList(index);
		if(pList) {
			pList->Destroy();
			NG_DELETE(NG_SYSALLOC_GRAPHIC, pList);
			m_cmdLists[index] = nullptr;
		}
	}

	void CDX12CommandListManager::Finalize()
	{
		for(u32 i = 0; i < NG_DX12_COMMAND_LIST_MAX; i++)
		{
			DeleteCommandList(i);
		}
	}

	CDX12CommandList* CDX12CommandListManager::GetCommandList(u32 index)
	{
		NG_ASSERT(index < NG_DX12_COMMAND_LIST_MAX);

		return m_cmdLists[index];
	}
	const CDX12CommandList* CDX12CommandListManager::GetCommandList(u32 index) const
	{
		return const_cast<CDX12CommandListManager*>(this)->GetCommandList(index);
	}

}	// namespace ng
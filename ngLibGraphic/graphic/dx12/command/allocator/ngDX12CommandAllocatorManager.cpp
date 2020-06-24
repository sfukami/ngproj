/*!
* @file		ngDX12CommandAllocatorManager.cpp
* @brief	DX12コマンドアロケータマネージャ
* @date		2018-04-26
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "../../common/ngDX12Common.h"
#include "ngDX12CommandAllocatorManager.h"
#include "ngDX12CommandAllocator.h"

namespace ng
{
	CDX12CommandAllocatorManager::CDX12CommandAllocatorManager()
	{
	}

	CDX12CommandAllocatorManager::~CDX12CommandAllocatorManager()
	{
		Finalize();
	}

	NG_ERRCODE CDX12CommandAllocatorManager::CreateCommandAllocator(
		CDX12Device& device,
		D3D12_COMMAND_LIST_TYPE type,
		u32 index
		)
	{
		NG_ASSERT(index < NG_DX12_COMMAND_ALLOCATOR_MAX);

		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// DX12コマンドアロケータ生成
		CDX12CommandAllocator* pAlloc = NG_NEW(NG_SYSALLOC_GRAPHIC) CDX12CommandAllocator();
		if(NG_FAILED(ret = pAlloc->Create(device, type))) {
			return ret;
		}

		m_cmdAllocs[index] = pAlloc;

		return ret;
	}

	void CDX12CommandAllocatorManager::DeleteCommandAllocator(u32 index)
	{
		NG_ASSERT(index < NG_DX12_COMMAND_ALLOCATOR_MAX);

		if(index >= NG_DX12_COMMAND_ALLOCATOR_MAX) return;

		CDX12CommandAllocator* pAlloc = GetCommandAllocator(index);
		if(pAlloc) {
			pAlloc->Destroy();
			NG_DELETE(NG_SYSALLOC_GRAPHIC, pAlloc);
			m_cmdAllocs[index] = nullptr;
		}
	}
	
	void CDX12CommandAllocatorManager::Finalize()
	{
		for(u32 i = 0; i < NG_DX12_COMMAND_ALLOCATOR_MAX; i++)
		{
			DeleteCommandAllocator(i);
		}
	}

	CDX12CommandAllocator* CDX12CommandAllocatorManager::GetCommandAllocator(u32 index)
	{
		NG_ASSERT(index < NG_DX12_COMMAND_ALLOCATOR_MAX);

		if(index < 0) {
			return nullptr;
		}

		return m_cmdAllocs[index];
	}
	const CDX12CommandAllocator* CDX12CommandAllocatorManager::GetCommandAllocator(u32 index) const
	{
		return const_cast<CDX12CommandAllocatorManager*>(this)->GetCommandAllocator(index);
	}

}	// namespace ng
/*!
* @file		ngMemoryManager.cpp
* @brief	メモリ管理
* @date		2019-03-10
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "ngMemoryManager.h"

namespace ng
{
	CMemoryManager::CMemoryManager()
		: m_pMemPool(nullptr)
	{
	}

	CMemoryManager::~CMemoryManager()
	{
	}

	NG_ERRCODE CMemoryManager::Initialize(
		CMemoryPool& memPool,
		u32 allocNumMax
		)
	{
		NG_ERRCODE ret = eNG_S_OK;

		if(!memPool.IsPool()) {
			NG_ERRMSG("CMemoryManager", "メモリプールが利用できませんでした");
			return eNG_E_INVALIDMEMORY;
		}

		// メモリアロケータ初期化
		if(NG_FAILED(ret = m_memAlloc.Initialize("memory_manager", memPool, memPool.GetSize()))) {
			NG_ERRLOG(ret, "メモリアロケータの初期化に失敗");
			return ret;
		}

		// 追加のメモリアロケータ格納先配列初期化
		if(NG_FAILED(ret = m_allocArr.Initialize(allocNumMax, m_memAlloc))) {
			NG_ERRLOG(ret, "追加のメモリアロケータ格納先配列の初期化に失敗");
			return ret;
		}

		m_pMemPool = &memPool;

		return ret;
	}

	void CMemoryManager::Finalize()
	{
		if(!IsInit()) return;

		m_allocArr.Finalize();
		m_memAlloc.Finalize();

		m_pMemPool = nullptr;
	}

	void CMemoryManager::DeleteAllocator(u32 index)
	{
		IMemoryAllocator* pAlloc = GetAllocator(index);
		if(pAlloc != nullptr) {
			// デストラクタのため先にアロケータを破棄
			pAlloc->Finalize();
			NG_DELETE(m_memAlloc, pAlloc);

			m_allocArr[index] = nullptr;
		}
	}

	void CMemoryManager::ClearAllocator()
	{
		for(u32 i = 0; i < m_allocArr.Size(); i++)
		{
			DeleteAllocator(i);
		}
	}

	IMemoryAllocator* CMemoryManager::GetAllocator(u32 index)
	{
		return m_allocArr[index];
	}

	bool CMemoryManager::IsInit() const
	{
		return (m_pMemPool != nullptr);
	}

	void CMemoryManager::_registerAllocator(u32 index, IMemoryAllocator* pAlloc)
	{
		if(pAlloc == nullptr) {
			return;
		}

		m_allocArr[index] = pAlloc;
	}

}	// namespace ng
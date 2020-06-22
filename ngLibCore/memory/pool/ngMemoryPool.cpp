/*!
* @file		ngMemoryPool.cpp
* @brief	メモリプール
* @date		2015-12-19
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "ngMemoryPool.h"

namespace ng
{
	CMemoryPool::CMemoryPool()
		: m_pMemory(nullptr)
		, m_size(0)
		, m_pAlloc(nullptr)
	{
	}

	CMemoryPool::~CMemoryPool()
	{
	}

	NG_ERRCODE CMemoryPool::Pool(
		void* pMemory,
		size_type size
		)
	{
		if(IsPool()) {
			return eNG_E_INITFAILED;
		}

		if(pMemory == nullptr) {
			return eNG_E_INVALIDMEMORY;
		}

		m_pMemory = pMemory;
		m_size = size;

		return eNG_S_OK;
	}

	NG_ERRCODE CMemoryPool::Pool(
		IMemoryAllocator& alloc,
		size_type size
		)
	{
		NG_ERRCODE ret = eNG_S_OK;

		if(NG_FAILED(ret = Pool(NG_NEW_BYTE(alloc, size), size))) {
			return ret;
		}

		m_pAlloc = &alloc;

		return ret;
	}

	void CMemoryPool::Unpool()
	{
		if(m_pMemory == nullptr) {
			return;
		}

		if(m_pAlloc != nullptr) {
			NG_DELETE(*m_pAlloc, m_pMemory);
		}

		m_pMemory = nullptr;
		m_size = 0;
		m_pAlloc = nullptr;
	}

	void* CMemoryPool::GetMemory()
	{
		return m_pMemory;
	}
	const void* CMemoryPool::GetMemory() const
	{
		return m_pMemory;
	}

	size_type CMemoryPool::GetSize() const
	{
		return m_size;
	}

	bool CMemoryPool::IsPool() const
	{
		if(m_pMemory == nullptr) {
			return false;
		}

		return true;
	}

}	// namespace ng
/*!
* @file		ngStackAllocator.cpp
* @brief	スタックアロケータ
* @date		2017-02-26
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "ngStackAllocator.h"

namespace ng
{
	CStackAllocator::CStackAllocator()
		: m_pBeg(nullptr)
		, m_pEnd(nullptr)
		, m_pPos(nullptr)
		, m_pAlloc(nullptr)
		, m_name("")
	#if defined(NG_CONFIG_MEMORY_PRINT_LOG)
		, m_isPrintLogEnable(false)
	#endif
	{
	}

	CStackAllocator::~CStackAllocator()
	{
		Finalize();
	}

	NG_ERRCODE CStackAllocator::Initialize(
		const char* name
		, IMemoryAllocator& alloc
		, size_type size
		)
	{
		NG_ERRCODE ret = _initialize(name, NG_NEW_BYTE(alloc, size), size);
		if(NG_SUCCEEDED(ret)) {
			m_pAlloc = &alloc;
		}
		return ret;
	}

	NG_ERRCODE CStackAllocator::Initialize(
		const char* name
		, CMemoryPool& pool
		, size_type size
		)
	{
		return _initialize(name, pool.GetMemory(), size);
	}

	void CStackAllocator::Finalize()
	{
		if(!IsInit()) return;

		void* pMemory = GetMemory();

		NG_CLRSTR(m_name);
		m_pBeg = m_pEnd = m_pPos = nullptr;
		m_memPool.Unpool();

		if(m_pAlloc) {
			NG_DELETE_BYTE(*m_pAlloc, pMemory);
			m_pAlloc = nullptr;
		}
	}

	void* CStackAllocator::Allocate(
		size_type size
		, u32 alignment
	#if defined(NG_CONFIG_MEMORY_DBGINFO)
		, const char* src
	#endif
		)
	{
		if(!IsInit()) return nullptr;

		char* pNext = PointerOffset<char*>(m_pPos, size);
		if(pNext >= m_pEnd) {
			return nullptr;
		}

		char* pPrev = m_pPos;
		m_pPos = pNext;

		return pPrev;
	}

	void CStackAllocator::Free(
		void* p
		)
	{
		if(!IsInit()) return;

		NG_ASSERT(p >= m_pBeg);
		NG_ASSERT(p < m_pEnd);

		m_pPos = static_cast<char*>(p);
	}

	void CStackAllocator::Clear()
	{
		m_pPos = m_pBeg;
	}

	bool CStackAllocator::IsInit() const
	{
		return (GetMemory() != nullptr);
	}
	
	void* CStackAllocator::GetMemory()
	{
		return m_pBeg;
	}
	const void* CStackAllocator::GetMemory() const
	{
		return m_pBeg;
	}

	size_type CStackAllocator::GetMemSize() const
	{
		return PointerDiff(m_pEnd, m_pBeg);
	}

	size_type CStackAllocator::GetAllocatableMaximum() const
	{
		return PointerDiff(m_pEnd, m_pPos);
	}

	const char* CStackAllocator::GetName() const
	{
		return m_name;
	}

#if defined(NG_CONFIG_MEMORY_PRINT_LOG)
	void CStackAllocator::SetPrintLogEnable(bool enable)
	{
		m_isPrintLogEnable = enable;
	}
	bool CStackAllocator::GetPrintLogEnable() const
	{
		return m_isPrintLogEnable;
	}
#endif

	NG_ERRCODE CStackAllocator::_initialize(const char* name, void* pMemory, size_type size)
	{
		NG_ASSERT(!IsInit(), "不正な再初期化");
		NG_ASSERT_NOT_NULL(name);
		NG_ASSERT_NOT_NULL(pMemory);

		NG_ERRCODE ret = m_memPool.Pool(pMemory, size);
		if(NG_FAILED(ret)) {
			return ret;
		}

		m_pBeg = m_pPos = static_cast<char*>(m_memPool.GetMemory());
		m_pEnd = PointerOffset<char*>(m_pBeg, size);

		NG_STRCPY(m_name, name);

		return ret;
	}

}	// namespace ng
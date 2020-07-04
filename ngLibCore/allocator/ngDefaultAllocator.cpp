/*!
* @file		ngDefaultAllocator.cpp
* @brief	メモリアロケータ デフォルトアロケータ
* @date		2017-08-28
* @author	s.fukami
*/

#include <stdlib.h>
#include <stdint.h>
#include "ngLibCore/common/ngCommon.h"
#include "ngDefaultAllocator.h"

namespace ng
{
	CDefaultAllocator::CDefaultAllocator()
		: m_isInit(false)
		, m_name("")
	{
	}
	CDefaultAllocator::~CDefaultAllocator()
	{
	}

	NG_ERRCODE CDefaultAllocator::Initialize(const char* name)
	{
		m_isInit = true;
		NG_STRCPY(m_name, name);

		return eNG_S_OK;
	}

	NG_ERRCODE CDefaultAllocator::Initialize(
		const char* name
		, IMemoryAllocator& alloc
		, size_type size
		)
	{
		return Initialize(name);
	}

	NG_ERRCODE CDefaultAllocator::Initialize(
		const char* name
		, CMemoryPool& pool
		, size_type size
		)
	{
		return Initialize(name);
	}

	void CDefaultAllocator::Finalize()
	{
		m_isInit = false;
		NG_CLRSTR(m_name);
	}

	void* CDefaultAllocator::Allocate(
		size_type size
		, u32 alignment
	#if defined(NG_CONFIG_MEMORY_DBGINFO)
		, const char* src
	#endif
		)
	{
		return NG_MALLOC(size);
	}

	void CDefaultAllocator::Free(
		void* p
		)
	{
		NG_FREE(p);
	}

	bool CDefaultAllocator::IsInit() const
	{
		return m_isInit;
	}

	void* CDefaultAllocator::GetMemory()
	{
		return nullptr;
	}
	const void* CDefaultAllocator::GetMemory() const
	{
		return nullptr;
	}

	size_type CDefaultAllocator::GetMemSize() const
	{
		return SIZE_MAX;
	}

	const char* CDefaultAllocator::GetName() const
	{
		return m_name;
	}

}	// namespace ng

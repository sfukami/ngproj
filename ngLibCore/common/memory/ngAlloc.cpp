/*!
* @file		ngAlloc.cpp
* @brief	メモリ管理
* @date		2017-08-28
* @author	s.fukami
*/

#include "ngAlloc.h"
#include "ngLibCore/common/debug/ngDbgMacro.h"
//#include "ngLibCore/allocator/ngIMemoryAllocator.h"

#if 0
void* operator new(
	ng::size_type size
	, ng::IMemoryAllocator& alloc
	, ng::u32 alignment
#if defined(NG_CONF_MEMORY_DBGINFO)
	, const char* src
#endif
	)
{
	void* p = alloc.Allocate(
		size
		, alignment
	#if defined(NG_CONF_MEMORY_DBGINFO)
		, src
	#endif
		);

#if defined(NG_CONF_MEMORY_DBGINFO)
#if defined(NG_CONF_MEMORY_PRINT_LOG)
	NG_DPRINTF("[new]   - <%s> 0x%p, size:%u\n", alloc.GetName(), p, size);
	NG_DPRINTF("          %s\n", src);
#endif	// NG_CONF_MEMORY_PRINT_LOG
	NG_ASSERT(p, "operator new failed. size:%u, called from:\n\t%s", size, src);
#else
#endif	// NG_CONF_MEMORY_DBGINFO

	return p;
}

void* operator new[](
	ng::size_type size
	, ng::IMemoryAllocator& alloc
	, ng::u32 alignment
#if defined(NG_CONF_MEMORY_DBGINFO)
	, const char* src
#endif
	)
{
	void* p = alloc.Allocate(
		size
		, alignment
	#if defined(NG_CONF_MEMORY_DBGINFO)
		, src
	#endif
		);
#if defined(NG_CONF_MEMORY_DBGINFO)
#if defined(NG_CONF_MEMORY_PRINT_LOG)
	NG_DPRINTF("[new[]] - <%s> 0x%p, size:%u\n", alloc.GetName(), p, size);
	NG_DPRINTF("          %s\n", src);
#endif	// NG_CONF_MEMORY_PRINT_LOG
	NG_ASSERT(p, "operator new[] failed. size:%u, called from:\n\t%s", size, src);
#else
#endif	// NG_CONF_MEMORY_DBGINFO
	return p;
}

void operator delete(
	void* p
	, ng::IMemoryAllocator& alloc
	, ng::u32 alignment
#if defined(NG_CONF_MEMORY_DBGINFO)
	, const char* src
#endif
	)
{
	NG_ASSERT(false, "使用禁止関数の呼び出し");
}

void operator delete[](
	void* p
	, ng::IMemoryAllocator& alloc
	, ng::u32 alignment
#if defined(NG_CONF_MEMORY_DBGINFO)
	, const char* src
#endif
	)
{
	NG_ASSERT(false, "使用禁止関数の呼び出し");
}

void operator delete(
	void* p
	, ng::IMemoryAllocator& alloc
#if defined(NG_CONF_MEMORY_DBGINFO)
	, const char* src
#endif
	)
{
#if defined(NG_CONF_MEMORY_DBGINFO)
#if defined(NG_CONF_MEMORY_PRINT_LOG)
	NG_DPRINTF("[del]   - <%s> 0x%p\n", alloc.GetName(), p);
	NG_DPRINTF("          %s\n", src);
#endif
#endif

	alloc.Free(
		p
		);
}

void operator delete[](
	void* p
	, ng::IMemoryAllocator& alloc
#if defined(NG_CONF_MEMORY_DBGINFO)
	, const char* src
#endif
	)
{
#if defined(NG_CONF_MEMORY_DBGINFO)
#if defined(NG_CONF_MEMORY_PRINT_LOG)
	NG_DPRINTF("[del[]] - <%s> 0x%p\n", alloc.GetName(), p);
	NG_DPRINTF("          %s\n", src);
#endif
#endif

	alloc.Free(
		ng::GetArrayHeadPointer(p)
		);
}
#endif

namespace ng
{
	void* GetArrayHeadPointer(void* p)
	{
		if (p == nullptr) {
			return nullptr;
		}

		return &(static_cast<int*>(p))[-1];
	}

	int GetArraySizeByPointer(void* p)
	{
		if (p == nullptr) {
			return 0;
		}

		return *static_cast<int*>(GetArrayHeadPointer(p));
	}

}	// namespace ng

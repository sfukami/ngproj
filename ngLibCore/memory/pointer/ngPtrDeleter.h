/*!
* @file		ngPtrDeleter.h
* @brief	スマートポインタ拡張用 メモリ解放
* @date		2020-07-02
* @author	s.fukami
*/

#ifndef __NG_CORE_PTR_DELETER_H__
#define __NG_CORE_PTR_DELETER_H__

#include "ngLibCore/common/debug/ngDbgMacro.h"
#include "ngLibCore/common/memory/ngAlloc.h"

namespace ng
{
	class IMemoryAllocator;
}

namespace ng
{
	/*!
	* @brief					スマートポインタ拡張用 メモリ解放
	*/
	template <class T>
	class NG_DECL CPtrDeleter
	{
	public:
		explicit CPtrDeleter(IMemoryAllocator& alloc) noexcept;
		void operator()(T* p);

	private:
		IMemoryAllocator* m_pAlloc;	//!< メモリアロケータ
	};
	
	template <class T>
	CPtrDeleter<T>::CPtrDeleter(IMemoryAllocator& alloc) noexcept
		: m_pAlloc(&alloc)
	{
	}

	template <class T>
	void CPtrDeleter<T>::operator()(T* p)
	{
		NG_ASSERT_NOT_NULL(m_pAlloc);
		NG_SAFE_DELETE(*m_pAlloc, p);
	}

}	// namespace ng

#endif	// __NG_CORE_PTR_DELETER_H__
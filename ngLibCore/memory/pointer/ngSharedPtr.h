﻿/*!
* @file		ngSharedPtr.h
* @brief	スマートポインタ std::shared_ptr拡張
* @date		2020-07-02
* @author	s.fukami
*/

#ifndef __NG_CORE_SHARED_PTR_H__
#define __NG_CORE_SHARED_PTR_H__

#include <memory>
#include "ngPtrDeleter.h"

namespace ng
{
	class IMemoryAllocator;
}

namespace ng
{
	//! std::shared_ptr拡張 基底クラス
	template <class T>
	using SharedPtrBase = std::shared_ptr<T>;

	/*!
	* @brief					スマートポインタ std::shared_ptr拡張
	*/
	template <class T>
	NG_DECL class CSharedPtr : public SharedPtrBase<T>
	{
	public:
		using BaseType = SharedPtrBase<T>;	//!< 基底クラス

	public:
		/*!
		* @brief					コンストラクタ
		* @param p					対象のポインタ
		* @param alloc				用いるメモリアロケータ
		*/
		explicit CSharedPtr(T* p, IMemoryAllocator& alloc) noexcept
			: BaseType(p, CPtrDeleter<T>(alloc))
		{ }
	};

}	// namespace ng

#endif	// __NG_CORE_SHARED_PTR_H__
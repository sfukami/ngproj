/*!
* @file		ngUniquePtr.h
* @brief	スマートポインタ std::unique_ptr拡張
* @date		2020-07-02
* @author	s.fukami
*/

#ifndef __NG_CORE_UNIQUE_PTR_H__
#define __NG_CORE_UNIQUE_PTR_H__

#include <memory>
#include "ngPtrDeleter.h"

namespace ng
{
	class IMemoryAllocator;
}

/*!
* @brief					CUniquePtr生成マクロ
* @param _type				生成する値の型
* @param _alloc				利用するメモリアロケータ
* @param _ctor				生成する値のコンストラクタ
*/
#define NG_MAKE_UNIQUE_PTR(_type, _alloc, _ctor) \
	ng::CUniquePtr<_type>(NG_NEW(_alloc) _ctor, _alloc)

namespace ng
{
	//! std::unique_ptr拡張 基底クラス
	template <class T>
	using UniquePtrBase = std::unique_ptr<T, CPtrDeleter<T> >;

	/*!
	* @brief					スマートポインタ std::unique_ptr拡張
	*/
	template <class T>
	NG_DECL class CUniquePtr : public UniquePtrBase<T>
	{
	public:
		using BaseType = UniquePtrBase<T>;	//!< 基底クラス

	public:
		explicit CUniquePtr() noexcept = default;

		/*!
		* @brief					コンストラクタ
		* @param p					対象のポインタ
		* @param alloc				用いるメモリアロケータ
		*/
		explicit CUniquePtr(T* p, IMemoryAllocator& alloc) noexcept
			: BaseType(p, CPtrDeleter<T>(alloc))
		{ }
	};

}	// namespace ng

#endif	// __NG_CORE_UNIQUE_PTR_H__
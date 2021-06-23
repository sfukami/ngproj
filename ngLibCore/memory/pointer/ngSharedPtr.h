/*!
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

/*!
* @brief					CSharedPtr生成マクロ
* @param _type				生成する値の型
* @param _alloc				利用するメモリアロケータ
* @param _ctor				生成する値のコンストラクタ
*/
#define NG_MAKE_SHARED_PTR(_type, _alloc) \
	NG_MAKE_SHARED_PTR_CTOR(_type, _alloc, _type)

/*!
* @brief					CSharedPtr生成マクロ（コンストラクタ指定）
* @param _type				生成する値の型
* @param _alloc				利用するメモリアロケータ
* @param _ctor				生成する値のコンストラクタ
*/
#define NG_MAKE_SHARED_PTR_CTOR(_type, _alloc, _ctor) \
	ng::CSharedPtr<_type>(NG_NEW(_alloc) _ctor, _alloc)

namespace ng
{
	//! std::shared_ptr拡張 基底クラス
	template <class T>
	using SharedPtrBase = std::shared_ptr<T>;

	/*!
	* @brief					スマートポインタ std::shared_ptr拡張
	*/
	template <class T>
	class NG_DECL CSharedPtr : public SharedPtrBase<T>
	{
	public:
		using BaseType = SharedPtrBase<T>;	//!< 基底クラス
		using ElemType = BaseType::element_type;	//!< 要素の型

	public:
		constexpr CSharedPtr() noexcept = default;

		/*!
		* @brief					コンストラクタ
		* @param p					対象のポインタ
		* @param alloc				用いるメモリアロケータ
		*/
		CSharedPtr(T* p, IMemoryAllocator& alloc) noexcept
			: BaseType(p, CPtrDeleter<T>(alloc))
		{ }

		/*!
		* @brief					コンストラクタ
		* @param other				変換元のスマートポインタ
		* @param p					対象のポインタ
		*/
		template <class Other>
		CSharedPtr(const CSharedPtr<Other>& other, T* p) noexcept
			: BaseType(other, p)
		{ }
	};

	/*! 静的キャスト */
	template <class Other, class Self>
	CSharedPtr<Other> StaticCast(const CSharedPtr<Self>& self)
	{
		return CSharedPtr<Other>(self, self.get());
	}

	/*! 動的キャスト */
	template <class Other, class Self>
	CSharedPtr<Other> DynamicCast(const CSharedPtr<Self>& self)
	{
		const auto p = dynamic_cast<typename CSharedPtr<Other>::ElemType*>(self.get());

		if(p) {
			return CSharedPtr<Other>(self, p);
		}

		return CSharedPtr<Other>();
	}

}	// namespace ng

#endif	// __NG_CORE_SHARED_PTR_H__
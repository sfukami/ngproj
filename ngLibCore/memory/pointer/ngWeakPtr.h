/*!
* @file		ngWeakPtr.h
* @brief	ウィークポインタ std::weak_ptr拡張
* @date		2020-07-21
* @author	s.fukami
*/

#ifndef __NG_CORE_WEAK_PTR_H__
#define __NG_CORE_WEAK_PTR_H__

#include <memory>

namespace ng
{
	template <class T> class CSharedPtr;
}

namespace ng
{
	//! std::weak_ptr拡張 基底クラス
	template <class T>
	using WeakPtrBase = std::shared_ptr<T>;

	/*!
	* @brief					ウィークポインタ
	*/
	template <class T>
	class CWeakPtr : public WeakPtrBase<T>
	{
	public:
		using BaseType = WeakPtrBase<T>;	//!< 基底クラス

	public:
		constexpr CWeakPtr() noexcept = default;

		/*!
		* @brief					コンストラクタ。監視対象を設定
		*/
		CWeakPtr(const CSharedPtr<T>& sp) noexcept
			: BaseType(sp)
		{ }
	};

}	// namespace ng

#endif	//__NG_CORE_WEAK_PTR_H__
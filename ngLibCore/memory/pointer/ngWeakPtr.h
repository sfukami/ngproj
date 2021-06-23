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
	//! std::weak_ptr拡張 基底クラス
	template <class T>
	using WeakPtrBase = std::weak_ptr<T>;

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
		* @note						キャストのため、CSharedPtr<T>ではなくstd::shared_ptr<T>を渡す
		*/
		explicit CWeakPtr(const std::shared_ptr<T>& sp) noexcept
			: BaseType(sp)
		{ }

		/*! 比較演算子のオーバーロード */
		bool operator==(nullptr_t rhs) const noexcept
		{
			return !(*this);
		}
		bool operator!=(nullptr_t rhs) const noexcept
		{
			return bool(*this);
		}

		/*! bool型変換演算子のオーバーロード */
		explicit operator bool() const noexcept
		{
			return !this->expired();
		}

		/*! 関節参照演算子のオーバーロード */
		T& operator*() const noexcept
		{
			return *(this->lock());
		}

		/*! アロー演算子のオーバーロード */
		T* operator->() const noexcept
		{
			return this->lock().get();
		}
	};

	/*! 静的キャスト */
	template <class Other, class Self>
	CWeakPtr<Other> StaticCast(const CWeakPtr<Self>& self)
	{
		return CWeakPtr<Other>(std::static_pointer_cast<Other>(self.lock()));
	}

	/*! 動的キャスト */
	template <class Other, class Self>
	CWeakPtr<Other> DynamicCast(const CWeakPtr<Self>& self)
	{
		if(std::shared_ptr<Other> otherPtr = std::dynamic_pointer_cast<Other>(self.lock())) {
			return CWeakPtr<Other>(otherPtr);
		}

		return CWeakPtr<Other>();
	}

}	// namespace ng

#endif	//__NG_CORE_WEAK_PTR_H__
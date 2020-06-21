/*!
* @file		ngArray.h
* @brief	配列 インターフェース
* @date		2019-02-06
* @author	s.fukami
*/

#ifndef __NG_CORE_ARRAY_H__
#define __NG_CORE_ARRAY_H__

namespace ng
{
	/*!
	* @brief					配列 インターフェース
	* @tparam T					格納する要素の型
	*/
	template <class T>
	class NG_DECL IArray
	{
	public:
		typedef T ElemType;		//!< 要素の型

	public:
		IArray() { }
		virtual ~IArray() { }

		/*! 先頭の要素を取得する */
		virtual ElemType& Front() = 0;

		/*! 先頭の要素を取得する */
		virtual const ElemType& Front() const = 0;

		/*! 末尾の要素を取得する */
		virtual ElemType& Back() = 0;

		/*! 末尾の要素を取得する */
		virtual const ElemType& Back() const = 0;

		/*! 指定位置の要素を取得する */
		virtual ElemType& operator[](u32 n) = 0;
		virtual const ElemType& operator[](u32 n) const = 0;

		/*! 要素数取得 */
		virtual u32 Size() const = 0;
	};

}	// namespace ng

#endif	// __NG_CORE_ARRAY_H__
/*!
* @file		ngStack.h
* @brief	スタック インターフェース
* @date		2018-12-06
* @author	s.fukami
*/

#ifndef __NG_CORE_STACK_H__
#define __NG_CORE_STACK_H__

namespace ng
{
	/*!
	* スタック インターフェース
	*
	* @tparam T					格納する要素の型
	*/
	template <typename T>
	class NG_DECL IStack
	{
	public:
		typedef T ElemType;		//!< 要素の型

	public:
		IStack() { }
		virtual ~IStack() { }

		/*! 先頭へ要素を追加する */
		virtual void Push(const ElemType& elem) = 0;

		/*! 先頭の要素を削除する */
		virtual void Pop() = 0;

		/*! 先頭の要素を取得する */
		virtual ElemType& Top() = 0;

		/*! 先頭の要素を取得する */
		virtual const ElemType& Top() const = 0;

		/*! 指定インデックスの要素を取得する */
		virtual ElemType& operator[](int index) = 0;

		/*! 指定インデックスの要素を取得する */
		virtual const ElemType& operator[](int index) const = 0;

		/*! 要素を全て削除 */
		virtual void Clear() = 0;

		/*! 要素が無いか調べる */
		virtual bool Empty() const = 0;

		/*! 要素数取得 */
		virtual u32 Size() const = 0;

		/*! 最大要素数取得 */
		virtual u32 MaxSize() const = 0;

		/*! 要素数が最大か調べる */
		virtual bool Full() const = 0;
	};

}	// namespace ng

#endif	// __NG_CORE_STACK_H__
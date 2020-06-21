/*!
* @file		ngQueue.h
* @brief	キュー インターフェース
* @date		2017-09-06
* @author	s.fukami
*/

#ifndef __NG_CORE_QUEUE_H__
#define __NG_CORE_QUEUE_H__

namespace ng
{
	/*!
	* @brief					キュー インターフェース
	* @tparam T					格納する要素の型
	*/
	template <class T>
	class NG_DECL IQueue
	{
	public:
		typedef T ElemType;		//!< 要素の型

	public:
		IQueue() { }
		virtual ~IQueue() { }

		/*! 末尾へ要素を追加する */
		virtual void PushBack(const ElemType& elem) = 0;

		/*! 先頭の要素を削除する */
		virtual void PopFront() = 0;

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

	/*!
	* @brief					両端キュー インターフェース
	* @tparam T					格納する要素の型
	*/
	template <class T>
	class NG_DECL IDeque : public IQueue<T>
	{
	public:
		typedef T ElemType;		//!< 要素の型

	public:
		/*! 先頭へ要素を追加する */
		virtual void PushFront(const ElemType& elem) = 0;

		/*! 末尾の要素を削除する */
		virtual void PopBack() = 0;
	};

}	// namespace ng

#endif	// __NG_CORE_QUEUE_H__
/*!
* @file		ngIntrusiveListBase.h
* @brief	侵入型リスト 基底クラス
* @date		2017-09-12
* @author	s.fukami
*/

#ifndef __NG_CORE_INTRUSIVE_LIST_BASE_H__
#define __NG_CORE_INTRUSIVE_LIST_BASE_H__

#include "../ngList.h"
#include "../ngListLinkedType.h"

namespace ng
{
	/*!
	* @brief					侵入型リスト ベースクラス
	* @tparam T					格納する要素の型
	* @tparam LinkedType		リンクタイプ(BidirectionalLinked もしくは ForwardLinked)
	*/
	template <class T, class LinkedType = BidirectionalLinked>
	class NG_DECL CIntrusiveListBase
	{
		// 使用しない
	};

	/*!
	* @brief					侵入型リスト ベースクラス侵入型リスト ベースクラス 双方向
	* @tparam T					格納する要素の型
	*/
	template <class T>
	class NG_DECL CIntrusiveListBase<T, BidirectionalLinked> : public IList<T, BidirectionalLinked>
	{
	public:
		typedef IList<T, BidirectionalLinked> BaseType;
	};

	/*!
	* @brief					侵入型リスト ベースクラス侵入型リスト ベースクラス 単方向
	* @tparam T					格納する要素の型
	*/
	template <class T>
	class NG_DECL CIntrusiveListBase<T, ForwardLinked> : public IList<T, ForwardLinked>
	{
	public:
		typedef IList<T, ForwardLinked> BaseType;
	};

	/*!
	* @brief					侵入型リスト ベースクラス侵入型リスト ベースクラス 双方向
	*							Tがポインタ型の部分特殊化版
	* @tparam T					格納する要素の型
	*/
	template <class T>
	class NG_DECL CIntrusiveListBase<T*, BidirectionalLinked> : public IList<T, BidirectionalLinked>
	{
	public:
		typedef IList<T, BidirectionalLinked> BaseType;
	};

	/*!
	* @brief					侵入型リスト ベースクラス侵入型リスト ベースクラス 単方向
	*							Tがポインタ型の部分特殊化版
	* @tparam T					格納する要素の型
	*/
	template <class T>
	class NG_DECL CIntrusiveListBase<T*, ForwardLinked> : public IList<T, ForwardLinked>
	{
	public:
		typedef IList<T, ForwardLinked> BaseType;
	};

	/*!
	* @brief					侵入型リスト
	* @tparam T					格納する要素の型
	* @tparam LinkedType		リンクタイプ(BidirectionalLinked もしくは ForwardLinked)
	* @attention				当リストの全てのノードは CIntrusiveListNodeクラス を継承する必要がある
	*							また、リストへ格納した要素を再びリストへ格納することは、それを一度リストから削除しない限り禁止とする
	*/
	template <class T, class LinkedType = BidirectionalLinked>
	class NG_DECL CIntrusiveList
	{
		// 使用しない
	};

	/*!
	* @brief					侵入型リスト
	* 							Tがポインタ型の部分特殊化版
	* @tparam T					格納する値の型
	* @tparam LinkedType		リンクタイプ(BidirectionalLinked もしくは ForwardLinked)
	* @attention				ポインタは実体を伴う保障がないため使用禁止
	*/
	/*
	template <class T, class LinkedType>
	class NG_DECL CIntrusiveList<T*, LinkedType>
	{
		NG_STATIC_ASSERT(
			NG_SIZEOF(T*)<0
			, "Instrusive List with pointer type template parameter is disabled."
			);
	};
	*/

}	// namespace ng

#endif	// __NG_CORE_INTRUSIVE_LIST_BASE_H__
/*!
* @file		ngIntrusiveListNode.h
* @brief	侵入型リストノード
* @date		2017-09-12
* @author	s.fukami
*/

#ifndef __NG_CORE_INTRUSIVE_LIST_NODE_H__
#define __NG_CORE_INTRUSIVE_LIST_NODE_H__

#include "../ngListLinkedType.h"
#include "../ngListNode.h"

namespace ng
{
	/*!
	* @brief					侵入型リスト用ノード
	* @tparam T					格納する要素の型
	* @tparam LinkedType		リンクタイプ(BidirectionalLinked もしくは ForwardLinked)
	*/
	template <class T, class LinkedType = BidirectionalLinked>
	class NG_DECL CIntrusiveListNode : public CListNodeBase<T, LinkedType>
	{
		template <class T, class LinkedType>
		friend class CIntrusiveList;

	public:
		typedef typename CListNodeBase<T, LinkedType>::ElemType ElemType;
		typedef typename CListNodeBase<T, LinkedType>::NodeType NodeType;

	public:
		CIntrusiveListNode();
		virtual ~CIntrusiveListNode();

		/*! 前ノード取得 */
		NodeType* GetPrev();

		/*! 前ノード取得 */
		const NodeType* GetPrev() const;

		/*! 次ノード取得 */
		NodeType* GetNext();

		/*! 次ノード取得 */
		const NodeType* GetNext() const;

		/*! 要素を取得 */
		ElemType& GetElem();

		/*! 要素を取得 */
		const ElemType& GetElem() const;

	private:
		/*! 前ノード設定 */
		void _setPrev(NodeType* pNode);

		/*! 次ノード設定 */
		void _setNext(NodeType* pNode);
	};

	template <class T, class LinkedType>
	CIntrusiveListNode<T, LinkedType>::CIntrusiveListNode()
	{
	}

	template <class T, class LinkedType>
	CIntrusiveListNode<T, LinkedType>::~CIntrusiveListNode()
	{
	}

	template <class T, class LinkedType>
	NG_INLINE typename CIntrusiveListNode<T, LinkedType>::NodeType* CIntrusiveListNode<T, LinkedType>::GetPrev()
	{
		return this->prev;
	}

	template <class T, class LinkedType>
	NG_INLINE typename const CIntrusiveListNode<T, LinkedType>::NodeType* CIntrusiveListNode<T, LinkedType>::GetPrev() const
	{
		return this->prev;
	}

	template <class T, class LinkedType>
	NG_INLINE typename CIntrusiveListNode<T, LinkedType>::NodeType* CIntrusiveListNode<T, LinkedType>::GetNext()
	{
		return this->next;
	}

	template <class T, class LinkedType>
	typename const CIntrusiveListNode<T, LinkedType>::NodeType* CIntrusiveListNode<T, LinkedType>::GetNext() const
	{
		return this->next;
	}

	template <class T, class LinkedType>
	NG_INLINE typename CIntrusiveListNode<T, LinkedType>::ElemType& CIntrusiveListNode<T, LinkedType>::GetElem()
	{
		return *static_cast<ElemType*>(this);
	}

	template <class T, class LinkedType>
	NG_INLINE typename const CIntrusiveListNode<T, LinkedType>::ElemType& CIntrusiveListNode<T, LinkedType>::GetElem() const
	{
		return *static_cast<const ElemType*>(this);
	}

	template <class T, class LinkedType>
	NG_INLINE void CIntrusiveListNode<T, LinkedType>::_setPrev(NodeType* pNode)
	{
		this->prev = pNode;
	}

	template <class T, class LinkedType>
	NG_INLINE void CIntrusiveListNode<T, LinkedType>::_setNext(NodeType* pNode)
	{
		this->next = pNode;
	}

	/*!
	* @brief					侵入型リスト用ノード
	* 							Tがポインタ型の部分特殊化版
	* @tparam T					格納する要素の型
	* @tparam LinkedType		リンクタイプ(BidirectionalLinked もしくは ForwardLinked)
	* @attention				ポインタは実体を伴う保障がないため使用禁止
	*/
	template <class T, class LinkedType>
	class NG_DECL CIntrusiveListNode<T*, LinkedType>
	{
		NG_STATIC_ASSERT(
			NG_SIZEOF(T*)<0
			, "Instrusive List with pointer type template parameter is disabled."
			);
	};

}	// namespace ng

#endif	// __NG_CORE_INTRUSIVE_LIST_NODE_H__
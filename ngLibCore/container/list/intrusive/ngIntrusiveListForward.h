/*!
* @file		ngIntrusiveListForward.h
* @brief	侵入型リスト（単方向）
* @date		2017-09-12
* @author	s.fukami
*/

#ifndef __NG_CORE_INTRUSIVE_LIST_FORWARD_H__
#define __NG_CORE_INTRUSIVE_LIST_FORWARD_H__

#include "ngIntrusiveListBase.h"
#include "ngIntrusiveListNode.h"

namespace ng
{
	/*!
	* @brief					侵入型リスト 単方向
	* @tparam T					格納する要素の型
	*/
	template <class T>
	class NG_DECL CIntrusiveList<T, ForwardLinked> : public CIntrusiveListBase<T, ForwardLinked>
	{
	public:
		typedef typename CIntrusiveListBase<T, ForwardLinked>::BaseType BaseType;	//!< 基底クラス
		typedef typename BaseType::ElemType ElemType;	//!< 要素の型
		typedef typename BaseType::NodeType NodeType;	//!< ノードの型
		typedef CIntrusiveListNode<ElemType, ForwardLinked> MyNodeType;	// ノードの型（具象クラス）

	public:
		CIntrusiveList();
		virtual ~CIntrusiveList();

		/*! 先頭の要素を返す */
		ElemType& Front();

		/*! 先頭の要素を返す */
		const ElemType& Front() const;

		/*! 先頭に要素を挿入する */
		void PushFront(const ElemType& e);

		/*! 先頭の要素を取り出す */
		void PopFront();

		/*! 先頭のノードを返す */
		NodeType* Begin();

		/*! 先頭のノードを返す */
		const NodeType* Begin() const;

		/*! 終端のノードを返す */
		NodeType* End();

		/*! 終端のノードを返す */
		const NodeType* End() const;

		/*! 指定要素の後方に要素を追加する */
		void Insert(NodeType* pos, const ElemType& e);

		/*! 要素を全て削除 */
		void Clear();

		/*! 要素が無いか調べる */
		bool Empty() const;

		/*! 要素数取得 */
		u32 Size() const;

	private:
		/*! ダミーノードの初期化を行う */
		void _initDummyNode();

	private:
		MyNodeType	m_head;	//!< 先頭ノード
		u32			m_size;	//!< サイズ
	};

	template <class T>
	CIntrusiveList<T, ForwardLinked>::CIntrusiveList()
		: m_size(0)
	{
		_initDummyNode();
	}

	template <class T>
	CIntrusiveList<T, ForwardLinked>::~CIntrusiveList()
	{
	}

	template <class T>
	typename CIntrusiveList<T, ForwardLinked>::ElemType& CIntrusiveList<T, ForwardLinked>::Front()
	{
		NG_ASSERT_AND_ABORT( ! Empty());

		return m_head.next->GetElem();
	}

	template <class T>
	typename const CIntrusiveList<T, ForwardLinked>::ElemType& CIntrusiveList<T, ForwardLinked>::Front() const
	{
		NG_ASSERT_AND_ABORT( ! Empty());
		
		return m_head.next->GetElem();
	}

	template <class T>
	void CIntrusiveList<T, ForwardLinked>::PushFront(const ElemType& e)
	{
		this->_insertNodeBehind(&m_head, &const_cast<ElemType&>(e));
		m_size++;
	}

	template <class T>
	void CIntrusiveList<T, ForwardLinked>::PopFront()
	{
		if( ! Empty())
		{
			this->_removeNode(&m_head, m_head.next);
			m_size--;
		}
	}

	template <class T>
	typename CIntrusiveList<T, ForwardLinked>::NodeType* CIntrusiveList<T, ForwardLinked>::Begin()
	{
		return m_head.next;
	}

	template <class T>
	const typename CIntrusiveList<T, ForwardLinked>::NodeType* CIntrusiveList<T, ForwardLinked>::Begin() const
	{
		return m_head.next;
	}

	template <class T>
	typename CIntrusiveList<T, ForwardLinked>::NodeType* CIntrusiveList<T, ForwardLinked>::End()
	{
		return &m_head;
	}

	template <class T>
	const typename CIntrusiveList<T, ForwardLinked>::NodeType* CIntrusiveList<T, ForwardLinked>::End() const
	{
		return &m_head;
	}

	template <class T>
	void CIntrusiveList<T, ForwardLinked>::Insert(NodeType* pos, const ElemType& e)
	{
		this->_insertNodeBehind(pos, &const_cast<ElemType&>(e));
		m_size++;
	}

	template <class T>
	void CIntrusiveList<T, ForwardLinked>::Clear()
	{
		if( ! Empty())
		{
			PopFront();
		}
	}

	template <class T>
	NG_INLINE bool CIntrusiveList<T, ForwardLinked>::Empty() const
	{
		return (m_size == 0);
	}

	template <class T>
	NG_INLINE u32 CIntrusiveList<T, ForwardLinked>::Size() const
	{
		return m_size;
	}

	template <class T>
	NG_INLINE void CIntrusiveList<T, ForwardLinked>::_initDummyNode()
	{
		m_head.next = &m_head;
	}

}	// namespace ng

#endif	// __NG_CORE_INTRUSIVE_LIST_FORWARD_H__
/*!
* @file		ngIntrusiveListBidirectional.h
* @brief	侵入型リスト（双方向）
* @date		2017-09-12
* @author	s.fukami
*/

#ifndef __NG_CORE_INTRUSIVE_LIST_BIDIRECTIONAL_H__
#define __NG_CORE_INTRUSIVE_LIST_BIDIRECTIONAL_H__

#include "ngLibCore/common/ngCommon.h"
#include "ngIntrusiveListBase.h"
#include "ngIntrusiveListNode.h"

namespace ng
{
	/*!
	* @brief					侵入型リスト 双方向
	* @tparam T					格納する要素の型
	*/
	template <class T>
	class NG_DECL CIntrusiveList<T, BidirectionalLinked> : public CIntrusiveListBase<T, BidirectionalLinked>
	{
	public:
		typedef typename CIntrusiveListBase<T, BidirectionalLinked>::BaseType BaseType;	//!< 基底クラス
		typedef typename BaseType::ElemType ElemType;	//!< 要素の型
		typedef typename BaseType::NodeType NodeType;	//!< ノードの型
		typedef CIntrusiveListNode<ElemType, BidirectionalLinked> MyNodeType;	// ノードの型（具象クラス）

	public:
		CIntrusiveList();
		~CIntrusiveList();

		/*! 先頭の要素を返す */
		ElemType& Front();

		/*! 先頭の要素を返す */
		const ElemType& Front() const;

		/*! 末尾の要素を返す */
		ElemType& Back();

		/*! 末尾の要素を返す */
		const ElemType& Back() const;

		/*! 先頭に要素を挿入する */
		void PushFront(const ElemType& e);

		/*! 末尾に要素を挿入する */
		void PushBack(const ElemType& e);

		/*! 先頭の要素を取り出す */
		void PopFront();

		/*! 末尾の要素を取り出す */
		void PopBack();

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

		/*! 
		* @brief					posの指す要素を削除する
		* @return					削除された要素の次の要素を返す
		* @retval nullptr			削除失敗
		*/
		NodeType* Erase(NodeType* pos);

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
		u32			m_size;	//!< 要素数
	};

	template <class T>
	CIntrusiveList<T, BidirectionalLinked>::CIntrusiveList()
		: m_size(0)
	{
		_initDummyNode();
	}

	template <class T>
	CIntrusiveList<T, BidirectionalLinked>::~CIntrusiveList()
	{
		Clear();
	}

	template <class T>
	typename CIntrusiveList<T, BidirectionalLinked>::ElemType& CIntrusiveList<T, BidirectionalLinked>::Front()
	{
		NG_ASSERT_AND_ABORT( ! Empty());

		return m_head.next->GetElem();
	}

	template <class T>
	typename const CIntrusiveList<T, BidirectionalLinked>::ElemType& CIntrusiveList<T, BidirectionalLinked>::Front() const
	{
		NG_ASSERT_AND_ABORT( ! Empty());

		return m_head.next->GetElem();
	}

	template <class T>
	typename CIntrusiveList<T, BidirectionalLinked>::ElemType& CIntrusiveList<T, BidirectionalLinked>::Back()
	{
		NG_ASSERT_AND_ABORT( ! Empty());

		return m_head.prev->GetElem();
	}

	template <class T>
	typename const CIntrusiveList<T, BidirectionalLinked>::ElemType& CIntrusiveList<T, BidirectionalLinked>::Back() const
	{
		NG_ASSERT_AND_ABORT( ! Empty());

		return m_head.prev->GetElem();
	}

	template <class T>
	void CIntrusiveList<T, BidirectionalLinked>::PushFront(const ElemType& e)
	{
		this->_insertNodeBehind(&m_head, &const_cast<ElemType&>(e));
		m_size++;
	}

	template <class T>
	void CIntrusiveList<T, BidirectionalLinked>::PushBack(const ElemType& e)
	{
		this->_insertNodeFront(&m_head, &const_cast<ElemType&>(e));
		m_size++;
	}

	template <class T>
	void CIntrusiveList<T, BidirectionalLinked>::PopFront()
	{
		if( ! Empty())
		{
			this->_removeNode(m_head.next);
			m_size--;
		}
	}

	template <class T>
	void CIntrusiveList<T, BidirectionalLinked>::PopBack()
	{
		if( ! Empty())
		{
			this->_removeNode(m_head.prev);
			m_size--;
		}
	}

	template <class T>
	typename CIntrusiveList<T, BidirectionalLinked>::NodeType* CIntrusiveList<T, BidirectionalLinked>::Begin()
	{
		return m_head.next;
	}

	template <class T>
	const typename CIntrusiveList<T, BidirectionalLinked>::NodeType* CIntrusiveList<T, BidirectionalLinked>::Begin() const
	{
		return m_head.next;
	}

	template <class T>
	typename CIntrusiveList<T, BidirectionalLinked>::NodeType* CIntrusiveList<T, BidirectionalLinked>::End()
	{
		return &m_head;
	}

	template <class T>
	const typename CIntrusiveList<T, BidirectionalLinked>::NodeType* CIntrusiveList<T, BidirectionalLinked>::End() const
	{
		return &m_head;
	}

	template <class T>
	void CIntrusiveList<T, BidirectionalLinked>::Insert(NodeType* pos, const ElemType& e)
	{
		this->_insertNodeBehind(pos, &const_cast<ElemType&>(e));
		m_size++;
	}

	template <class T>
	typename CIntrusiveList<T, BidirectionalLinked>::NodeType* CIntrusiveList<T, BidirectionalLinked>::Erase(NodeType* pos)
	{
		if(Empty())
		{
			return nullptr;
		}
		if(pos == &m_head)
		{
			return &m_head;
		}

		NodeType* next = pos->GetNext();

		this->_removeNode(pos);

		m_size--;

		return next;
	}

	template <class T>
	void CIntrusiveList<T, BidirectionalLinked>::Clear()
	{
		NodeType* pNode = m_head.next;
		NodeType* pBuf = nullptr;

		while(pNode != &m_head)
		{
			pBuf = pNode->GetNext();
			this->_removeNode(pNode);
			pNode = pBuf;
		}

		m_size = 0;
	}

	template <class T>
	NG_INLINE bool CIntrusiveList<T, BidirectionalLinked>::Empty() const
	{
		return (m_size == 0);
	}

	template <class T>
	NG_INLINE u32 CIntrusiveList<T, BidirectionalLinked>::Size() const
	{
		return m_size;
	}

	template <class T>
	NG_INLINE void CIntrusiveList<T, BidirectionalLinked>::_initDummyNode()
	{
		m_head.next = &m_head;
		m_head.prev = &m_head;
	}

}	// namespace ng

#endif	// __NG_CORE_INTRUSIVE_LIST_BIDIRECTIONAL_H__
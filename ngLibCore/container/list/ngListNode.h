/*!
* @file		ngListNode.h
* @brief	リスト ノード
* @date		2017-11-24
* @author	s.fukami
*/

#ifndef __NG_CORE_LIST_NODE_H__
#define __NG_CORE_LIST_NODE_H__

#include "ngListLinkedType.h"

namespace ng
{
	/*!
	* @brief					リストノード インターフェース
	* @tparam Elem				格納する要素の型
	* @tparam LinkedType		リンクタイプ(BidirectionalLinked もしくは ForwardLinked)
	*/
	template <typename Elem, class LinkedType = BidirectionalLinked>
	class NG_DECL IListNode
	{
		// 使用禁止
		NG_STATIC_ASSERT(
			NG_SIZEOF(Elem)<0
			, "IListNode template parameter \"LinkedType\" is invalid."
			);
	};

	/*
	* @brief					双方向リストノード インターフェース
	* @tparam Elem				格納する要素の型
	*/
	template <typename Elem>
	class NG_DECL IListNode<Elem, BidirectionalLinked>
	{
	public:
		typedef Elem ElemType;	//!< 要素の型
		typedef IListNode<ElemType, BidirectionalLinked> NodeType;	//!< ノードの型

	public:
		IListNode() { }
		virtual ~IListNode() { }

		/*! 前ノード取得 */
		virtual NodeType* GetPrev() = 0;

		/*! 前ノード取得 */
		virtual const NodeType* GetPrev() const = 0;

		/*! 次ノード取得 */
		virtual NodeType* GetNext() = 0;

		/*! 次ノード取得 */
		virtual const NodeType* GetNext() const = 0;

		/*! 要素を取得 */
		virtual ElemType& GetElem() = 0;

		/*! 要素を取得 */
		virtual const ElemType& GetElem() const = 0;

		/*! 前ノード設定 */
		virtual void SetPrev(NodeType* pNode) = 0;

		/*! 前ノード設定 */
		virtual void SetNext(NodeType* pNode) = 0;
	};

	/*
	* @brief					単方向リストノード インターフェース
	* @tparam Elem				格納する要素の型
	*/
	template <typename Elem>
	class NG_DECL IListNode<Elem, ForwardLinked>
	{
	public:
		typedef Elem ElemType;	//!< 要素の型
		typedef IListNode<ElemType, ForwardLinked> NodeType;	//!< ノードの型

	public:
		IListNode() { }
		virtual ~IListNode() { }

		/*! 次ノード取得 */
		virtual NodeType* GetNext() = 0;

		/*! 次ノード取得 */
		virtual const NodeType* GetNext() const = 0;

		/*! 要素を取得 */
		virtual ElemType& GetElem() = 0;

		/*! 要素を取得 */
		virtual const ElemType& GetElem() const = 0;

		/*! 前ノード設定 */
		virtual void SetNext(NodeType* pNode) = 0;
	};

	/*!
	* @brief					リストノードベース
	* @tparam Elem				格納する要素の型
	*/
	template <typename Elem, class LinkedType = BidirectionalLinked>
	class NG_DECL CListNodeBase : public IListNode<Elem, LinkedType>
	{
		// 使用不可
	};

	/*!
	* @brief					双方向リストノード ベース
	* @tparam Elem				格納する要素の型
	*/
	template <typename Elem>
	class NG_DECL CListNodeBase<Elem, BidirectionalLinked> : public IListNode<Elem, BidirectionalLinked>
	{
	public:
		typedef Elem ElemType;	//!< 要素の型
		typedef IListNode<ElemType, BidirectionalLinked> NodeType;	//!< ノードの型

	public:
		CListNodeBase();
		virtual ~CListNodeBase();

		/*! 前ノード取得 */
		virtual NodeType* GetPrev();

		/*! 前ノード取得 */
		virtual const NodeType* GetPrev() const;

		/*! 次ノード取得 */
		virtual NodeType* GetNext();

		/*! 次ノード取得 */
		virtual const NodeType* GetNext() const;

		/*! 要素を取得 */
		virtual ElemType& GetElem() = 0;

		/*! 要素を取得 */
		virtual const ElemType& GetElem() const = 0;

		/*! 前ノード設定 */
		virtual void SetPrev(NodeType* pNode);

		/*! 前ノード設定 */
		virtual void SetNext(NodeType* pNode);

	protected:
		NodeType* prev;	//!< 前ノード
		NodeType* next;	//!< 次ノード
	};

	template <typename Elem>
	CListNodeBase<Elem, BidirectionalLinked>::CListNodeBase()
		: prev(nullptr)
		, next(nullptr)
	{
	}

	template <typename Elem>
	CListNodeBase<Elem, BidirectionalLinked>::~CListNodeBase()
	{
	}

	template <typename Elem>
	NG_INLINE typename CListNodeBase<Elem, BidirectionalLinked>::NodeType* CListNodeBase<Elem, BidirectionalLinked>::GetPrev()
	{
		return prev;
	}

	template <typename Elem>
	NG_INLINE typename const CListNodeBase<Elem, BidirectionalLinked>::NodeType* CListNodeBase<Elem, BidirectionalLinked>::GetPrev() const
	{
		return prev;
	}

	template <typename Elem>
	NG_INLINE typename CListNodeBase<Elem, BidirectionalLinked>::NodeType* CListNodeBase<Elem, BidirectionalLinked>::GetNext()
	{
		return next;
	}

	template <typename Elem>
	NG_INLINE typename const CListNodeBase<Elem, BidirectionalLinked>::NodeType* CListNodeBase<Elem, BidirectionalLinked>::GetNext() const
	{
		return next;
	}

	template <typename Elem>
	NG_INLINE void CListNodeBase<Elem, BidirectionalLinked>::SetPrev(NodeType* pNode)
	{
		prev = pNode;
	}

	template <typename Elem>
	NG_INLINE void CListNodeBase<Elem, BidirectionalLinked>::SetNext(NodeType* pNode)
	{
		next = pNode;
	}

	/*!
	* @brief					単方向リストノード ベース
	* @tparam Elem				格納する要素の型
	*/
	template <typename Elem>
	class NG_DECL CListNodeBase<Elem, ForwardLinked> : public IListNode<Elem, ForwardLinked>
	{
	public:
		typedef Elem ElemType;	//!< 要素の型
		typedef IListNode<ElemType, ForwardLinked> NodeType;	//!< ノードの型

	public:
		CListNodeBase();
		virtual ~CListNodeBase();

		/*! 次ノード取得 */
		virtual NodeType* GetNext();

		/*! 次ノード取得 */
		virtual const NodeType* GetNext() const;

		/*! 要素を取得 */
		virtual ElemType& GetElem() = 0;

		/*! 要素を取得 */
		virtual const ElemType& GetElem() const = 0;

		/*! 前ノード設定 */
		virtual void SetNext(NodeType* pNode);

	protected:
		NodeType* next;	//!< 次ノード
	};

	template <typename Elem>
	CListNodeBase<Elem, ForwardLinked>::CListNodeBase()
		: next(nullptr)
	{
	}

	template <typename Elem>
	CListNodeBase<Elem, ForwardLinked>::~CListNodeBase()
	{
	}

	template <typename Elem>
	typename CListNodeBase<Elem, ForwardLinked>::NodeType* CListNodeBase<Elem, ForwardLinked>::GetNext()
	{
		return next;
	}

	template <typename Elem>
	typename const CListNodeBase<Elem, ForwardLinked>::NodeType* CListNodeBase<Elem, ForwardLinked>::GetNext() const
	{
		return next;
	}

	template <typename Elem>
	void CListNodeBase<Elem, ForwardLinked>::SetNext(NodeType* pNode)
	{
		next = pNode;
	}

	/*!
	* @brief					双方向リストノード
	*/
	template <typename Elem>
	using CBidirectionalListNode = CListNodeBase<Elem, BidirectionalLinked>;

	/*!
	* @brief					単方向リストノード
	*/
	template <typename Elem>
	using CForwardListNode = CListNodeBase<Elem, ForwardLinked>;

}	// namespace ng

#endif	// __NG_CORE_LIST_NODE_H__
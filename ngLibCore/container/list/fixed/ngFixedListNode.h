/*!
* @file		ngFixedListNode.h
* @brief	固定長リスト ノード
* @date		2017-12-02
* @author	s.fukami
*/

#ifndef __NG_CORE_FIXED_LIST_NODE_H__
#define __NG_CORE_FIXED_LIST_NODE_H__

namespace ng
{
	/*!
	* @brief					固定長リストノード
	* @tparam NodeBase			基底となるノードクラス
	*/
	template <class NodeBase>
	class NG_DECL CFixedListNode : public NodeBase
	{
		template <typename T, class LinkedType>
		friend class CFixedListBase;

	public:
		typedef typename NodeBase::ElemType ElemType;	//!< 要素の型

	public:
		/*! 要素を取得 */
		virtual typename ElemType& GetElem();
		virtual typename const ElemType& GetElem() const;
	};

	template <class NodeBase>
	typename CFixedListNode<NodeBase>::ElemType& CFixedListNode<NodeBase>::GetElem()
	{
		return *PointerOffset<ElemType*>(this, NG_SIZEOF(*this));
	}

	template <class NodeBase>
	typename const CFixedListNode<NodeBase>::ElemType& CFixedListNode<NodeBase>::GetElem() const
	{
		return *PointerOffset<const ElemType*>(this, NG_SIZEOF(*this));
	}

	/*!
	* @brief					固定長リストノード 要素がポインタのもの
	* @tparam NodeBase			基底となるノードクラス
	*/
	template <class NodeBase>
	class NG_DECL CFixedListNodePtr : public NodeBase
	{
		template <typename T, class LinkedType>
		friend class CFixedListBase;

	public:
		typedef typename NodeBase::ElemType ElemType;	//!< 要素の型

	public:
		/*! 要素を取得 */
		virtual typename ElemType GetElem();
		virtual typename const ElemType GetElem() const;
	};

	template <class NodeBase>
	typename CFixedListNodePtr<NodeBase>::ElemType CFixedListNodePtr<NodeBase>::GetElem()
	{
		return PointerOffset<ElemType>(this, NG_SIZEOF(*this));
	}

	template <class NodeBase>
	typename const CFixedListNodePtr<NodeBase>::ElemType CFixedListNodePtr<NodeBase>::GetElem() const
	{
		return PointerOffset<const ElemType>(this, NG_SIZEOF(*this));
	}

}	// namespace ng

#endif	// __NG_CORE_FIXED_LIST_NODE_H__
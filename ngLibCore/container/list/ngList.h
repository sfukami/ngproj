/*!
* @file		ngList.h
* @brief	リスト インターフェース
* @date		2017-11-24
* @author	s.fukami
*/

#ifndef __NG_CORE_LIST_H__
#define __NG_CORE_LIST_H__

#include "ngListLinkedType.h"
#include "ngListNode.h"

namespace ng
{
	/*!
	* @brief					リスト インターフェース
	* @tparam Elem				格納する要素の型
	* @tparam LinkedType		リンクタイプ(BidirectionalLinked もしくは ForwardLinked)
	*/
	template <typename Elem, class LinkedType = BidirectionalLinked>
	class NG_DECL IList
	{
		// 使用禁止
		NG_STATIC_ASSERT(
			NG_SIZEOF(Elem)<0
			, "IList template parameter \"LinkedType\" is invalid."
			);
	};

	/*!
	* @brief					双方向リスト インターフェース
	* @tparam Elem				格納する要素の型
	*/
	template <typename Elem>
	class NG_DECL IList<Elem, BidirectionalLinked>
	{
	public:
		typedef Elem ElemType;	//!< 要素の型
		typedef IListNode<ElemType, BidirectionalLinked> NodeType;	//!< ノードの型

	public:
		IList() { }
		virtual ~IList() { }

		/*! 先頭の要素を返す */
		virtual ElemType& Front() = 0;

		/*! 先頭の要素を返す */
		virtual const ElemType& Front() const = 0;

		/*! 末尾の要素を返す */
		virtual ElemType& Back() = 0;

		/*! 末尾の要素を返す */
		virtual const ElemType& Back() const = 0;

		/*! 先頭に要素を挿入する */
		virtual void PushFront(const ElemType& e) = 0;

		/*! 末尾に要素を挿入する */
		virtual void PushBack(const ElemType& e) = 0;

		/*! 先頭の要素を取り出す */
		virtual void PopFront() = 0;

		/*! 末尾の要素を取り出す */
		virtual void PopBack() = 0;

		/*! 先頭のノードを返す */
		virtual NodeType* Begin() = 0;

		/*! 先頭のノードを返す */
		virtual const NodeType* Begin() const = 0;

		/*! 終端のノードを返す */
		virtual NodeType* End() = 0;

		/*! 終端のノードを返す */
		virtual const NodeType* End() const = 0;

		/*! 指定要素の後方に要素を追加する */
		virtual void Insert(NodeType* pos, const ElemType& e) = 0;

		/*! 
		* @brief					posの指す要素を削除する
		* @return					削除された要素の次の要素を返す
		*/
		virtual NodeType* Erase(NodeType* pos) = 0;

		/*! 要素を全て削除 */
		virtual void Clear() = 0;

		/*! 要素が無いか調べる */
		virtual bool Empty() const = 0;

		/*! 要素数取得 */
		virtual u32 Size() const = 0;
		
	protected:
		/*! 2つのノード同士を繋げる */
		virtual void _linkNode(NodeType* front, NodeType* behind);

		/*! 指定したノードの後方にノードを挿入 */
		virtual void _insertNodeBehind(NodeType* front, NodeType* in);
		
		/*! 指定したノードの前方にノードを挿入 */
		virtual void _insertNodeFront(NodeType* behind, NodeType* in);

		/*! 指定したノードをリンクから外す */
		virtual void _removeNode(NodeType* node);

	private:
		/*! ノードNULLチェック */
		void _checkNodeIsNull(NodeType* node) const;
	};

	template <typename Elem>
	NG_INLINE void IList<Elem, BidirectionalLinked>::_linkNode(NodeType* front, NodeType* behind)
	{
	#if defined(NG_DEBUG)
		_checkNodeIsNull(front);
		_checkNodeIsNull(behind);
	#endif
		front->SetNext(behind);
		behind->SetPrev(front);
	}

	template <typename Elem>
	NG_INLINE void IList<Elem, BidirectionalLinked>::_insertNodeBehind(NodeType* front, NodeType* in)
	{
	#if defined(NG_DEBUG)
		_checkNodeIsNull(in);
	#endif
		in->SetPrev(front);
		in->SetNext(front->GetNext());

		front->GetNext()->SetPrev(in);
		front->SetNext(in);
	}

	template <typename Elem>
	NG_INLINE void IList<Elem, BidirectionalLinked>::_insertNodeFront(NodeType* behind, NodeType* in)
	{
	#if defined(NG_DEBUG)
		_checkNodeIsNull(in);
	#endif
		in->SetPrev(behind->GetPrev());
		in->SetNext(behind);

		behind->GetPrev()->SetNext(in);
		behind->SetPrev(in);
	}

	template <typename Elem>
	NG_INLINE void IList<Elem, BidirectionalLinked>::_removeNode(NodeType* node)
	{
		node->GetPrev()->SetNext(node->GetNext());
		node->GetNext()->SetPrev(node->GetPrev());

		node->SetNext(nullptr);
		node->SetPrev(nullptr);
	}

	/*! ノードNULLチェック */
	template <typename Elem>
	NG_INLINE void IList<Elem, BidirectionalLinked>::_checkNodeIsNull(NodeType* node) const
	{
		NG_ASSERT(node->GetNext() == nullptr, "ノードに既存のリンクが存在します.");
		NG_ASSERT(node->GetPrev() == nullptr, "ノードに既存のリンクが存在します.");
	}

	/*!
	* @brief					単方向リスト インターフェース
	* @tparam Elem				格納する要素の型
	*/
	template <typename Elem>
	class NG_DECL IList<Elem, ForwardLinked>
	{
	public:
		typedef Elem ElemType;	//!< 要素の型
		typedef IListNode<ElemType, ForwardLinked> NodeType;	//!< ノードの型

	public:
		/*! コンストラクタ */
		IList() { }

		/*! デストラクタ */
		virtual ~IList() { }

		/*! 先頭の要素を返す */
		virtual ElemType& Front() = 0;

		/*! 先頭の要素を返す */
		virtual const ElemType& Front() const = 0;

		/*! 先頭に要素を挿入する */
		virtual void PushFront(const ElemType& e) = 0;

		/*! 先頭の要素を取り出す */
		virtual void PopFront() = 0;

		/*! 先頭のノードを返す */
		virtual NodeType* Begin() = 0;

		/*! 先頭のノードを返す */
		virtual const NodeType* Begin() const = 0;

		/*! 終端のノードを返す */
		virtual NodeType* End() = 0;

		/*! 終端のノードを返す */
		virtual const NodeType* End() const = 0;

		/*! 指定要素の後方に要素を追加する */
		virtual void Insert(NodeType* pos, const ElemType& e) = 0;

		/*! 要素を全て削除 */
		virtual void Clear() = 0;

		/*! 要素が無いか調べる */
		virtual bool Empty() const = 0;

		/*! 要素数取得 */
		virtual u32 Size() const = 0;

	protected:
		/*! 指定したノードの後方にノードを挿入 */
		virtual void _insertNodeBehind(NodeType* front, NodeType* in);

		/*! 指定したノードをリンクから外す */
		virtual void _removeNode(NodeType* prev, NodeType* node);

	private:
		/*! ノードNULLチェック */
		void _checkNodeIsNull(NodeType* node) const;
	};

	template <typename Elem>
	NG_INLINE void IList<Elem, ForwardLinked>::_insertNodeBehind(NodeType* front, NodeType* in)
	{
	#if defined(NG_DEBUG)
		_checkNodeIsNull(in);
	#endif
		in->SetNext(front->GetNext());
		front->SetNext(in);
	}

	template <typename Elem>
	NG_INLINE void IList<Elem, ForwardLinked>::_removeNode(NodeType* prev, NodeType* node)
	{
		prev->SetNext(node->GetNext());

		node->SetNext(nullptr);
	}

	template <typename Elem>
	NG_INLINE void IList<Elem, ForwardLinked>::_checkNodeIsNull(NodeType* node) const
	{
		NG_ASSERT(node->GetNext() == nullptr, "ノードに既存のリンクが存在します.");
	}

}	// namespace ng

#endif	// __NG_CORE_LIST_H__
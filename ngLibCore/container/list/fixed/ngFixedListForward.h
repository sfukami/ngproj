/*!
* @file		ngFixedListForward.h
* @brief	固定長リスト（単方向）
* @date		2017-12-02
* @author	s.fukami
*/

#ifndef __NG_CORE_FIXED_LIST_FORWARD_H__
#define __NG_CORE_FIXED_LIST_FORWARD_H__

#include "ngLibCore/common/ngCommon.h"
#include "ngLibCore/allocator/ngMemoryAllocator.h"
#include "ngLibCore/memory/pool/ngMemoryPool.h"
#include "../ngList.h"
#include "ngFixedListBase.h"
#include "ngFixedListNode.h"

namespace ng
{
	/*!
	* @brief					固定長リスト(単方向) ベースクラス
	* @tparam T					格納する要素の型
	* @note						初期化時にバッファを指定する固定長のコンテナ
	*/
	template <typename T>
	class NG_DECL CFixedListBase<T, ForwardLinked> : public IList<T, ForwardLinked>
	{
	public:
		typedef IList<T, ForwardLinked> BaseType;	//!< 基底クラス
		typedef typename BaseType::ElemType ElemType;	//!< 要素の型
		typedef typename BaseType::NodeType NodeType;	//!< ノードの型
		typedef CFixedListNode<CForwardListNode<T> > MyNodeType;	//!< ノードの型（具象クラス）

	public:
		CFixedListBase();
		virtual ~CFixedListBase();

		/*! 先頭の要素を返す */
		virtual ElemType& Front();

		/*! 先頭の要素を返す */
		virtual const ElemType& Front() const;

		/*! 先頭に要素を挿入する */
		virtual void PushFront(const ElemType& e);

		/*! 先頭の要素を取り出す */
		virtual void PopFront();

		/*! 先頭のノードを返す */
		virtual NodeType* Begin();

		/*! 先頭のノードを返す */
		virtual const NodeType* Begin() const;

		/*! 終端のノードを返す */
		virtual NodeType* End();

		/*! 終端のノードを返す */
		virtual const NodeType* End() const;

		/*! 指定要素の後方に要素を追加する */
		virtual void Insert(NodeType* pos, const ElemType& e);

		/*! 要素を全て削除 */
		virtual void Clear();

		/*! 要素が無いか調べる */
		virtual bool Empty() const;

		/*! 要素数取得 */
		virtual u32 Size() const;

		/*! 最大要素数取得 */
		virtual u32 MaxSize() const;

		/*! 要素数が最大か調べる */
		virtual bool Full() const;

	protected:
		/*! 初期化 */
		NG_ERRCODE _initialize(u32 max);

		/*! 終了処理 */
		void _finalize();

		/*! 初期化済みかを調べる */
		bool _isInit() const;

		/*! メモリをプールする */
		NG_ERRCODE _poolMemory(void* pMemory, size_type memSize);
		NG_ERRCODE _poolMemory(IMemoryAllocator& alloc, size_type memSize);

	private:
		/*! ダミーノードの初期化を行う */
		void _initDummyNode();

		/*! ノードを生成 */
		MyNodeType* _createNode(void* p);

		/*! ノードを破棄 */
		void _destroyNode(NodeType* pNode);

		/*! フリーノードよりノードを取出し */
		NodeType* _popFreeNode();

		/*! 要素を生成 */
		void _createElem(NodeType* pNode, const ElemType* pElem);

		/*! 要素を破棄 */
		void _destroyElem(NodeType* pNode, ElemType* pElem);

		/*! メモリ領域を取得 */
		void* _getMemory();
		const void* _getMemory() const;

		/*! メモリ領域のサイズを取得 */
		size_type _getMemSize() const;

	public:
		static const size_type NODE_SIZE = NG_SIZEOF(MyNodeType);	//!< ノードのサイズ
		static const size_type ELEM_SIZE = NG_SIZEOF(ElemType);		//!< 要素のサイズ
		static const size_type BLOCK_SIZE = NODE_SIZE + ELEM_SIZE;	//!< ブロック（ノード+要素）のサイズ

	protected:
		MyNodeType	m_freeHead;	//!< 先頭のフリーノード
		MyNodeType	m_useHead;	//!< 先頭のユーズノード
		u32			m_size;		//!< 要素数
		u32			m_maxSize;	//!< 最大要素数
		CMemoryPool	m_memPool;	//!< メモリプール
	};

	template <typename T>
	CFixedListBase<T, ForwardLinked>::CFixedListBase()
		: m_size(0)
		, m_maxSize(0)
	{
	}

	template <typename T>
	CFixedListBase<T, ForwardLinked>::~CFixedListBase()
	{
	}

	template <typename T>
	NG_ERRCODE CFixedListBase<T, ForwardLinked>::_initialize(u32 max)
	{
		void* pMemory = m_memPool.GetMemory();
		size_type memSize = m_memPool.GetSize();

		NG_ASSERT(pMemory);
		if( ! pMemory)
		{
			return eNG_E_INVALIDMEMORY;
		}

		u32 capacity = (u32)(memSize / BLOCK_SIZE);

		NG_ASSERT(max <= capacity);
		if(max > capacity)
		{
			return eNG_E_CAPACITYLACK;
		}

		m_maxSize = max;

		// ダミーノードを初期化
		_initDummyNode();

		// 全てのフリーノードを作成
		MyNodeType* pBuf = PointerCast<MyNodeType*>(pMemory);
		MyNodeType* pPrev = &m_freeHead;
		for(unsigned int i = 0; i < m_maxSize; i++, pBuf = PointerOffset<MyNodeType*>(pBuf, BLOCK_SIZE))
		{
			pBuf = _createNode(pBuf);
			this->_insertNodeBehind(pPrev, pBuf);
			pPrev = pBuf;
		}

		return eNG_S_OK;
	}

	template <typename T>
	void CFixedListBase<T, ForwardLinked>::_finalize()
	{
		Clear();

		m_size = 0;
		m_maxSize = 0;
		m_memPool.Unpool();
	}

	template <typename T>
	typename CFixedListBase<T, ForwardLinked>::ElemType& CFixedListBase<T, ForwardLinked>::Front()
	{
		NG_ASSERT_AND_ABORT(_isInit());
		NG_ASSERT_AND_ABORT( ! Empty());

		return m_useHead.next->GetElem();
	}

	template <typename T>
	typename const CFixedListBase<T, ForwardLinked>::ElemType& CFixedListBase<T, ForwardLinked>::Front() const
	{
		NG_ASSERT_AND_ABORT(_isInit());
		NG_ASSERT_AND_ABORT( ! Empty());

		return m_useHead.next->GetElem();
	}

	template <typename T>
	void CFixedListBase<T, ForwardLinked>::PushFront(const ElemType& e)
	{
		NG_ASSERT_AND_ABORT(_isInit());

		// フリーノードより空きノードを取得
		NodeType* pNode = _popFreeNode();
		NG_ASSERT(pNode);
		if( ! pNode)
		{
			return;
		}

		// ユーズノードへ追加
		_createElem(pNode, &e);
		this->_insertNodeBehind(&m_useHead, pNode);
		m_size++;
	}

	template <typename T>
	void CFixedListBase<T, ForwardLinked>::PopFront()
	{
		NG_ASSERT_AND_ABORT(_isInit());
		if(Empty())
		{
			return;
		}
		NodeType* pNode = m_useHead.next;
		this->_removeNode(&m_useHead, pNode);
		m_size--;

		_destroyElem(pNode, &pNode->GetElem());
		this->_insertNodeBehind(&m_freeHead, pNode);
	}

	template <typename T>
	typename CFixedListBase<T, ForwardLinked>::NodeType* CFixedListBase<T, ForwardLinked>::Begin()
	{
		NG_ASSERT_AND_ABORT(_isInit());

		return m_useHead.next;
	}

	template <typename T>
	typename const CFixedListBase<T, ForwardLinked>::NodeType* CFixedListBase<T, ForwardLinked>::Begin() const
	{
		NG_ASSERT_AND_ABORT(_isInit());

		return m_useHead.next;
	}

	template <typename T>
	typename CFixedListBase<T, ForwardLinked>::NodeType* CFixedListBase<T, ForwardLinked>::End()
	{
		NG_ASSERT_AND_ABORT(_isInit());

		return &m_useHead;
	}

	template <typename T>
	typename const CFixedListBase<T, ForwardLinked>::NodeType* CFixedListBase<T, ForwardLinked>::End() const
	{
		NG_ASSERT_AND_ABORT(_isInit());

		return &m_useHead;
	}

	template <typename T>
	void CFixedListBase<T, ForwardLinked>::Insert(NodeType* pos, const ElemType& e)
	{
		NG_ASSERT_AND_ABORT(_isInit());

		// フリーノードより空きノードを取得
		NodeType* pNode = _popFreeNode();
		NG_ASSERT(pNode);
		if( ! pNode)
		{
			return;
		}

		// ユーズノードへ追加
		_createElem(pNode, &e);
		this->_insertNodeBehind(pos, pNode);
		m_size++;
	}

	template <typename T>
	void CFixedListBase<T, ForwardLinked>::Clear()
	{
		while( ! Empty())
		{
			PopFront();
		}
	}

	template <typename T>
	NG_INLINE bool CFixedListBase<T, ForwardLinked>::Empty() const
	{
		return (m_size == 0);
	}

	template <typename T>
	NG_INLINE u32 CFixedListBase<T, ForwardLinked>::Size() const
	{
		return m_size;
	}

	template <typename T>
	NG_INLINE u32 CFixedListBase<T, ForwardLinked>::MaxSize() const
	{
		return m_maxSize;
	}

	template <typename T>
	bool CFixedListBase<T, ForwardLinked>::Full() const
	{
		if(m_maxSize == 0)
		{
			return false;
		}
		return (Size() == m_maxSize);
	}

	template <typename T>
	NG_INLINE bool CFixedListBase<T, ForwardLinked>::_isInit() const
	{
		return (_getMemory() != nullptr);
	}

	template <typename T>
	NG_ERRCODE CFixedListBase<T, ForwardLinked>::_poolMemory(void* pMemory, size_type memSize)
	{
		return m_memPool.Pool(pMemory, memSize);
	}
	template <typename T>
	NG_ERRCODE CFixedListBase<T, ForwardLinked>::_poolMemory(IMemoryAllocator& alloc, size_type memSize)
	{
		return m_memPool.Pool(alloc, memSize);
	}

	template <typename T>
	NG_INLINE void CFixedListBase<T, ForwardLinked>::_initDummyNode()
	{
		m_freeHead.next = &m_freeHead;
		m_useHead.next = &m_useHead;
	}

	template <typename T>
	NG_INLINE typename CFixedListBase<T, ForwardLinked>::MyNodeType* CFixedListBase<T, ForwardLinked>::_createNode(void* p)
	{
		return NG_PLACEMENT_NEW(p) MyNodeType();
	}

	template <typename T>
	NG_INLINE void CFixedListBase<T, ForwardLinked>::_destroyNode(NodeType* pNode)
	{
		NG_PLACEMENT_DELETE(pNode, pNode);
	}

	template <typename T>
	NG_INLINE typename CFixedListBase<T, ForwardLinked>::NodeType* CFixedListBase<T, ForwardLinked>::_popFreeNode()
	{
		if(&m_freeHead == m_freeHead.next)
		{
			return nullptr;
		}

		// フリーノードより空きノードを取得
		NodeType* pNode = m_freeHead.next;
		this->_removeNode(&m_freeHead, pNode);
		return pNode;
	}

	template <typename T>
	NG_INLINE void CFixedListBase<T, ForwardLinked>::_createElem(NodeType* pNode, const ElemType* pElem)
	{
		ElemType* pDst = PointerOffset<ElemType*>(pNode, NG_SIZEOF(MyNodeType));
		NG_PLACEMENT_NEW(pDst) ElemType(*pElem);
	}

	template <typename T>
	NG_INLINE void CFixedListBase<T, ForwardLinked>::_destroyElem(NodeType* /*pNode*/, ElemType* pElem)
	{
		NG_PLACEMENT_DELETE(pElem, pElem);
	}

	template <typename T>
	NG_INLINE void* CFixedListBase<T, ForwardLinked>::_getMemory()
	{
		return m_memPool.GetMemory();
	}
	template <typename T>
	NG_INLINE const void* CFixedListBase<T, ForwardLinked>::_getMemory() const
	{
		return m_memPool.GetMemory();
	}

	template <typename T>
	NG_INLINE size_type CFixedListBase<T, ForwardLinked>::_getMemSize() const
	{
		return m_memPool.GetSize();
	}

	/*!
	* @brief					固定長リスト(単方向)
	* @tparam T					格納する要素の型
	* @tparam SIZE				格納する要素数。NG_UNSPECIFIED_SIZE で初期化時に要素数を指定する
	* @note						初期化時にバッファを指定する固定長のコンテナ
	*/
	template <typename T, u32 SIZE>
	class NG_DECL CFixedList<T, ForwardLinked, SIZE> : public CFixedListBase<T, ForwardLinked>
	{
	public:
		CFixedList();
		virtual ~CFixedList();

	private:
		typedef CFixedListBase<T, ForwardLinked> BaseType;	//!< 基底クラス

	private:
		char m_buffer[ SIZE * BaseType::BLOCK_SIZE ];	//!< バッファ
	};

	template <typename T, u32 SIZE>
	CFixedList<T, ForwardLinked, SIZE>::CFixedList()
	{
		size_type bufSize = NG_SIZEOF(m_buffer);

		NG_ERRCODE err = this->_poolMemory(m_buffer, bufSize);
		NG_ASSERT_AND_ABORT(NG_SUCCEEDED(err));

		err = this->_initialize(SIZE);
		NG_ASSERT_AND_ABORT(NG_SUCCEEDED(err));
	}

	template <typename T, u32 SIZE>
	CFixedList<T, ForwardLinked, SIZE>::~CFixedList()
	{
		this->_finalize();
	}

	/*!
	* @brief					固定長リスト(単方向)
	* @tparam T					格納する要素の型
	* @note						初期化時にバッファを指定する固定長のコンテナ
	*/
	template <typename T>
	class NG_DECL CFixedList<T, ForwardLinked, NG_UNSPECIFIED_SIZE> : public CFixedListBase<T, ForwardLinked>
	{
	public:
		CFixedList();
		virtual ~CFixedList();

		/*!
		* @brief					初期化
		* @param max				最大要素数
		* @param alloc				使用するメモリアロケータ
		* @return					NG エラーコード
		*/
		virtual NG_ERRCODE Initialize(u32 max, IMemoryAllocator& alloc);

		/*!
		* 終了処理
		*/
		virtual void Finalize();
	};

	template <typename T>
	CFixedList<T, ForwardLinked, NG_UNSPECIFIED_SIZE>::CFixedList()
	{
	}

	template <typename T>
	CFixedList<T, ForwardLinked, NG_UNSPECIFIED_SIZE>::~CFixedList()
	{
		Finalize();
	}

	template <typename T>
	NG_ERRCODE CFixedList<T, ForwardLinked, NG_UNSPECIFIED_SIZE>::Initialize(u32 max, IMemoryAllocator& alloc)
	{
		if(this->_isInit()) {
			return eNG_E_LEAK;
		}

		size_type reqMemSize = max * this->BLOCK_SIZE;

		if(alloc.GetMemSize() < reqMemSize)
		{
			return eNG_E_CAPACITYLACK;
		}

		// メモリ領域をプール
		{
			NG_ERRCODE err = this->_poolMemory(alloc, reqMemSize);
			if(NG_FAILED(err)) {
				return err;
			}
		}

		return this->_initialize(max);
	}

	template <typename T>
	void CFixedList<T, ForwardLinked, NG_UNSPECIFIED_SIZE>::Finalize()
	{
		this->_finalize();
	}

}	// namespace ng

#endif	// __NG_CORE_FIXED_LIST_FORWARD_H__
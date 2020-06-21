/*!
* @file		ngFixedQueue.h
* @brief	固定長キュー
* @date		2017-09-06
* @author	s.fukami
*/

#ifndef __NG_CORE_FIXED_QUEUE_H__
#define __NG_CORE_FIXED_QUEUE_H__

#include "ngQueue.h"
#include "ngLibCore/allocator/ngMemoryAllocator.h"
#include "ngLibCore/memory/pool/ngMemoryPool.h"

namespace ng
{
	/*!
	* @brief					固定長キュー ベースクラス
	* @tparam T					格納する要素の型
	* @note						初期化時にバッファを指定する固定長のコンテナ
	*							FIFO
	*/
	template <typename T>
	class NG_DECL CFixedQueueBase : public IQueue<T>
	{
	public:
		typedef T ElemType;		//!< 要素の型

	public:
		CFixedQueueBase();
		virtual ~CFixedQueueBase();

		/*! 末尾へ要素を追加する */
		virtual void PushBack(const ElemType& elem);

		/*! 先頭の要素を削除する */
		virtual void PopFront();

		/*! 先頭の要素を取得する */
		virtual ElemType& Front();

		/*! 先頭の要素を取得する */
		virtual const ElemType& Front() const;

		/*! 末尾の要素を取得する */
		virtual ElemType& Back();

		/*! 末尾の要素を取得する */
		virtual const ElemType& Back() const;

		/*! 指定位置の要素を取得する */
		virtual ElemType& operator[](u32 n);
		virtual const ElemType& operator[](u32 n) const;

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

		/*! 要素配列の先頭ポインタを取得 */
		virtual ElemType* ToArray();
		virtual const ElemType* ToArray() const;

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
		/*! 終端の位置を取得 */
		void* _getEndPos();
		const void* _getEndPos() const;

		/*! バッファ内部の位置を取得 */
		ElemType* _getInnerPos(const ElemType* pElem);
		const ElemType* _getInnerPos(const ElemType* pElem) const;

		/*! 要素を生成 */
		ElemType* _createElem(void* p, const ElemType& src);

		/*! 要素を破棄 */
		void _destroyElem(ElemType* pElem);

		/*! メモリ領域を取得 */
		void* _getMemory();
		const void* _getMemory() const;

		/*! メモリ領域のサイズを取得 */
		size_type _getMemSize() const;

	protected:
		static const size_type ELEM_SIZE = NG_SIZEOF(ElemType);	//!< 要素のサイズ

	private:
		CMemoryPool	m_memPool;	//!< メモリプール
		u32			m_maxSize;	//!< 最大サイズ（要素数）
		ElemType*	m_pFront;	//!< 先頭の要素
		ElemType*	m_pBack;	//!< 末尾の要素
	};

	template <typename T>
	CFixedQueueBase<T>::CFixedQueueBase()
		: m_maxSize(0)
		, m_pFront(nullptr)
		, m_pBack(nullptr)
	{
	}

	template <typename T>
	CFixedQueueBase<T>::~CFixedQueueBase()
	{
	}

	template <typename T>
	void CFixedQueueBase<T>::PushBack(const ElemType& elem)
	{
		NG_ASSERT_AND_ABORT(_isInit());

		ElemType* pNext = _getInnerPos(m_pBack + 1);
		NG_ASSERT(pNext != m_pFront);
		if(pNext == m_pFront)
		{
			return;
		}

		_createElem(m_pBack, elem);
		m_pBack = pNext;
	}

	template <typename T>
	void CFixedQueueBase<T>::PopFront()
	{
		NG_ASSERT_AND_ABORT(_isInit());
		if(Empty())
		{
			return;
		}

		_destroyElem(m_pFront);

		m_pFront++;
		m_pFront = _getInnerPos(m_pFront);
	}

	template <typename T>
	NG_INLINE typename CFixedQueueBase<T>::ElemType& CFixedQueueBase<T>::Front()
	{
		NG_ASSERT_AND_ABORT(_isInit());
		NG_ASSERT_AND_ABORT( ! Empty());

		return *m_pFront;
	}

	template <typename T>
	NG_INLINE typename const CFixedQueueBase<T>::ElemType& CFixedQueueBase<T>::Front() const
	{
		NG_ASSERT_AND_ABORT(_isInit());
		NG_ASSERT_AND_ABORT( ! Empty());

		return *m_pFront;
	}

	template <typename T>
	NG_INLINE typename CFixedQueueBase<T>::ElemType& CFixedQueueBase<T>::Back()
	{
		NG_ASSERT_AND_ABORT(_isInit());
		NG_ASSERT_AND_ABORT( ! Empty());

		return *(m_pBack - 1);
	}

	template <typename T>
	NG_INLINE typename const CFixedQueueBase<T>::ElemType& CFixedQueueBase<T>::Back() const
	{
		NG_ASSERT_AND_ABORT(_isInit());
		NG_ASSERT_AND_ABORT( ! Empty());

		return *(m_pBack - 1);
	}

	template <typename T>
	NG_INLINE typename CFixedQueueBase<T>::ElemType& CFixedQueueBase<T>::operator[](u32 n)
	{
		NG_ASSERT_AND_ABORT(_isInit());
		NG_ASSERT_AND_ABORT(n < Size());

		return *(m_pFront + n);
	}
	template <typename T>
	NG_INLINE typename const CFixedQueueBase<T>::ElemType& CFixedQueueBase<T>::operator[](u32 n) const
	{
		NG_ASSERT_AND_ABORT(_isInit());
		NG_ASSERT_AND_ABORT(n < Size());

		return *(m_pFront + n);
	}

	template <typename T>
	void CFixedQueueBase<T>::Clear()
	{
		while( ! Empty())
		{
			PopFront();
		}
	}

	template <typename T>
	NG_INLINE bool CFixedQueueBase<T>::Empty() const
	{
		return (m_pFront == m_pBack);
	}

	template <typename T>
	NG_INLINE u32 CFixedQueueBase<T>::Size() const
	{
		size_type diff = 0;
		if(m_pFront <= m_pBack) {
			diff = PointerDiff(m_pBack, m_pFront);
		} else {
			diff += PointerDiff(m_pBack, _getMemory());
			diff += PointerDiff(_getEndPos(), m_pFront);
		}
		return (u32)(diff / ELEM_SIZE);
	}

	template <typename T>
	NG_INLINE u32 CFixedQueueBase<T>::MaxSize() const
	{
		return m_maxSize;
	}

	template <typename T>
	NG_INLINE bool CFixedQueueBase<T>::Full() const
	{
		return (Size() == MaxSize());
	}

	template <typename T>
	NG_INLINE typename CFixedQueueBase<T>::ElemType* CFixedQueueBase<T>::ToArray()
	{
		return m_pFront;
	}
	template <typename T>
	NG_INLINE typename const CFixedQueueBase<T>::ElemType* CFixedQueueBase<T>::ToArray() const
	{
		return m_pFront;
	}

	template <typename T>
	NG_ERRCODE CFixedQueueBase<T>::_initialize(u32 max)
	{
		void* pMemory = m_memPool.GetMemory();
		size_type memSize = m_memPool.GetSize();

		NG_ASSERT(pMemory);
		if( ! pMemory)
		{
			return eNG_E_INVALIDMEMORY;
		}

		u32 capacity = (u32)(memSize / ELEM_SIZE);

		NG_ASSERT(max+1 <= capacity);
		if(max+1 > capacity)
		{
			return eNG_E_CAPACITYLACK;
		}

		m_maxSize = max;
		m_pBack = m_pFront = PointerCast<ElemType*>(pMemory);

		return eNG_S_OK;
	}

	template <typename T>
	void CFixedQueueBase<T>::_finalize()
	{
		Clear();

		m_maxSize = 0;
		m_pFront = nullptr;
		m_pBack = nullptr;
		m_memPool.Unpool();
	}

	template <typename T>
	NG_INLINE bool CFixedQueueBase<T>::_isInit() const
	{
		return (_getMemory() != nullptr);
	}

	template <typename T>
	NG_ERRCODE CFixedQueueBase<T>::_poolMemory(void* pMemory, size_type memSize)
	{
		return m_memPool.Pool(pMemory, memSize);
	}
	template <typename T>
	NG_ERRCODE CFixedQueueBase<T>::_poolMemory(IMemoryAllocator& alloc, size_type memSize)
	{
		return m_memPool.Pool(alloc, memSize);
	}

	template <typename T>
	NG_INLINE void* CFixedQueueBase<T>::_getEndPos()
	{
		return (PointerCast<ElemType*>(_getMemory()) + MaxSize() + 1);
	}
	template <typename T>
	NG_INLINE const void* CFixedQueueBase<T>::_getEndPos() const
	{
		return const_cast<CFixedQueueBase<T>*>(this)->_getEndPos();
	}

	template <typename T>
	NG_INLINE typename CFixedQueueBase<T>::ElemType* CFixedQueueBase<T>::_getInnerPos(const ElemType* pElem)
	{
		if(pElem >= _getEndPos())
		{
			return PointerCast<ElemType*>(_getMemory());
		}
		return const_cast<ElemType*>(pElem);
	}
	template <typename T>
	NG_INLINE const typename CFixedQueueBase<T>::ElemType* CFixedQueueBase<T>::_getInnerPos(const ElemType* pElem) const
	{
		return const_cast<CFixedQueueBase<T>*>(this)->_getInnerPos(pElem);
	}

	template <typename T>
	NG_INLINE typename CFixedQueueBase<T>::ElemType* CFixedQueueBase<T>::_createElem(void* p, const ElemType& src)
	{
		return NG_PLACEMENT_NEW(p) ElemType(src);
	}

	template <typename T>
	NG_INLINE void CFixedQueueBase<T>::_destroyElem(ElemType* pElem)
	{
		NG_PLACEMENT_DELETE(pElem, pElem);
	}

	template <typename T>
	NG_INLINE void* CFixedQueueBase<T>::_getMemory()
	{
		return m_memPool.GetMemory();
	}
	template <typename T>
	NG_INLINE const void* CFixedQueueBase<T>::_getMemory() const
	{
		return m_memPool.GetMemory();
	}

	template <typename T>
	NG_INLINE size_type CFixedQueueBase<T>::_getMemSize() const
	{
		return m_memPool.GetSize();
	}

	/*!
	* @brief					固定長キュー
	* @tparam T					格納する要素の型
	* @tparam SIZE				格納する要素数。NG_UNSPECIFIED_SIZE で初期化時に要素数を指定する
	* @note						初期化時にバッファを指定する固定長のコンテナ
	*							FIFO
	*/
	template <typename T, u32 SIZE = NG_UNSPECIFIED_SIZE>
	class NG_DECL CFixedQueue : public CFixedQueueBase<T>
	{
	public:
		CFixedQueue();
		virtual ~CFixedQueue();

	private:
		char m_buffer[ (SIZE+1) * CFixedQueueBase<T>::ELEM_SIZE ];	//!< バッファ
	};

	template <typename T, u32 SIZE>
	CFixedQueue<T, SIZE>::CFixedQueue()
	{
		size_type bufSize = NG_SIZEOF(m_buffer);

		NG_ERRCODE err = this->_poolMemory(m_buffer, bufSize);
		NG_ASSERT_AND_ABORT(NG_SUCCEEDED(err));

		err = this->_initialize(SIZE);
		NG_ASSERT_AND_ABORT(NG_SUCCEEDED(err));
	}

	template <typename T, u32 SIZE>
	CFixedQueue<T, SIZE>::~CFixedQueue()
	{
		this->_finalize();
	}

	/*!
	* @brief					固定長キュー
	* @tparam T					格納する要素の型
	* @note						初期化時にバッファを指定する固定長のコンテナ
	*							FIFO
	*/
	template <typename T>
	class NG_DECL CFixedQueue<T, NG_UNSPECIFIED_SIZE> : public CFixedQueueBase<T>
	{
	public:
		CFixedQueue();
		virtual ~CFixedQueue();

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
		void Finalize();

	private:
	};

	template<typename T>
	CFixedQueue<T, NG_UNSPECIFIED_SIZE>::CFixedQueue()
	{
	}

	template<typename T>
	CFixedQueue<T, NG_UNSPECIFIED_SIZE>::~CFixedQueue()
	{
		Finalize();
	}

	template<typename T>
	NG_ERRCODE CFixedQueue<T, NG_UNSPECIFIED_SIZE>::Initialize(u32 max, IMemoryAllocator& alloc)
	{
		if(this->_isInit()) {
			return eNG_E_LEAK;
		}

		size_type reqMemSize = (max+1) * this->ELEM_SIZE;
		
		if(alloc.GetMemSize() < reqMemSize)
		{
			return eNG_E_CAPACITYLACK;
		}

		NG_ERRCODE err = eNG_E_FAIL;

		// メモリ領域をプール
		if(NG_FAILED(err = this->_poolMemory(alloc, reqMemSize))) {
			return err;
		}

		// 初期化
		if(NG_FAILED(err = this->_initialize(max))) {
			Finalize();
		}

		return err;
	}

	template<typename T>
	void CFixedQueue<T, NG_UNSPECIFIED_SIZE>::Finalize()
	{
		this->_finalize();
	}

}	// namespace ng

#endif	// __NG_CORE_FIXED_QUEUE_H__
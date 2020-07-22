/*!
* @file		ngFixedStack.h
* @brief	固定長スタック
* @date		2018-12-06
* @author	s.fukami
*/

#ifndef __NG_CORE_FIXED_STACK_H__
#define __NG_CORE_FIXED_STACK_H__

#include "ngLibCore/common/ngCommon.h"
#include "ngLibCore/allocator/ngMemoryAllocator.h"
#include "ngLibCore/memory/pool/ngMemoryPool.h"
#include "ngStack.h"

namespace ng
{
	/*!
	* @brief					固定長スタック ベースクラス
	* @tparam T					格納する要素の型
	* @note						初期化時にバッファを指定する固定長のコンテナ
	*							LIFO
	*/
	template <typename T>
	class NG_DECL CFixedStackBase : public IStack<T>
	{
	public:
		typedef T ElemType;		//!< 要素の型

	public:
		CFixedStackBase();
		virtual ~CFixedStackBase();

		/*! 先頭へ要素を追加する */
		virtual void Push(const ElemType& elem);

		/*! 先頭の要素を削除する */
		virtual void Pop();

		/*! 先頭の要素を取得する */
		virtual ElemType& Top();

		/*! 先頭の要素を取得する */
		virtual const ElemType& Top() const;

		/*! 指定インデックスの要素を取得する */
		virtual ElemType& operator[](int index);

		/*! 指定インデックスの要素を取得する */
		virtual const ElemType& operator[](int index) const;

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
		/*! 指定の位置を取得 */
		ElemType* _getElem(u32 pos);
		const ElemType* _getElem(u32 pos) const;

		/*! 終端の位置を取得 */
		void* _getEndPos();

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
		ElemType*	m_pTop;		//!< 先頭の要素
	};

	template <typename T>
	CFixedStackBase<T>::CFixedStackBase()
		: m_maxSize(0)
		, m_pTop(nullptr)
	{
	}

	template <typename T>
	CFixedStackBase<T>::~CFixedStackBase()
	{
	}

	template <typename T>
	void CFixedStackBase<T>::Push(const ElemType& elem)
	{
		NG_ASSERT_AND_ABORT(_isInit());
		NG_ASSERT( ! Full());
		if(Full()) {
			return;
		}

		m_pTop = _createElem(m_pTop, elem);
		m_pTop++;
	}

	template <typename T>
	void CFixedStackBase<T>::Pop()
	{
		NG_ASSERT_AND_ABORT(_isInit());
		NG_ASSERT( ! Empty());
		if(Empty()) {
			return;
		}

		_destroyElem(m_pTop-1);
		m_pTop--;
	}

	template <typename T>
	typename CFixedStackBase<T>::ElemType& CFixedStackBase<T>::Top()
	{
		NG_ASSERT_AND_ABORT(_isInit());
		NG_ASSERT_AND_ABORT( ! Empty());

		return *(m_pTop-1);
	}

	template <typename T>
	typename const CFixedStackBase<T>::ElemType& CFixedStackBase<T>::Top() const
	{
		NG_ASSERT_AND_ABORT(_isInit());
		NG_ASSERT_AND_ABORT( ! Empty());

		return *(m_pTop-1);
	}

	template <typename T>
	typename CFixedStackBase<T>::ElemType& CFixedStackBase<T>::operator[](int index)
	{
		NG_ASSERT_AND_ABORT(_isInit());
		NG_ASSERT_AND_ABORT( ! Empty());

		return *_getElem(index);
	}

	template <typename T>
	typename const CFixedStackBase<T>::ElemType& CFixedStackBase<T>::operator[](int index) const
	{
		NG_ASSERT_AND_ABORT(_isInit());
		NG_ASSERT_AND_ABORT( ! Empty());

		return *_getElem(index);
	}

	template <typename T>
	void CFixedStackBase<T>::Clear()
	{
		while( ! Empty())
		{
			Pop();
		}
	}

	template <typename T>
	NG_INLINE bool CFixedStackBase<T>::Empty() const
	{
		return (m_pTop == _getMemory());
	}

	template <typename T>
	NG_INLINE typename u32 CFixedStackBase<T>::Size() const
	{
		return (u32)(PointerDiff(m_pTop, this->_getMemory()) / (intptr_t)this->ELEM_SIZE);
	}

	template <typename T>
	NG_INLINE typename u32 CFixedStackBase<T>::MaxSize() const
	{
		return m_maxSize;
	}

	template <typename T>
	NG_INLINE bool CFixedStackBase<T>::Full() const
	{
		if(m_maxSize == 0)
		{
			return false;
		}
		return (Size() == m_maxSize);
	}

	template <typename T>
	NG_ERRCODE CFixedStackBase<T>::_initialize(u32 max)
	{
		void* pMemory = m_memPool.GetMemory();
		size_type memSize = m_memPool.GetSize();

		NG_ASSERT_NOT_NULL(pMemory);
		if( ! pMemory)
		{
			return eNG_E_INVALIDMEMORY;
		}

		u32 capacity = (u32)(memSize / ELEM_SIZE);

		NG_ASSERT(max <= capacity);
		if(max > capacity)
		{
			return eNG_E_CAPACITYLACK;
		}

		m_maxSize = max;
		m_pTop = PointerCast<ElemType*>(pMemory);

		return eNG_S_OK;
	}

	template <typename T>
	void CFixedStackBase<T>::_finalize()
	{
		Clear();
		
		m_maxSize = 0;
		m_pTop = nullptr;
		m_memPool.Unpool();
	}

	template <typename T>
	NG_INLINE bool CFixedStackBase<T>::_isInit() const
	{
		return (_getMemory() != nullptr);
	}

	template <typename T>
	NG_ERRCODE CFixedStackBase<T>::_poolMemory(void* pMemory, size_type memSize)
	{
		return m_memPool.Pool(pMemory, memSize);
	}
	template <typename T>
	NG_ERRCODE CFixedStackBase<T>::_poolMemory(IMemoryAllocator& alloc, size_type memSize)
	{
		return m_memPool.Pool(alloc, memSize);
	}

	template <typename T>
	typename CFixedStackBase<T>::ElemType* CFixedStackBase<T>::_getElem(u32 pos)
	{
		bool isOutOfRange = (pos >= m_maxSize);
		NG_ASSERT( ! isOutOfRange);
		if(isOutOfRange) {
			return nullptr;
		}

		ElemType* pElem = PointerCast<ElemType*>(_getMemory());
		return (pElem + pos);
	}
	template <typename T>
	typename const CFixedStackBase<T>::ElemType* CFixedStackBase<T>::_getElem(u32 pos) const
	{
		return const_cast<CFixedStackBase<T>*>(this)->_getElem(pos);
	}

	template <typename T>
	NG_INLINE void* CFixedStackBase<T>::_getEndPos()
	{
		return (PointerCast<ElemType*>(_getMemory()) + m_maxSize);
	}

	template <typename T>
	NG_INLINE typename CFixedStackBase<T>::ElemType* CFixedStackBase<T>::_createElem(void* p, const ElemType& src)
	{
		return NG_PLACEMENT_NEW(p) ElemType(src);
	}

	template <typename T>
	NG_INLINE void CFixedStackBase<T>::_destroyElem(ElemType* pElem)
	{
		NG_PLACEMENT_DELETE(pElem, pElem);
	}

	template <typename T>
	NG_INLINE void* CFixedStackBase<T>::_getMemory()
	{
		return m_memPool.GetMemory();
	}
	template <typename T>
	NG_INLINE const void* CFixedStackBase<T>::_getMemory() const
	{
		return m_memPool.GetMemory();
	}

	template <typename T>
	NG_INLINE size_type CFixedStackBase<T>::_getMemSize() const
	{
		return m_memPool.GetSize();
	}

	/*!
	* @brief					固定長スタック
	* @tparam T					格納する要素の型
	* @tparam SIZE				格納する要素数。NG_UNSPECIFIED_SIZE で初期化時に要素数を指定する
	* @note						初期化時にバッファを指定する固定長のコンテナ
	*							LIFO
	*/
	template <typename T, u32 SIZE = NG_UNSPECIFIED_SIZE>
	class NG_DECL CFixedStack : public CFixedStackBase<T>
	{
	public:
		CFixedStack();
		~CFixedStack();

	private:
		typedef CFixedStackBase<T> BaseType;	//!< 基底クラス

	private:
		char m_buffer[ SIZE * BaseType::ELEM_SIZE ];	//!< バッファ
	};

	template <typename T, u32 SIZE>
	CFixedStack<T, SIZE>::CFixedStack()
	{
		size_type bufSize = NG_SIZEOF(m_buffer);

		NG_ERRCODE err = this->_poolMemory(m_buffer, bufSize);
		NG_ASSERT_AND_ABORT(NG_SUCCEEDED(err));

		err = this->_initialize(SIZE);
		NG_ASSERT_AND_ABORT(NG_SUCCEEDED(err));
	}

	template <typename T, u32 SIZE>
	CFixedStack<T, SIZE>::~CFixedStack()
	{
		this->_finalize();
	}

	/*!
	* @brief					固定長スタック
	* @tparam T					格納する要素の型
	* @note						初期化時にバッファを指定する固定長のコンテナ
	*							LIFO
	*/
	template <typename T>
	class NG_DECL CFixedStack<T, NG_UNSPECIFIED_SIZE> : public CFixedStackBase<T>
	{
	public:
		CFixedStack();
		~CFixedStack();

		/*!
		* @brief					初期化
		* @param alloc				使用するメモリアロケータ
		* @param max				最大要素数
		* @return					NG エラーコード
		*/
		NG_ERRCODE Initialize(IMemoryAllocator& alloc, u32 max);

		/*!
		* @brief					終了処理
		*/
		void Finalize();
	};

	template <typename T>
	CFixedStack<T, NG_UNSPECIFIED_SIZE>::CFixedStack()
	{
	}

	template <typename T>
	CFixedStack<T, NG_UNSPECIFIED_SIZE>::~CFixedStack()
	{
		Finalize();
	}

	template <typename T>
	NG_ERRCODE CFixedStack<T, NG_UNSPECIFIED_SIZE>::Initialize(IMemoryAllocator& alloc, u32 max)
	{
		if(this->_isInit()) {
			return eNG_E_LEAK;
		}

		size_type reqMemSize = max * this->ELEM_SIZE;

		if(alloc.GetMemSize() < reqMemSize)
		{
			return eNG_E_CAPACITYLACK;
		}

		NG_ERRCODE err = NG_ERRCODE_DEFAULT;

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

	template <typename T>
	void CFixedStack<T, NG_UNSPECIFIED_SIZE>::Finalize()
	{
		this->_finalize();
	}

}	// namespace ng

#endif	// __NG_CORE_FIXED_STACK_H__
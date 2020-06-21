/*!
* @file		ngFixedArray.h
* @brief	固定長配列
* @date		2019-02-06
* @author	s.fukami
*/

#ifndef __NG_CORE_FIXED_ARRAY_H__
#define __NG_CORE_FIXED_ARRAY_H__

#include "ngArray.h"
#include "ngLibCore/allocator/ngMemoryAllocator.h"
#include "ngLibCore/memory/pool/ngMemoryPool.h"

namespace ng
{
	/*!
	* @brief					固定長配列 ベースクラス
	* @tparam T					格納する要素の型
	* @note						初期化時にバッファを指定する固定長のコンテナ
	*							FIFO
	*/
	template <class T>
	class NG_DECL CFixedArrayBase : public IArray<T>
	{
	public:
		typedef T ElemType;		//!< 要素の型
		
	public:
		CFixedArrayBase();
		virtual ~CFixedArrayBase();

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

		/*! 要素数取得 */
		virtual u32 Size() const;

		/*! 要素配列の先頭ポインタを取得 */
		virtual ElemType* ToArray();
		virtual const ElemType* ToArray() const;

	protected:
		/*! 初期化 */
		NG_ERRCODE _initialize(u32 size);

		/*! 終了処理 */
		void _finalize();

		/*! 初期化済みかを調べる */
		bool _isInit() const;

		/*! メモリをプールする */
		NG_ERRCODE _poolMemory(void* pMemory, size_type memSize);
		NG_ERRCODE _poolMemory(IMemoryAllocator& alloc, size_type memSize);

	private:
		/*! 要素を生成 */
		ElemType* _createElem(void* p);

		/*! 要素を破棄 */
		void _destroyElem(ElemType* pElem);

		/*! メモリ領域を取得 */
		void* _getMemory();
		const void* _getMemory() const;

		/*! メモリ領域のサイズを取得 */
		size_type _getMemSize() const;

	public:
		static const size_type ELEM_SIZE = NG_SIZEOF(ElemType);	//!< 要素のサイズ

	private:
		CMemoryPool	m_memPool;	//!< メモリプール
		u32			m_size;		//!< 最大サイズ（要素数）
		ElemType*	m_pFront;	//!< 先頭の要素
	};

	template <typename T>
	CFixedArrayBase<T>::CFixedArrayBase()
		: m_size(0)
		, m_pFront(nullptr)
	{
	}

	template <typename T>
	CFixedArrayBase<T>::~CFixedArrayBase()
	{
	}

	template <typename T>
	NG_INLINE typename CFixedArrayBase<T>::ElemType& CFixedArrayBase<T>::Front()
	{
		NG_ASSERT_AND_ABORT(_isInit());

		return *m_pFront;
	}

	template <typename T>
	NG_INLINE typename const CFixedArrayBase<T>::ElemType& CFixedArrayBase<T>::Front() const
	{
		return const_cast<CFixedArrayBase<T>*>(this)->Front();
	}

	template <typename T>
	NG_INLINE typename CFixedArrayBase<T>::ElemType& CFixedArrayBase<T>::Back()
	{
		NG_ASSERT_AND_ABORT(_isInit());

		return *(m_pFront + (m_size-1));
	}

	template <typename T>
	NG_INLINE typename const CFixedArrayBase<T>::ElemType& CFixedArrayBase<T>::Back() const
	{
		return const_cast<CFixedArrayBase<T>*>(this)->Back();
	}

	template <typename T>
	NG_INLINE typename CFixedArrayBase<T>::ElemType& CFixedArrayBase<T>::operator[](u32 n)
	{
		NG_ASSERT_AND_ABORT(_isInit());
		NG_ASSERT_AND_ABORT(n < Size());

		return *(m_pFront + n);
	}
	template <typename T>
	NG_INLINE typename const CFixedArrayBase<T>::ElemType& CFixedArrayBase<T>::operator[](u32 n) const
	{
		return const_cast<CFixedArrayBase<T>*>(this)->operator[](n);
	}

	template <typename T>
	NG_INLINE u32 CFixedArrayBase<T>::Size() const
	{
		return m_size;
	}

	template <typename T>
	NG_INLINE typename CFixedArrayBase<T>::ElemType* CFixedArrayBase<T>::ToArray()
	{
		return m_pFront;
	}
	template <typename T>
	NG_INLINE typename const CFixedArrayBase<T>::ElemType* CFixedArrayBase<T>::ToArray() const
	{
		return m_pFront;
	}

	template <typename T>
	NG_ERRCODE CFixedArrayBase<T>::_initialize(u32 size)
	{
		void* pMemory = m_memPool.GetMemory();
		size_type memSize = m_memPool.GetSize();

		NG_ASSERT(pMemory);
		if(!pMemory)
		{
			return eNG_E_INVALIDMEMORY;
		}

		u32 capacity = (u32)(memSize / ELEM_SIZE);

		NG_ASSERT(size <= capacity);
		if(size > capacity)
		{
			return eNG_E_CAPACITYLACK;
		}

		m_size = size;
		m_pFront = PointerCast<ElemType*>(pMemory);

		for(u32 i = 0; i < m_size; i++)
		{
			_createElem(m_pFront + i);
		}

		return eNG_S_OK;
	}

	template <typename T>
	void CFixedArrayBase<T>::_finalize()
	{
		for(u32 i = 0; i < m_size; i++)
		{
			_destroyElem(m_pFront + i);
		}

		m_size = 0;
		m_pFront = nullptr;
		m_memPool.Unpool();
	}

	template <typename T>
	NG_INLINE bool CFixedArrayBase<T>::_isInit() const
	{
		return (_getMemory() != nullptr);
	}

	template <typename T>
	NG_ERRCODE CFixedArrayBase<T>::_poolMemory(void* pMemory, size_type memSize)
	{
		return m_memPool.Pool(pMemory, memSize);
	}
	template <typename T>
	NG_ERRCODE CFixedArrayBase<T>::_poolMemory(IMemoryAllocator& alloc, size_type memSize)
	{
		return m_memPool.Pool(alloc, memSize);
	}

	template <typename T>
	NG_INLINE typename CFixedArrayBase<T>::ElemType* CFixedArrayBase<T>::_createElem(void* p)
	{
		return NG_PLACEMENT_NEW(p) ElemType();
	}

	template <typename T>
	NG_INLINE void CFixedArrayBase<T>::_destroyElem(ElemType* pElem)
	{
		NG_PLACEMENT_DELETE(pElem, pElem);
	}

	template <typename T>
	NG_INLINE void* CFixedArrayBase<T>::_getMemory()
	{
		return m_memPool.GetMemory();
	}
	template <typename T>
	NG_INLINE const void* CFixedArrayBase<T>::_getMemory() const
	{
		return m_memPool.GetMemory();
	}

	template <typename T>
	NG_INLINE size_type CFixedArrayBase<T>::_getMemSize() const
	{
		return m_memPool.GetSize();
	}

	/*!
	* @brief					固定長配列
	* @tparam T					格納する要素の型
	* @tparam SIZE				格納する要素数。NG_UNSPECIFIED_SIZE で初期化時に要素数を指定する
	* @note						初期化時にバッファを指定する固定長のコンテナ
	*							FIFO
	*/
	template <typename T, u32 SIZE = NG_UNSPECIFIED_SIZE>
	class NG_DECL CFixedArray : public CFixedArrayBase<T>
	{
	public:
		CFixedArray();
		virtual ~CFixedArray();

	private:
		typedef CFixedArrayBase<T> BaseType;	//!< 基底クラス

	private:
		char m_buffer[ SIZE * BaseType::ELEM_SIZE ];	//!< バッファ
	};

	template <typename T, u32 SIZE>
	CFixedArray<T, SIZE>::CFixedArray()
	{
		size_type bufSize = NG_SIZEOF(m_buffer);

		NG_ERRCODE err = this->_poolMemory(m_buffer, bufSize);
		NG_ASSERT_AND_ABORT(NG_SUCCEEDED(err));

		err = this->_initialize(SIZE);
		NG_ASSERT_AND_ABORT(NG_SUCCEEDED(err));
	}

	template <typename T, u32 SIZE>
	CFixedArray<T, SIZE>::~CFixedArray()
	{
		this->_finalize();
	}

	/*!
	* @brief					固定長配列
	* @tparam T					格納する要素の型
	* @note						初期化時にバッファを指定する固定長のコンテナ
	*							FIFO
	*/
	template <typename T>
	class NG_DECL CFixedArray<T, NG_UNSPECIFIED_SIZE> : public CFixedArrayBase<T>
	{
	public:
		CFixedArray();
		virtual ~CFixedArray();

		/*!
		* @brief					初期化
		* @param size				要素数
		* @param alloc				使用するメモリアロケータ
		* @return					NG エラーコード
		*/
		virtual NG_ERRCODE Initialize(u32 size, IMemoryAllocator& alloc);

		/*!
		* 終了処理
		*/
		void Finalize();

	private:
	};

	template<typename T>
	CFixedArray<T, NG_UNSPECIFIED_SIZE>::CFixedArray()
	{
	}

	template<typename T>
	CFixedArray<T, NG_UNSPECIFIED_SIZE>::~CFixedArray()
	{
		Finalize();
	}

	template<typename T>
	NG_ERRCODE CFixedArray<T, NG_UNSPECIFIED_SIZE>::Initialize(u32 size, IMemoryAllocator& alloc)
	{
		if(this->_isInit()) {
			return eNG_E_LEAK;
		}

		size_type reqMemSize = size * this->ELEM_SIZE;
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

		return this->_initialize(size);
	}

	template<typename T>
	void CFixedArray<T, NG_UNSPECIFIED_SIZE>::Finalize()
	{
		this->_finalize();
	}

}	// namespace ng

#endif	// __NG_CORE_FIXED_ARRAY_H__
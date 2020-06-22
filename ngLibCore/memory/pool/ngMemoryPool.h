/*!
* @file		ngMemoryPool.h
* @brief	メモリプール
* @date		2015-12-19
* @author	s.fukami
*/

#ifndef __NG_CORE_MEMORY_POOL_H__
#define __NG_CORE_MEMORY_POOL_H__

namespace ng
{
	class IMemoryAllocator;
}

namespace ng
{
	/*!
	* @brief					メモリプール
	*/
	class NG_DECL CMemoryPool
	{
	public:
		CMemoryPool();
		virtual ~CMemoryPool();

		/*!
		* @brief					メモリ領域をプール
		* @param pMemory			使用するメモリ領域へのポインタ
		* @param size				メモリ領域のサイズ
		* @return					NG エラーコード
		*/
		virtual NG_ERRCODE Pool(
			void* pMemory,
			size_type size
			);

		/*!
		* @brief					メモリ領域をプール
		* @param alloc				使用するメモリアロケータ
		* @param size				メモリ領域のサイズ
		* @return					NG エラーコード
		*/
		virtual NG_ERRCODE Pool(
			IMemoryAllocator& alloc,
			size_type size
			);

		/*!
		* @brief					プールされたメモリ領域を解放する
		*/
		virtual void Unpool();

		/*! メモリ領域取得 */
		virtual void* GetMemory();
		virtual const void* GetMemory() const;

		/*! メモリ領域のサイズを取得 */
		virtual size_type GetSize() const;

		/*! メモリ領域がプールされているか */
		virtual bool IsPool() const;

	private:
		void*		m_pMemory;	//!< メモリ領域
		size_type	m_size;		//!< メモリ領域サイズ
		IMemoryAllocator* m_pAlloc;	//!< 使用するメモリアロケータ
	};

}	// namespace ng

#endif	//__NG_CORE_MEMORY_POOL_H__
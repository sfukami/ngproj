/*!
* @file		ngRootMemoryPool.h
* @brief	ルートメモリプール
* @date		2019-01-10
* @author	s.fukami
*/

#ifndef __NG_ROOT_MEMORY_POOL_H__
#define __NG_ROOT_MEMORY_POOL_H__

#include "ngLibCore/memory/pool/ngMemoryPool.h"
#include "ngLibCore/allocator/ngDefaultAllocator.h"

namespace ng
{
	/*!
	* @brief					ルートメモリプール
	*/
	class NG_DECL CRootMemoryPool
	{
	public:
		CRootMemoryPool();
		~CRootMemoryPool();

		/*!
		* @brief					初期化
		* @param size				メモリサイズ
		* @return					NG エラーコード
		*/
		NG_ERRCODE Initialize(size_type size);

		/*!
		* @brief					終了処理
		*/
		void Finalize();

		/*!
		* @brief					メモリプール取得
		*/
		CMemoryPool& GetMemoryPool();
		const CMemoryPool& GetMemoryPool() const;

	private:
		CDefaultAllocator m_rootAlloc;	//!< ルートアロケータ
		CMemoryPool m_memPool;		//!< メモリプール
	};

}	// namespace ng

#endif	// __NG_ROOT_MEMORY_POOL_H__
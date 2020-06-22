/*!
* @file		ngMemoryManager.h
* @brief	メモリ管理
* @date		2019-03-10
* @author	s.fukami
*/

#ifndef __NG_CORE_MEMORY_MANAGER_H__
#define __NG_CORE_MEMORY_MANAGER_H__

#include "ngLibCore/allocator/ngDefaultAllocator.h"
#include "ngLibCore/container/array/ngFixedArray.h"

namespace ng
{
	class CMemoryPool;
	class IMemoryAllocator;
}

namespace ng
{
	/*!
	* @brief					メモリ管理
	*/
	class NG_DECL CMemoryManager
	{
	public:
		CMemoryManager();
		virtual ~CMemoryManager();

		/*!
		* @brief					初期化
		* @param memPool			メモリ割り当てに用いるメモリプール
		* @param allocNumMax		メモリアロケータ最大数
		*/
		NG_ERRCODE Initialize(
			CMemoryPool& memPool,
			u32 allocNumMax
			);

		/*!
		* @brief					終了処理
		*/
		void Finalize();

		/*!
		* @brief					メモリアロケータ生成・登録
		* @tparam T					生成するメモリアロケータ
		* @param index				メモリアロケータのインデックス
		* @param name				メモリアロケータの名称
		* @param size				使用するメモリ領域サイズ（バイト）
		*/
		template <class T>
		T* CreateAndRegisterAllocator(
			u32 index
			, const char* name
			, size_type size
			);

		/*!
		* @brief					メモリアロケータ削除
		* @param index				メモリアロケータのインデックス
		*/
		void DeleteAllocator(u32 index);

		/*!
		* @brief					全メモリアロケータ削除
		*/
		void ClearAllocator();

		/*!
		* @brief					メモリアロケータ取得
		* @param index				メモリアロケータのインデックス
		* @return					メモリアロケータ
		*/
		IMemoryAllocator* GetAllocator(u32 index);

		/*! 初期化済みか */
		bool IsInit() const;

	private:
		/*!
		* @brief					メモリアロケータ登録
		* @param index				メモリアロケータのインデックス
		* @param pAlloc				登録するメモリアロケータ
		*/
		void _registerAllocator(u32 index, IMemoryAllocator* pAlloc);
		
	private:
		CMemoryPool* m_pMemPool;	//!< メモリプール
		CDefaultAllocator m_memAlloc;	//!< メモリアロケータ
		CFixedArray<IMemoryAllocator*> m_allocArr;	//!< 追加のメモリアロケータ格納先配列
	};

	template <class T>
	T* CMemoryManager::CreateAndRegisterAllocator(
		u32 index
		, const char* name
		, size_type size
		)
	{
		T* pAlloc = NG_NEW(m_memAlloc) T();
		pAlloc->Initialize(
			name, 
			m_memAlloc,
			size
			);
		_registerAllocator(index, pAlloc);

		return pAlloc;
	}

}	// namespace ng

#endif	// __NG_CORE_MEMORY_MANAGER_H__
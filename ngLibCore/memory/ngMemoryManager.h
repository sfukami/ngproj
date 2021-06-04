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
#include "ngLibCore/memory/pointer/ngSharedPtr.h"
#include "ngLibCore/memory/pointer/ngWeakPtr.h"

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
		~CMemoryManager();

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
		* @param isPrintLogEnable	ログ出力が有効か
		* @return					成否
		*/
		template <class T>
		bool CreateAndRegisterAllocator(
			u32 index
			, const char* name
			, size_type size
		#if defined(NG_CONFIG_MEMORY_PRINT_LOG)
			, bool isPrintLogEnable = false
		#endif
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
		CWeakPtr<IMemoryAllocator> GetAllocator(u32 index);

		/*! 初期化済みか */
		bool IsInit() const;

	private:
		/*!
		* @brief					メモリアロケータ登録
		* @param index				メモリアロケータのインデックス
		* @param pAlloc				登録するメモリアロケータ
		*/
		void _registerAllocator(u32 index, CSharedPtr<IMemoryAllocator>& allocPtr);
		
	private:
		CMemoryPool* m_pMemPool;	//!< メモリプール
		CDefaultAllocator m_memAlloc;	//!< メモリアロケータ
		CFixedArray<CSharedPtr<IMemoryAllocator>> m_allocArr;	//!< 追加のメモリアロケータ格納先配列
	};

	template <class T>
	bool CMemoryManager::CreateAndRegisterAllocator(
		u32 index
		, const char* name
		, size_type size
	#if defined(NG_CONFIG_MEMORY_PRINT_LOG)
		, bool isPrintLogEnable
	#endif
		)
	{
		NG_ASSERT(IsInit());

		CSharedPtr<IMemoryAllocator> allocPtr = NG_MAKE_SHARED_PTR_CTOR(IMemoryAllocator, m_memAlloc, T);

		NG_ERRCODE err = NG_ERRCODE_DEFAULT;
		if(NG_FAILED(err = allocPtr->Initialize(
			name, 
			m_memAlloc,
			size
			))) {
			NG_ERRLOG_C("MemoryManager", err, "メモリアロケータの初期化に失敗しました.");
			return false;
		}

	#if defined(NG_CONFIG_MEMORY_PRINT_LOG)
		allocPtr->SetPrintLogEnable(isPrintLogEnable);
	#endif

		_registerAllocator(index, allocPtr);

		return true;
	}

}	// namespace ng

#endif	// __NG_CORE_MEMORY_MANAGER_H__
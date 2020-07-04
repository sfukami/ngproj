/*!
* @file		ngStackAllocator.h
* @brief	スタックアロケータ
* @date		2017-02-26
* @author	s.fukami
*/

#ifndef __NG_CORE_STACK_ALLOCATOR_H__
#define __NG_CORE_STACK_ALLOCATOR_H__

#include "ngMemoryAllocator.h"
#include "ngLibCore/memory/pool/ngMemoryPool.h"

namespace ng
{
	/*!
	* @brief					スタックアロケータ
	*/
	class NG_DECL CStackAllocator : public IMemoryAllocator
	{
	public:
		CStackAllocator();
		~CStackAllocator();

		/*!
		* @brief					初期化
		* @param name				メモリアロケータの名称
		* @param alloc				使用するメモリアロケータ
		* @param size				使用するメモリ領域サイズ（バイト）
		* @return					NG エラーコード
		*/
		NG_ERRCODE Initialize(
			const char* name
			, IMemoryAllocator& alloc
			, size_type size
			);

		/*!
		* @brief					初期化
		* @param name				メモリアロケータの名称
		* @param pool				使用するメモリプール
		* @param size				使用するメモリ領域サイズ（バイト）
		* @return					NG エラーコード
		*/
		NG_ERRCODE Initialize(
			const char* name
			, CMemoryPool& pool
			, size_type size
			);

		/*!
		* @brief					終了処理
		*/
		void Finalize();

		/*!
		* @brief					メモリ領域を割り当て、取得する
		* @param size				割り当てるメモリ領域サイズ（バイト）
		* @param alignment			アライメント（バイト）
		* @param src				割り当て元の情報（NG_CONF_MEMORY_DBGINFO定義時のみ）
		* @return					割り当てたメモリ領域へのポインタ
		* @attention				アライメントは無効
		*/
		void* Allocate(
			size_type size
			, u32 alignment
		#if defined(NG_CONFIG_MEMORY_DBGINFO)
			, const char* src
		#endif
			);

		/*!
		* @brief					割り当て済みのメモリ領域を解放する
		* @param p					解放するメモリ領域へのポインタ
		* @attention				オブジェクトの解放処理は行わないので注意
		*/
		void Free(
			void* p
			);

		/*!
		* @brief					全メモリ解放
		* @attention				個々のオブジェクトの解放処理は行わないので注意
		*/
		void Clear();

		/*!
		* @brief					初期化済みか
		*/
		bool IsInit() const;

		/*!
		* @brief					メモリ領域を取得する
		*/
		void* GetMemory();
		const void* GetMemory() const;

		/*!
		* @brief					メモリ領域のサイズを取得する
		*/
		size_type GetMemSize() const;

		/*!
		* @brief					割り当て可能な最大サイズを取得する
		*/
		size_type GetAllocatableMaximum() const;

		/*!
		* @brief					名称取得
		*/
		const char* GetName() const;

	private:
		/*! 初期化 */
		NG_ERRCODE _initialize(const char* name, void* pMemory, size_type size);

	private:
		static const u32 NAME_LENGTH = 127;		//!< 名称の長さ

	private:
		CMemoryPool	m_memPool;		//!< メモリプール
		char* m_pBeg;	//!< 先頭ポインタ
		char* m_pEnd;	//!< 末尾ポインタ
		char* m_pPos;	//!< マーカーの位置
		char m_name[ NAME_LENGTH+1 ];	//!< 名称
		IMemoryAllocator*	m_pAlloc;	//!< 利用するメモリアロケータ
	};

}	// namespace ng

#endif	// __NG_CORE_STACK_ALLOCATOR_H__
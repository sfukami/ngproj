/*!
* @file		ngDefaultAllocator.h
* @brief	メモリアロケータ デフォルトアロケータ
* @date		2017-08-28
* @author	s.fukami
*/

#ifndef __NG_CORE_DEFAULT_ALLOCATOR_H__
#define __NG_CORE_DEFAULT_ALLOCATOR_H__

#include "ngMemoryAllocator.h"

namespace ng
{
	class IMemoryPool;
}

namespace ng
{
	/*!
	* @brief					メモリアロケータ デフォルトアロケータ
	* @note						malloc(), Free() 使用
	*/
	class NG_DECL CDefaultAllocator : public IMemoryAllocator
	{
	public:
		CDefaultAllocator();
		~CDefaultAllocator();

		/*!
		* @brief					初期化
		* @param name				メモリアロケータの名称
		* @return					NG エラーコード
		*/
		NG_ERRCODE Initialize(
			const char* name
			);

		/*!
		* @brief					初期化
		* @param name				メモリアロケータの名称
		* @param alloc				未使用
		* @param size				未使用
		* @return					NG エラーコード
		* @note						メモリアロケータ、メモリ領域サイズは使用しない
		*/
		NG_ERRCODE Initialize(
			const char* name
			, IMemoryAllocator& alloc
			, size_type size
			);

		/*!
		* @brief					初期化
		* @param name				メモリアロケータの名称
		* @param pool				未使用
		* @param size				未使用
		* @return					NG エラーコード
		* @note						メモリプール、メモリ領域サイズは使用しない
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
		* @param src				割り当て元の情報
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
		*/
		void Free(
			void* p
			);

		/*!
		* @brief					初期化済みか
		*/
		bool IsInit() const;

		/*!
		* @brief					メモリ領域を取得する
		* @attention				利用不可。nullを返す
		*/
		void* GetMemory();
		const void* GetMemory() const;

		/*!
		* @brief					メモリ領域のサイズを取得する
		* @attention				size_t の限界値 (0xffffffff)を返す
		*/
		size_type GetMemSize() const;

		/*!
		* @brief					名称取得
		*/
		const char* GetName() const;

	private:
		static const u32 NAME_LENGTH = 127;		//!< 名称の長さ

	private:
		bool m_isInit;	//!< 初期化済みか
		char m_name[ NAME_LENGTH+1 ];	//!< 名称
	};

}	// namespace ng

#endif	// __NG_CORE_DEFAULT_ALLOCATOR_H__

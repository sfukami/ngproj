/*!
* @file		ngMemoryAllocator.h
* @brief	メモリアロケータ インターフェース
* @date		2016-08-28
* @author	s.fukami
*/

#ifndef __NG_CORE_MEMORY_ALLOCATOR_H__
#define __NG_CORE_MEMORY_ALLOCATOR_H__

namespace ng
{
	class CMemoryPool;
}

namespace ng
{
	/*!
	* @brief					メモリアロケータ インターフェース
	*/
	class NG_DECL IMemoryAllocator
	{
	public:
		IMemoryAllocator() { }
		virtual ~IMemoryAllocator() { }

		/*!
		* @brief					初期化
		* @param name				メモリアロケータの名称
		* @param alloc				使用するメモリアロケータ
		* @param size				使用するメモリ領域サイズ（バイト）
		* @return					NG エラーコード
		*/
		virtual NG_ERRCODE Initialize(
			const char* name
			, IMemoryAllocator& alloc
			, size_type size
			) = 0;

		/*!
		* @brief					初期化
		* @param name				メモリアロケータの名称
		* @param pool				使用するメモリプール
		* @param size				使用するメモリ領域サイズ（バイト）
		* @return					NG エラーコード
		*/
		virtual NG_ERRCODE Initialize(
			const char* name
			, CMemoryPool& pool
			, size_type size
			) = 0;

		/*!
		* @brief					終了処理
		*/
		virtual void Finalize() = 0;

		/*!
		* @brief					メモリ領域を割り当て、取得する
		* @param size				割り当てるメモリ領域サイズ（バイト）
		* @param alignment			アライメント（バイト）
		* @param src				割り当て元の情報（NG_CONFIG_MEMORY_DBGINFO定義時のみ）
		* @return					割り当てたメモリ領域へのポインタ
		*/
		virtual void* Allocate(
			size_type size
			, u32 alignment
		#if defined(NG_CONFIG_MEMORY_DBGINFO)
			, const char* src
		#endif
			) = 0;

		/*!
		* @brief					割り当て済みのメモリ領域を解放する
		* @param p					解放するメモリ領域へのポインタ
		*/
		virtual void Free(
			void* p
			) = 0;

		/*!
		* @brief					メモリ領域を取得する
		*/
		virtual void* GetMemory() = 0;
		virtual const void* GetMemory() const = 0;

		/*!
		* @brief					メモリ領域のサイズを取得する
		*/
		virtual size_type GetMemSize() const = 0;

		/*!
		* @brief					名称取得
		*/
		virtual const char* GetName() const = 0;

	#if defined(NG_CONFIG_MEMORY_PRINT_LOG)
		/*!
		* @brief					ログ出力有効設定
		*/
		virtual void SetPrintLogEnable(bool enable) { }
		virtual bool GetPrintLogEnable() const { return false; }
	#endif
	};

}	// namespace ng

#endif	// __NG_CORE_MEMORY_ALLOCATOR_H__
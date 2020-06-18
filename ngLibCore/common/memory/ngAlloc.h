/*!
* @file		ngAlloc.h
* @brief	メモリ管理
* @date		2017-08-28
* @author	s.fukami
*/

#ifndef __NG_CORE_ALLOC_H__
#define __NG_CORE_ALLOC_H__

#include <new>	// for placement new

//! メモリアロケーション デフォルトアライメント
#define NG_MEMORY_DEFAULT_ALIGNMENT		(8)

namespace ng
{
	class IMemoryAllocator;
}

/*!
* @brief					new演算子オーバーロード
* @param size				割り当てるメモリ領域サイズ（バイト）
* @param alloc				使用するメモリアロケータ
* @param alignment			アライメント（バイト）
* @param src				割り当て元の情報
*/
void* operator new(
	ng::size_type size
	, ng::IMemoryAllocator& alloc
	, ng::u32 alignment
#if defined(NG_CONFIG_MEMORY_DBGINFO)
	, const char* src
#endif
	);

/*!
* @brief					new[]演算子オーバーロード
* @param size				割り当てるメモリ領域サイズ（バイト）
* @param alloc				使用するメモリアロケータ
* @param alignment			アライメント（バイト）
* @param src				割り当て元の情報
*/
void* operator new[](
	ng::size_type size
	, ng::IMemoryAllocator& alloc
	, ng::u32 alignment
#if defined(NG_CONFIG_MEMORY_DBGINFO)
	, const char* src
#endif
	);

/*!
* @brief					delete演算子オーバーロード
* @param p					解放するメモリ領域へのポインタ
* @param alloc				使用するメモリアロケータ
* @param alignment			アライメント（バイト）
* @param src				解放元の情報
* @attention				使用不可
* @note						for warning C4291
*/
void operator delete(
	void* p
	, ng::IMemoryAllocator& alloc
	, ng::u32 alignment
#if defined(NG_CONFIG_MEMORY_DBGINFO)
	, const char* src
#endif
	);

/*!
* @brief					delete[]演算子オーバーロード
* @param p					解放するメモリ領域へのポインタ
* @param alloc				使用するメモリアロケータ
* @param alignment			アライメント（バイト）
* @param src				解放元の情報
* @attention				使用不可
* @note						for warning C4291
*/
void operator delete[](
	void* p
	, ng::IMemoryAllocator& alloc
	, ng::u32 alignment
#if defined(NG_CONFIG_MEMORY_DBGINFO)
	, const char* src
#endif
	);


/*!
* @brief					delete演算子オーバーロード
* @param p					解放するメモリ領域へのポインタ
* @param alloc				使用するメモリアロケータ
* @param src				解放元の情報
*/
void operator delete(
	void* p
	, ng::IMemoryAllocator& alloc
#if defined(NG_CONFIG_MEMORY_DBGINFO)
	, const char* src
#endif
	);

/*!
* @brief					delete[]演算子オーバーロード
* @param p					解放するメモリ領域へのポインタ
* @param alloc				使用するメモリアロケータ
* @param src				解放元の情報
*/
void operator delete[](
	void* p
	, ng::IMemoryAllocator& alloc
#if defined(NG_CONFIG_MEMORY_DBGINFO)
	, const char* src
#endif
	);

	/*!
	* @brief					メモリアロケータを用いてメモリ領域を確保する
	* @param _alloc				使用するメモリアロケータ
	*/
#if defined(NG_CONFIG_MEMORY_DBGINFO)
	#define NG_NEW(_alloc)	new(_alloc, NG_MEMORY_DEFAULT_ALIGNMENT, NG_FILE_LINE)
#else
	#define NG_NEW(_alloc)	new(_alloc, NG_MEMORY_DEFAULT_ALIGNMENT)
#endif

	/*!
	* @brief					メモリアロケータを用いてメモリ領域を確保する
	* @param _alloc				使用するメモリアロケータ
	* @param _alignment			アライメント
	*/
#if defined(NG_CONFIG_MEMORY_DBGINFO)
	#define NG_NEW_ALIGNED(_alloc, _alignment)	new(_alloc, _alignment, NG_FILE_LINE)
#else
	#define NG_NEW_ALIGNED(_alloc, _alignment)	new(_alloc, _alignment)
#endif

	/*!
	* @brief					メモリアロケータを用いてメモリ領域を解放する
	* @param _alloc				使用するメモリアロケータ
	* @param _p					解放するメモリ領域へのポインタ
	*/
#if defined(NG_CONFIG_MEMORY_DBGINFO)
	#define NG_DELETE(_alloc, _p) \
		{ \
			if(_p) { \
				ng::PlacementDelete(_p, _p); \
				::operator delete(_p, _alloc, NG_FILE_LINE); \
			} \
		}
#else
	#define NG_DELETE(_alloc, _p) \
		{ \
			if(_p) { \
				ng::PlacementDelete(_p, _p); \
				::operator delete(_p, _alloc); \
			} \
		}
#endif

	/*!
	* @brief					メモリアロケータを用いてメモリ領域を解放する（null代入版）
	* @param _alloc				使用するメモリアロケータ
	* @param _p					解放するメモリ領域へのポインタ
	* @note						引数 _p へnullを代入する
	*/
#if defined(NG_CONFIG_MEMORY_DBGINFO)
#define NG_SAFE_DELETE(_alloc, _p) \
		{ \
			if(_p) { \
				ng::PlacementDelete(_p, _p); \
				::operator delete(_p, _alloc, NG_FILE_LINE); \
				_p = nullptr; \
			} \
		}
#else
#define NG_SAFE_DELETE(_alloc, _p) \
		{ \
			if(_p) { \
				ng::PlacementDelete(_p, _p); \
				::operator delete(_p, _alloc); \
				_p = nullptr; \
			} \
		}
#endif

	/*!
	* @brief					メモリアロケータを用いてメモリ領域を解放する（配列用）
	* @param _alloc				使用するメモリアロケータ
	* @param _p					解放するメモリ領域へのポインタ
	*/
#if defined(NG_CONFIG_MEMORY_DBGINFO)
#define NG_DELETE_ARRAY(_alloc, _p)	\
		{ \
			if(_p) { \
				ng::PlacementDeleteArray(_p, _p); \
				::operator delete[](_p, _alloc, NG_FILE_LINE); \
			} \
		}
#else
#define NG_DELETE_ARRAY(_alloc, _p)	\
		{ \
			if(_p) { \
				ng::PlacementDeleteArray(_p, _p); \
				::operator delete[](_p, _alloc); \
			} \
		}
#endif

	/*!
	* @brief					メモリアロケータを用いてメモリ領域を解放する（配列用）（null代入版）
	* @param _alloc				使用するメモリアロケータ
	* @param _p					解放するメモリ領域へのポインタ
	* @note						引数 _p へnullを代入する
	*/
#if defined(NG_CONFIG_MEMORY_DBGINFO)
	#define NG_SAFE_DELETE_ARRAY(_alloc, _p)	\
		{ \
			if(_p) { \
				ng::PlacementDeleteArray(_p, _p); \
				::operator delete[](_p, _alloc, NG_FILE_LINE); \
				_p = nullptr; \
			} \
		}
#else
	#define NG_SAFE_DELETE_ARRAY(_alloc, _p)	\
		{ \
			if(_p) { \
				ng::PlacementDeleteArray(_p, _p); \
				::operator delete[](_p, _alloc); \
				_p = nullptr; \
			} \
		}
#endif

	/*!
	* @brief					メモリアロケータを用いて指定バイトのメモリ領域を確保する
	* @param _alloc				使用するメモリアロケータ
	* @param _size				確保するバイト数
	*/
#if defined(NG_CONFIG_MEMORY_DBGINFO)
	#define NG_NEW_BYTE(_alloc, _size)	(new(_alloc, NG_MEMORY_DEFAULT_ALIGNMENT, NG_FILE_LINE) char[_size])
#else
	#define NG_NEW_BYTE(_alloc, _size)	(new(_alloc, NG_MEMORY_DEFAULT_ALIGNMENT) char[_size])
#endif

	/*!
	* @brief					メモリアロケータを用いて指定バイトのメモリ領域を確保する
	* @param _alloc				使用するメモリアロケータ
	* @param _size				確保するバイト数
	* @param _alignment			アライメント
	*/
#if defined(NG_CONFIG_MEMORY_DBGINFO)
	#define NG_NEW_BYTE_ALIGNED(_alloc, _size, _alignment)	(new(_alloc, _alignment, NG_FILE_LINE) char[_size])
#else
	#define NG_NEW_BYTE_ALIGNED(_alloc, _size, _alignment)	(new(_alloc, _alignment) char[_size])
#endif

/*!
* @brief					メモリアロケータを用いてメモリ領域を解放する（NG_NEW_BYTEマクロ用）
* @param _alloc				使用するメモリアロケータ
* @param _p					解放するメモリ領域へのポインタ
*/
#define NG_DELETE_BYTE(_alloc, _p)	NG_DELETE(_alloc, (char*)_p)

namespace ng
{
	template <typename T>
	NG_INLINE void PlacementDelete(void* pBuffer, T* p);
	template <typename T>
	NG_INLINE void SafePlacementDelete(void* pBuffer, T*& p);

	template <typename T>
	NG_INLINE void PlacementDeleteArray(void* pBuffer, T* p);
	template <typename T>
	NG_INLINE void SafePlacementDeleteArray(void* pBuffer, T*& p);

	void* GetArrayHeadPointer(void* p);
	int GetArraySizeByPointer(void* p);

}	// namespace ng

/*!
* @brief					再配置new
* @param _pBuffer			配置先のバッファへのポインタ
*/
#define NG_PLACEMENT_NEW(_pBuffer)	::new(_pBuffer)

/*!
* @brief					再配置delete
* @param _pBuffer			配置元のバッファへのポインタ
* @param _p					解放するメモリ領域へのポインタ
*/
#define NG_PLACEMENT_DELETE(_pBuffer, _p)	ng::PlacementDelete(_pBuffer, _p)

/*!
* @brief					再配置delete（null代入版）
* @param _pBuffer			配置元のバッファへのポインタ
* @param _p					解放するメモリ領域へのポインタ
* @note						引数 _p へnullを代入する
*/
#define NG_SAFE_PLACEMENT_DELETE(_pBuffer, _p)	ng::SafePlacementDelete(_pBuffer, _p)

/*!
* @brief					再配置delete（配列用）
* @param _pBuffer			配置元のバッファへのポインタ
* @param _p					解放するメモリ領域へのポインタ
*/
#define NG_PLACEMENT_DELETE_ARRAY(_pBuffer, _p)	ng::PlacementDeleteArray(_pBuffer, _p)

/*!
* @brief					再配置delete（配列用）（null代入版）
* @param _pBuffer			配置元のバッファへのポインタ
* @param _p					解放するメモリ領域へのポインタ
* @note						引数 _p へnullを代入する
*/
#define NG_SAFE_PLACEMENT_DELETE_ARRAY(_pBuffer, _p)	ng::SafePlacementDeleteArray(_pBuffer, _p)

namespace ng
{
	/*!
	* @brief					再配置delete
	* @param pBuffer			配置元のバッファへのポインタ
	* @param p					解放するメモリ領域へのポインタ
	*/
	template <typename T>
	NG_INLINE void PlacementDelete(void* /*pBuffer*/, T* p)
	{
		p->~T();
	}

	/*!
	* @brief					再配置delete（引数null代入版）
	* @param pBuffer			配置元のバッファへのポインタ
	* @param p					解放するメモリ領域へのポインタ
	*/
	template <typename T>
	NG_INLINE void SafePlacementDelete(void* pBuffer, T*& p)
	{
		if(p) {
			PlacementDelete(pBuffer, p);
			p = nullptr;
		}
	}

	/*!
	* @brief					再配置delete（配列用）
	* @param pBuffer			配置元のバッファへのポインタ
	* @param p					解放するメモリ領域へのポインタ
	*/
	template <typename T>
	NG_INLINE void PlacementDeleteArray(void* /*pBuffer*/, T* p)
	{
		// 配列の要素数取得
		// ※処理系依存
		int length = GetArraySizeByPointer(p);

		for(int i = 0; i < length; ++i, ++p)
		{
			p->~T();
		}
	}

	/*!
	* @brief					再配置delete（配列用）（引数null代入版）
	* @param pBuffer			配置元のバッファへのポインタ
	* @param p					解放するメモリ領域へのポインタ
	*/
	template <typename T>
	NG_INLINE void SafePlacementDeleteArray(void* pBuffer, T*& p)
	{
		if(p) {
			PlacementDeleteArray(pBuffer, p);
			p = nullptr;
		}
	}

}	// namespace ng

#endif	// __NG_CORE_ALLOC_H__
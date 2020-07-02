/*!
* @file		appMemoryModule.h
* @brief	メモリ機能
* @date		2020-07-02
* @author	s.fukami
*/

#ifndef __APP_MEMORY_MODULE_H__
#define __APP_MEMORY_MODULE_H__

#include "appMemoryAllocatorId.h"

namespace ng
{
	class IMemoryAllocator;
}
namespace app
{
	class CApplicationMemory;
}

/*!
* @brief					アプリケーション メモリアロケータ取得
*/
#define APP_GET_MEMALLOC(_id)	(*app::CMemoryModule::GetAllocator(_id))
//! アプリケーション
#define APP_MEMALLOC_APPLICATION	(APP_GET_MEMALLOC(app::eMemoryAllocatorId::APPLICATION))
//! ワーク
#define APP_MEMALLOC_WORK			(APP_GET_MEMALLOC(app::eMemoryAllocatorId::WORK))

namespace app
{
	/*!
	* @brief					メモリ機能
	*/
	class CMemoryModule
	{
		friend class CGame;

	public:
		CMemoryModule() = delete;
		~CMemoryModule() = delete;

		/*!
		* @brief					メモリアロケータ取得
		* @param id					メモリアロケータID
		* @return					メモリアロケータ
		*/
		static ng::IMemoryAllocator* GetAllocator(eMemoryAllocatorId id);

	private:
		/*! アプリケーションメモリのインスタンスを設定 */
		static void SetApplicationMemory(CApplicationMemory* pAppMem);

		/*! 有効か */
		static bool _isValid();

	private:
		static CApplicationMemory* s_pAppMem;	//!< アプリケーションメモリへの参照
	};

}	// namespace app

#endif	// __APP_MEMORY_MODULE_H__
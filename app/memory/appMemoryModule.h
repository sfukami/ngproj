/*!
* @file		appMemoryModule.h
* @brief	メモリ機能
* @date		2020-07-02
* @author	s.fukami
*/

#ifndef __APP_MEMORY_MODULE_H__
#define __APP_MEMORY_MODULE_H__

#include "ngLibCore/traits/ngNonInstantiable.h"
#include "ngLibCore/memory/pointer/ngWeakPtr.h"
#include "appMemoryAllocatorId.h"

namespace ng
{
	class IMemoryAllocator;
}
namespace app
{
	class CApplicationMemory;
}

namespace app
{
	/*!
	* @brief					メモリ機能
	*/
	class CMemoryModule : public ng::CNonInstantiable
	{
		friend class CApplication;

	public:
		/*!
		* @brief					メモリアロケータ取得
		* @param id					メモリアロケータID
		* @return					メモリアロケータ
		*/
		static ng::CWeakPtr<ng::IMemoryAllocator> GetAllocator(eMemoryAllocatorId id);

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
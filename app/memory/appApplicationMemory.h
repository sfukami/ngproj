/*!
* @file		appApplicationMemory.h
* @brief	アプリケーションメモリ
* @date		2020-07-02
* @author	s.fukami
*/

#ifndef __APP_APPLICATION_MEMORY_H__
#define __APP_APPLICATION_MEMORY_H__

#include "ngLibCore/memory/ngMemoryManager.h"
#include "ngLibCore/memory/pool/ngRootMemoryPool.h"
#include "appMemoryAllocatorId.h"

namespace ng
{
	class IMemoryAllocator;
}

namespace app
{
	/*!
	* @brief					アプリケーションメモリ
	*/
	class CApplicationMemory
	{
	public:
		CApplicationMemory();
		~CApplicationMemory();

		/*!
		* @brief					初期化
		* @return					成否
		*/
		bool Initialize();

		/*!
		* @brief					終了処理
		*/
		void Finalize();

		/*!
		* @brief					ワークメモリをクリア
		*/
		void ClearWorkMemory();

		/*!
		* @brief					メモリアロケータ取得
		* @param id					メモリアロケータID
		* @return					メモリアロケータ
		*/
		ng::IMemoryAllocator* GetAllocator(eMemoryAllocatorId id);

	private:
		ng::CRootMemoryPool	m_memPool;	//!< メモリプール
		ng::CMemoryManager	m_memMngr;	//!< メモリ管理
	};

}	// namespace app

#endif	// __APP_APPLICATION_MEMORY_H__
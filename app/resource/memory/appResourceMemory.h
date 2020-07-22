/*!
* @file		appResourceMemory.h
* @brief	リソースメモリ
* @date		2020-07-21
* @author	s.fukami
*/

#ifndef __APP_RESOURCE_MEMORY_H__
#define __APP_RESOURCE_MEMORY_H__

#include "ngLibCore/memory/pool/ngMemoryPool.h"
#include "ngLibCore/memory/ngMemoryManager.h"
#include "ngLibCore/memory/pointer/ngWeakPtr.h"
#include "appResourceMemoryType.h"

namespace ng
{
	class IMemoryAllocator;
}

namespace app
{
	/*!
	* @brief					リソースメモリ
	*/
	class CResourceMemory
	{
	public:
		CResourceMemory();
		~CResourceMemory();

		/*!
		* @brief					初期化
		* @param alloc				利用するメモリアロケータ
		* @return					成否
		*/
		bool Initialize(ng::IMemoryAllocator& alloc);

		/*!
		* @brief					終了処理
		*/
		void Finalize();

		/*!
		* @brief					メモリアロケータ取得
		* @param id					リソースメモリタイプ
		* @return					メモリアロケータ
		*/
		ng::CWeakPtr<ng::IMemoryAllocator> GetAllocator(eResourceMemoryType type);

	private:
		ng::CMemoryPool		m_memPool;	//!< メモリプール
		ng::CMemoryManager	m_memMngr;	//!< メモリ管理
	};

}	// namespace app

#endif	// __APP_RESOURCE_MEMORY_H__
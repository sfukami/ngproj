/*!
* @file		appApplicationMemory.cpp
* @brief	アプリケーションメモリ
* @date		2020-07-02
* @author	s.fukami
*/

#include "ngLibCore/allocator/ngDefaultAllocator.h"
#include "appApplicationMemory.h"

namespace app
{
	CApplicationMemory::CApplicationMemory()
	{
	}

	CApplicationMemory::~CApplicationMemory()
	{
		Finalize();
	}

	bool CApplicationMemory::Initialize()
	{
		NG_ERRCODE err = NG_ERRCODE_DEFAULT;

		// ルートメモリプール初期化
		{
			ng::size_type allocSize = NG_MB(1);	// TODO:
			if(NG_FAILED(err = m_memPool.Initialize(allocSize))) {
				NG_ERRLOG_C("ApplicationMemory", err, "ルートメモリプールの初期化に失敗");
				return false;
			}
		}

		// メモリマネージャ初期化
		if(NG_FAILED(err = m_memMngr.Initialize(
			m_memPool.GetMemoryPool(),
			static_cast<unsigned int>(eMemoryAllocatorId::NUM)))
			) {
			m_memPool.Finalize();
			NG_ERRLOG_C("ApplicationMemory", err, "メモリマネージャの初期化に失敗");
			return false;
		}

		// 各メモリアロケータ初期化
		{
			// TODO:
			m_memMngr.CreateAndRegisterAllocator<ng::CDefaultAllocator>(
				static_cast<ng::u32>(eMemoryAllocatorId::APPLICATION), "app_application", NG_KB(1)
				);
			m_memMngr.CreateAndRegisterAllocator<ng::CDefaultAllocator>(
				static_cast<ng::u32>(eMemoryAllocatorId::WORK), "app_work", NG_KB(1)
				);
		}

		return true;
	}

	void CApplicationMemory::Finalize()
	{
		m_memMngr.Finalize();
		m_memPool.Finalize();
	}

	ng::IMemoryAllocator* CApplicationMemory::GetAllocator(eMemoryAllocatorId id)
	{
		return m_memMngr.GetAllocator(static_cast<ng::u32>(id));
	}

}	// namespace app
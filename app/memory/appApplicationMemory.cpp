/*!
* @file		appApplicationMemory.cpp
* @brief	アプリケーションメモリ
* @date		2020-07-02
* @author	s.fukami
*/

#include "ngLibCore/allocator/ngDefaultAllocator.h"
#include "ngLibCore/allocator/ngStackAllocator.h"
#include "appApplicationMemory.h"

namespace app
{
	//! メモリサイズ
	enum eMemorySize : ng::size_type
	{
		INSTANCE		= NG_KB(1),		//!< インスタンス
		APPLICATION		= NG_MB(1),		//!< アプリケーション
		WORK			= NG_MB(1),		//!< ワーク

		//! 合計
		TOTAL			= INSTANCE
						+ APPLICATION
						+ WORK
						,
	};

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
			ng::size_type allocSize = eMemorySize::TOTAL;
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
			m_memMngr.CreateAndRegisterAllocator<ng::CDefaultAllocator>(
				static_cast<ng::u32>(eMemoryAllocatorId::APPLICATION), "app_application", eMemorySize::APPLICATION
				);
			m_memMngr.CreateAndRegisterAllocator<ng::CStackAllocator>(
				static_cast<ng::u32>(eMemoryAllocatorId::WORK), "app_work", eMemorySize::WORK
				);
		}

		return true;
	}

	void CApplicationMemory::Finalize()
	{
		m_memMngr.Finalize();
		m_memPool.Finalize();
	}

	void CApplicationMemory::ClearWorkMemory()
	{
		ng::CWeakPtr<ng::IMemoryAllocator> allocPtr = GetAllocator(eMemoryAllocatorId::WORK);

		if(allocPtr != nullptr) {
			std::dynamic_pointer_cast<ng::CStackAllocator>(allocPtr)->Clear();
		}
	}

	ng::CWeakPtr<ng::IMemoryAllocator> CApplicationMemory::GetAllocator(eMemoryAllocatorId id)
	{
		return m_memMngr.GetAllocator(static_cast<ng::u32>(id));
	}

}	// namespace app
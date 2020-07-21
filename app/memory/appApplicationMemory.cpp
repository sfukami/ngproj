﻿/*!
* @file		appApplicationMemory.cpp
* @brief	アプリケーションメモリ
* @date		2020-07-02
* @author	s.fukami
*/

#include "ngLibCore/allocator/ngDefaultAllocator.h"
#include "ngLibCore/allocator/ngStackAllocator.h"
#include "appApplicationMemory.h"
#include "appApplicationMemorySize.h"

namespace app
{
	//! インスタンス用メモリサイズ
	#define _INSTANCE_MEMSIZE	(NG_KB(1))

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
			ng::size_type allocSize = GetApplicationMemorySizeTotal();
			allocSize += _INSTANCE_MEMSIZE;

			if(NG_FAILED(err = m_memPool.Initialize(allocSize))) {
				NG_ERRLOG_C("ApplicationMemory", err, "ルートメモリプールの初期化に失敗");
				return false;
			}
		}

		// メモリマネージャ初期化
		if(NG_FAILED(err = m_memMngr.Initialize(
			m_memPool.GetMemoryPool(),
			ng::UnderlyingCast(eMemoryAllocatorId::NUM)
			))) {
			m_memPool.Finalize();
			NG_ERRLOG_C("ApplicationMemory", err, "メモリマネージャの初期化に失敗");
			return false;
		}

		// 各メモリアロケータ生成
		{
			// メモリアロケータ生成マクロ
			#define _CREATE_MEMALLOC(_type, _id, _name) \
				m_memMngr.CreateAndRegisterAllocator<_type>( \
					ng::UnderlyingCast(_id), _name, GetApplicationMemorySize(_id) \
					);

			// アプリケーション
			_CREATE_MEMALLOC(ng::CDefaultAllocator,	eMemoryAllocatorId::APPLICATION,	"app_application");
			// ワーク
			_CREATE_MEMALLOC(ng::CStackAllocator,	eMemoryAllocatorId::WORK,			"app_work");

			#undef _CREATE_MEMALLOC
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
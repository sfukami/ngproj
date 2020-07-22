/*!
* @file		appResourceMemory.cpp
* @brief	リソースメモリ
* @date		2020-07-21
* @author	s.fukami
*/

#include "ngLibCore/allocator/ngMemoryAllocator.h"
#include "appResourceMemory.h"
#include "appResourceMemorySize.h"

namespace app
{
	//! インスタンス用メモリサイズ
	#define _INSTANCE_MEMSIZE	(NG_KB(1))

	CResourceMemory::CResourceMemory()
	{
	}
	CResourceMemory::~CResourceMemory()
	{
		Finalize();
	}

	bool CResourceMemory::Initialize(ng::IMemoryAllocator& alloc)
	{
		NG_ERRCODE err = NG_ERRCODE_DEFAULT;

		// メモリプール初期化
		{
			ng::size_type allocSize = GetResourceMemorySizeTotal();
			allocSize += _INSTANCE_MEMSIZE;

			if(NG_FAILED(err = m_memPool.Pool(
				alloc,
				allocSize
				))) {
				NG_ERRLOG_C("ResourceMemory", err, "メモリプールの初期化に失敗しました.");
				return false;
			}
		}

		// メモリマネージャ初期化
		if(NG_FAILED(err = m_memMngr.Initialize(
			m_memPool,
			static_cast<ng::u32>(eResourceMemoryType::NUM)
			))) {
			m_memPool.Unpool();
			NG_ERRLOG_C("ResourceMemory", err, "メモリマネージャの初期化に失敗しました.");
			return false;
		}

		// 各メモリアロケータ生成
		{
			// メモリアロケータ生成マクロ
			#define _CREATE_MEMALLOC(_type, _id, _name) \
				m_memMngr.CreateAndRegisterAllocator<_type>( \
					static_cast<ng::u32>(_id), _name, GetResourceMemorySize(_id) \
					);

			// MANAGE
			_CREATE_MEMALLOC(ng::CDefaultAllocator, eResourceMemoryType::MANAGE, "res_manage");
			// FIXED
			_CREATE_MEMALLOC(ng::CDefaultAllocator,	eResourceMemoryType::FIXED,	"res_fixed");
			// SCENE
			_CREATE_MEMALLOC(ng::CDefaultAllocator,	eResourceMemoryType::SCENE,	"res_scene");
			// TEMP
			_CREATE_MEMALLOC(ng::CDefaultAllocator,	eResourceMemoryType::TEMP,	"res_temp");

			#undef _CREATE_MEMALLOC
		}

		return true;
	}

	void CResourceMemory::Finalize()
	{
		m_memMngr.Finalize();
		m_memPool.Unpool();
	}

	ng::CWeakPtr<ng::IMemoryAllocator> CResourceMemory::GetAllocator(eResourceMemoryType type)
	{
		return m_memMngr.GetAllocator(static_cast<ng::u32>(type));
	}

}	// namespace app
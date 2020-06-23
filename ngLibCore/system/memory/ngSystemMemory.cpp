/*!
* @file		ngSystemMemory.cpp
* @brief	NGライブラリ システムメモリ
* @date		2018-02-19
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "ngSystemMemory.h"

namespace ng
{
	//! 最小メモリサイズ
	enum eSystemMemoryMinSize : size_type
	{
		INSTANCE	= NG_KB(1),		//!< インスタンス
		MAINSYS		= NG_KB(1),		//!< メインシステム
		GRAPHIC		= NG_KB(1),		//!< グラフィック
	};

	CSystemMemory::InitParam::InitParam()
	{
		AllocInfo info[] = {
			{ eSystemMemoryMinSize::MAINSYS },
			{ eSystemMemoryMinSize::GRAPHIC },
		};
		NG_MEMCPY(allocInfo, info, NG_SIZEOF(info));
	}

	void CSystemMemory::InitParam::SetAllocSize(eSystemMemoryType type, size_type allocSize)
	{
		allocInfo[ static_cast<u32>(type) ].allocSize = allocSize;
	}

	const CSystemMemory::InitParam::AllocInfo& CSystemMemory::InitParam::GetAllocInfo(eSystemMemoryType type) const
	{
		return allocInfo[ static_cast<u32>(type) ];
	}

	size_type CSystemMemory::InitParam::GetTotalAllocSize() const
	{
		size_type total = 0;
		for(int i = 0; i < static_cast<u32>(eSystemMemoryType::NUM); i++)
		{
			total += allocInfo[i].allocSize;
		}

		return total;
	}

	CSystemMemory::CSystemMemory()
	{
	}

	CSystemMemory::~CSystemMemory()
	{
		Finalize();
	}

	NG_ERRCODE CSystemMemory::Initialize(const InitParam& param)
	{
		NG_ERRCODE ret = eNG_S_OK;

		Finalize();

		// ルートメモリプール初期化
		{
			size_type allocSize = param.GetTotalAllocSize() + eSystemMemoryMinSize::INSTANCE;
			if(NG_FAILED(ret = m_memPool.Initialize(allocSize))) {
				NG_ERRLOG(ret, "ルートメモリプールの初期化に失敗");
				return ret;
			}
		}

		// メモリマネージャ初期化
		if(NG_FAILED(ret = m_memMngr.Initialize(m_memPool.GetMemoryPool(), static_cast<u32>(eSystemMemoryType::NUM)))) {
			m_memPool.Finalize();
			NG_ERRLOG(ret, "メモリマネージャの初期化に失敗");
			return ret;
		}

		// 各メモリアロケータ初期化
		{
			// メモリアロケータ生成マクロ
			#define CREATE_ALLOC(_alloc, _type, _name) { \
				const InitParam::AllocInfo& info = param.GetAllocInfo(_type); \
				_alloc* pAlloc = m_memMngr.CreateAndRegisterAllocator<_alloc>(static_cast<u32>(_type), _name, info.allocSize); \
			}
			
			// メインシステム
			CREATE_ALLOC(CDefaultAllocator, eSystemMemoryType::MAINSYS, "ng_mainsys");
			// グラフィック
			CREATE_ALLOC(CDefaultAllocator, eSystemMemoryType::GRAPHIC, "ng_graphic");

			#undef CREATE_ALLOC
		}

		return ret;
	}

	void CSystemMemory::Finalize()
	{
		m_memMngr.Finalize();
		m_memPool.Finalize();
	}

	IMemoryAllocator* CSystemMemory::GetAllocator(eSystemMemoryType type)
	{
		return m_memMngr.GetAllocator(static_cast<u32>(type));
	}

}	// namespace ng
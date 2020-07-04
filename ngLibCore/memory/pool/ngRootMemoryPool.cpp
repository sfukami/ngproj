/*!
* @file		ngRootMemoryPool.cpp
* @brief	ルートメモリプール
* @date		2019-01-10
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "ngRootMemoryPool.h"

namespace ng
{
	CRootMemoryPool::CRootMemoryPool()
	{
	}

	CRootMemoryPool::~CRootMemoryPool()
	{
		Finalize();
	}

	NG_ERRCODE CRootMemoryPool::Initialize(size_type size)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		if(NG_FAILED(ret = m_rootAlloc.Initialize("ng_rootmem"))) {
			NG_ERRLOG_C("RootMemoryPool", ret, "ルートアロケータの初期化に失敗");
			return ret;
		}
		if(NG_FAILED(ret = m_memPool.Pool(NG_NEW_BYTE(m_rootAlloc, size), size))) {
			NG_ERRLOG_C("RootMemoryPool", ret, "ルートアロケータを用いたメモリ領域のプールに失敗");
			return ret;
		}

		return ret;
	}

	void CRootMemoryPool::Finalize()
	{
		if(m_memPool.IsPool()) {
			NG_DELETE(m_rootAlloc, m_memPool.GetMemory());
			m_memPool.Unpool();
		}
	}

	CMemoryPool& CRootMemoryPool::GetMemoryPool()
	{
		return m_memPool;
	}

	const CMemoryPool& CRootMemoryPool::GetMemoryPool() const
	{
		return m_memPool;
	}

}	// namespace ng
/*!
* @file		ngDX12DepthStencilManager.cpp
* @brief	DX12深度ステンシルマネージャ
* @date		2019-08-14
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "../../common/ngDX12Common.h"
#include "ngDX12DepthStencilManager.h"
#include "ngDX12DepthStencilId.h"

namespace ng
{
	CDX12DepthStencilManager::CDX12DepthStencilManager()
	{
	}
	CDX12DepthStencilManager::~CDX12DepthStencilManager()
	{
		Finalize();
	}

	NG_ERRCODE CDX12DepthStencilManager::CreateDepthStencil(
		CDX12Device& device,
		u32 width,
		u32 height,
		eDX12DepthStencilId id
		)
	{
		NG_ASSERT_RANGE(eDX12DepthStencilId::ID_BEGIN, <=, id, <, eDX12DepthStencilId::ID_NUM);

		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// DX12深度ステンシル生成
		CDX12DepthStencil& ds = m_dss[ static_cast<int>(id) ];
		ds.Destroy();
		if(NG_FAILED(ret = ds.Create(device, width, height))) {
			return ret;
		}

		return ret;
	}

	void CDX12DepthStencilManager::Finalize()
	{
		for(auto& ds : m_dss)
		{
			ds.Destroy();
		}
	}

	CDX12DepthStencil* CDX12DepthStencilManager::GetDepthStencil(eDX12DepthStencilId id)
	{
		NG_ASSERT(id < eDX12DepthStencilId::ID_NUM);

		CDX12DepthStencil& ds = m_dss[ static_cast<u32>(id) ];
		if(!ds.IsValid()) {
			return nullptr;
		}

		return &ds;
	}
	const CDX12DepthStencil* CDX12DepthStencilManager::GetDepthStencil(eDX12DepthStencilId id) const
	{
		return const_cast<CDX12DepthStencilManager*>(this)->GetDepthStencil(id);
	}

}	// namespace ng
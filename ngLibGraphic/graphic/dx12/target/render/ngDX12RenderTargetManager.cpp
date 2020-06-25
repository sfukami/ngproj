/*!
* @file		ngDX12RenderTargetManager.cpp
* @brief	DX12レンダーターゲットマネージャ
* @date		2018-05-12
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "../../common/ngDX12Common.h"
#include "ngDX12RenderTargetManager.h"
#include "../../swapchain/ngDX12SwapChain.h"

namespace ng
{
	CDX12RenderTargetManager::CDX12RenderTargetManager()
	{
	}

	CDX12RenderTargetManager::~CDX12RenderTargetManager()
	{
		Finalize();
	}

	NG_ERRCODE CDX12RenderTargetManager::CreateRenderTargetView(
		CDX12Device& device,
		CDX12SwapChain& swapChain,
		u32 bufferIndex,
		eDX12RenderTargetId id
		)
	{
		NG_ASSERT_RANGE(eDX12RenderTargetId::ID_BEGIN, <=, id, <, eDX12RenderTargetId::ID_NUM);

		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// DX12レンダーターゲット生成
		CDX12RenderTarget& rt = m_rts[ static_cast<u32>(id) ];
		rt.Destroy();
		if(NG_FAILED(ret = rt.Create(device, swapChain, bufferIndex))) {
			return ret;
		}

		return ret;
	}

	void CDX12RenderTargetManager::Finalize()
	{
		for(auto& rt : m_rts)
		{
			rt.Destroy();
		}
	}

	CDX12RenderTarget* CDX12RenderTargetManager::GetRenderTarget(eDX12RenderTargetId id)
	{
		NG_ASSERT(id < eDX12RenderTargetId::ID_NUM);

		CDX12RenderTarget& rt = m_rts[ static_cast<u32>(id) ];
		if(!rt.IsValid()) {
			return nullptr;
		}

		return &rt;
	}
	const CDX12RenderTarget* CDX12RenderTargetManager::GetRenderTarget(eDX12RenderTargetId id) const
	{
		return const_cast<CDX12RenderTargetManager*>(this)->GetRenderTarget(id);
	}

}	// namespace ng
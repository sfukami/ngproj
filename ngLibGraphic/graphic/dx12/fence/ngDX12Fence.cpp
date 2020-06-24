/*!
* @file		ngDX12Fence.cpp
* @brief	DX12フェンス
* @date		2017-09-24
* @author	s.fukami
*/

#include <d3d12.h>
#include "ngLibCore/common/ngCommon.h"
#include "../common/ngDX12Common.h"
#include "../device/ngDX12Device.h"
#include "ngDX12Fence.h"

namespace ng
{
	CDX12Fence::CDX12Fence()
		: m_pIFence(nullptr)
	{
	}

	CDX12Fence::~CDX12Fence()
	{
		Destroy();
	}

	NG_ERRCODE CDX12Fence::Create(CDX12Device& device, D3D12_FENCE_FLAGS flags)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;
		
		// DX12フェンス生成
		if(NG_FAILED(ret = device.Interface()->CreateFence(
			0,
			flags,
			IID_PPV_ARGS(&m_pIFence)
			))) {
			NG_DXERR("DX12Fence", ret, CreateFence, "DX12フェンスの生成に失敗しました.");
			return ret;
		}

		return ret;
	}

	u64 CDX12Fence::GetCompletedValue()
	{
		return m_pIFence->GetCompletedValue();
	}

	NG_ERRCODE CDX12Fence::SetEventOnCompletion(u64 value, HANDLE hEvent)
	{
		return m_pIFence->SetEventOnCompletion(value, hEvent);
	}
	
	void CDX12Fence::Destroy()
	{
		NG_SAFE_RELEASE(m_pIFence);
	}

	bool CDX12Fence::IsValid() const
	{
		return (m_pIFence != nullptr);
	}

	ID3D12Fence* CDX12Fence::Interface()
	{
		return m_pIFence;
	}
	const ID3D12Fence* CDX12Fence::Interface() const
	{
		return m_pIFence;
	}

}	// namespace ng
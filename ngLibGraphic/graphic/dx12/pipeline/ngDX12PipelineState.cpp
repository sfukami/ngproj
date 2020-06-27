/*!
* @file		ngDX12PipelineState.cpp
* @brief	DX12パイプラインステート
* @date		2019-03-24
* @author	s.fukami
*/

#include <d3d12.h>
#include "ngLibCore/common/ngCommon.h"
#include "../common/ngDX12Common.h"
#include "../device/ngDX12Device.h"
#include "../rootsign/ngDX12RootSignature.h"
#include "../shader/ngDX12Shader.h"
#include "ngDX12PipelineState.h"
#include "ngDX12PipelineStateDesc.h"

namespace ng
{
	CDX12PipelineState::CDX12PipelineState()
		: m_pIState(nullptr)
	{
	}

	CDX12PipelineState::~CDX12PipelineState()
	{
		Destroy();
	}

	NG_ERRCODE CDX12PipelineState::Create(
		CDX12Device& device,
		const CDX12PipelineStateDesc& desc
		)
	{
		NG_ASSERT(!IsValid());

		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		ID3D12Device* pIDevice = device.Interface();
		NG_ASSERT(pIDevice != nullptr);

		if(NG_FAILED(ret = pIDevice->CreateGraphicsPipelineState(
			&desc,
			IID_PPV_ARGS(&m_pIState)
			))) {
			NG_DXERRLOG("DX12PipelineState", ret, CreateGraphicsPipelineState, "パイプラインステートの生成に失敗しました.");
			return ret;
		}

		return ret;
	}

	void CDX12PipelineState::Destroy()
	{
		NG_SAFE_RELEASE(m_pIState);
	}
	
	bool CDX12PipelineState::IsValid() const
	{
		return (m_pIState != nullptr);
	}
	
	ID3D12PipelineState* CDX12PipelineState::Interface()
	{
		return m_pIState;
	}
	const ID3D12PipelineState* CDX12PipelineState::Interface() const
	{
		return m_pIState;
	}

}	// namespace ng
/*!
* @file		ngDX12ResourceBarrierTransition.cpp
* @brief	DX12リソースバリア トランジション
* @date		2018-01-09
* @author	s.fukami
*/

#include <d3d12.h>
#include "../common/ngDX12Common.h"
#include "ngDX12ResourceBarrierTransition.h"

namespace ng
{
	CDX12ResourceBarrierTransition::CDX12ResourceBarrierTransition()
	{
	}

	CDX12ResourceBarrierTransition::~CDX12ResourceBarrierTransition()
	{
	}

	void CDX12ResourceBarrierTransition::Initialize(
		ID3D12Resource* pResource,
		D3D12_RESOURCE_STATES stateBefore,
		D3D12_RESOURCE_STATES stateAfter,
		UINT subresource,
		D3D12_RESOURCE_BARRIER_FLAGS flags
		)
	{
		//CD3DX12_RESOURCE_BARRIER::Transition(pResource, stateBefore, stateAfter);
		m_barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		m_barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		m_barrier.Transition.pResource = pResource;
		m_barrier.Transition.Subresource = subresource;
		m_barrier.Transition.StateBefore = stateBefore;
		m_barrier.Transition.StateAfter = stateAfter;
	}

}	// namespace ng
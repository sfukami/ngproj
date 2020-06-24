/*!
* @file		ngDX12ResourceBarrier.cpp
* @brief	DX12リソースバリア
* @date		2018-01-09
* @author	s.fukami
*/

#include "ngDX12ResourceBarrier.h"

namespace ng
{
	CDX12ResourceBarrier::CDX12ResourceBarrier()
	{
	}

	CDX12ResourceBarrier::~CDX12ResourceBarrier()
	{
	}

	const D3D12_RESOURCE_BARRIER& CDX12ResourceBarrier::GetResourceBarrier() const
	{
		return m_barrier;
	}

}	// namespace ng
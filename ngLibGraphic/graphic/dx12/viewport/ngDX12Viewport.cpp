/*!
* @file		ngDX12Viewport.cpp
* @brief	DX12ビューポート
* @date		2018-01-20
* @author	s.fukami
*/

#include "ngDX12Viewport.h"

namespace ng
{
	CDX12Viewport::CDX12Viewport()
	{
		m_viewport = {};
	}

	CDX12Viewport::~CDX12Viewport()
	{
	}

	void CDX12Viewport::Initialize(
		float topLeftX,
		float topLeftY,
		float width,
		float height,
		float minDepth,
		float maxDepth
		)
	{
		m_viewport.TopLeftX = topLeftX;
		m_viewport.TopLeftY = topLeftY;
		m_viewport.Width = width;
		m_viewport.Height = height;
		m_viewport.MinDepth = minDepth;
		m_viewport.MaxDepth = maxDepth;
	}

	const D3D12_VIEWPORT& CDX12Viewport::GetViewport() const
	{
		return m_viewport;
	}

}	// namespace ng
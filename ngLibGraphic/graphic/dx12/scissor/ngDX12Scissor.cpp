/*!
* @file		ngDX12Scissor.cpp
* @brief	DX12シザー矩形
* @date		2018-01-20
* @author	s.fukami
*/

#include "ngDX12Scissor.h"

namespace ng
{
	CDX12Scissor::CDX12Scissor()
	{
	}

	CDX12Scissor::~CDX12Scissor()
	{
	}

	void CDX12Scissor::Initialize(
		LONG left,
		LONG top,
		LONG right,
		LONG bottom
		)
	{
		m_rect = CD3DX12_RECT(left, top, right, bottom);
	}

	const CD3DX12_RECT& CDX12Scissor::GetScissorRect() const
	{
		return m_rect;
	}

}	// namespace ng
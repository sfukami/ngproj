/*!
* @file		appRootSignatureDescSprite.cpp
* @brief	ルートシグネチャ記述子
* @date		2020-07-24
* @author	s.fukami
*/

#include "appRootSignatureDescSprite.h"

namespace app
{
	CRootSignatureDescSprite::CRootSignatureDescSprite()
		: m_cbRange(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0)
		, m_texRange(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0)
	{
		m_rootParams[0].InitAsDescriptorTable(1, &m_cbRange, D3D12_SHADER_VISIBILITY_VERTEX);
		m_rootParams[1].InitAsDescriptorTable(1, &m_texRange, D3D12_SHADER_VISIBILITY_PIXEL);

		m_samplerDesc.Init(0, D3D12_FILTER_MIN_MAG_MIP_POINT);

		Init(NG_ARRAY_SIZE(m_rootParams), m_rootParams,
			1, &m_samplerDesc,
			D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT
			);
	}

}	// namespace app
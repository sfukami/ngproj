/*!
* @file		ngDX12VertexLayout.cpp
* @brief	DX12頂点レイアウト
* @date		2019-08-12
* @author	s.fukami
*/

#include <d3d12.h>
#include <dxgiformat.h>
#include "ngLibCore/common/ngCommon.h"
#include "ngDX12VertexLayout.h"

namespace ng
{
	//! 頂点レイアウト 入力エレメント生成
	#define MAKE_VERTELEM(_semantic, _semanticIndex, _format) \
		{_semantic, _semanticIndex, _format, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0}

	//! 頂点レイアウト配列
	static const DX12VertexLayout g_inputLayout[] = {
		// SPRITE
		{
			{
				MAKE_VERTELEM("POSITION",	0,	DXGI_FORMAT_R32G32B32_FLOAT),
				MAKE_VERTELEM("COLOR",		0,	DXGI_FORMAT_R32G32B32A32_FLOAT),
				MAKE_VERTELEM("TEXCOORD",	0,	DXGI_FORMAT_R32G32_FLOAT),
			}, 3
		},
		// STATIC
		{
			{
				MAKE_VERTELEM("POSITION",	0,	DXGI_FORMAT_R32G32B32_FLOAT),
				MAKE_VERTELEM("NORMAL",		0,	DXGI_FORMAT_R32G32B32_FLOAT),
				MAKE_VERTELEM("TEXCOORD",	0,	DXGI_FORMAT_R32G32_FLOAT),
			}, 3
		},
		// SKELETAL
		{
			{
				MAKE_VERTELEM("POSITION",	0,	DXGI_FORMAT_R32G32B32_FLOAT),
				MAKE_VERTELEM("NORMAL",		0,	DXGI_FORMAT_R32G32B32_FLOAT),
				MAKE_VERTELEM("TEXCOORD",	0,	DXGI_FORMAT_R32G32_FLOAT),
			}, 3
		},
	};

	const DX12VertexLayout& DX12GetVertexLayout(eVertexLayout layout)
	{
		NG_ASSERT_COMPARE(layout, <, eVertexLayout::NUM, "頂点レイアウトのインデックスが範囲外です.");
		
		return g_inputLayout[ UnderlyingCast(layout) ];
	}

}	// namespace ng
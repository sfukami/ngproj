/*!
* @file		ngDX12VertexLayout.h
* @brief	DX12頂点レイアウト
* @date		2019-08-12
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_VERTEX_LAYOUT_H__
#define __NG_GRAPHIC_DX12_VERTEX_LAYOUT_H__

#include <d3d12.h>
#include "ngLibGraphic/graphic/dx12/common/ngDX12Const.h"

namespace ng
{
	/*! 頂点レイアウト */
	enum class eVertexLayout : u32
	{
		SPRITE,		//!< スプライト
		STATIC,		//!< スタティックメッシュ
		SKELETAL,	//!< スケルタルメッシュ
		
		NUM
	};

	/*! 頂点レイアウト */
	struct DX12VertexLayout
	{
		D3D12_INPUT_ELEMENT_DESC descs[ NG_DX12_MESH_INPUT_ELEMENT_DESC_MAX ];
		u32 descNum;
	};

	/*!
	* @brief					DX12頂点レイアウト取得
	*/
	const DX12VertexLayout& DX12GetVertexLayout(eVertexLayout layout);

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_VERTEX_LAYOUT_H__
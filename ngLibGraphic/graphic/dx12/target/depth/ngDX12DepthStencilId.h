/*!
* @file		ngDX12DepthStencilId.h
* @brief	DX12深度ステンシルID
* @date		2019-08-14
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_DEPTH_STENCIL_ID_H__
#define __NG_GRAPHIC_DX12_DEPTH_STENCIL_ID_H__

namespace ng
{
	/*!
	* @brief					DX12深度ステンシルID
	*/
	enum class eDX12DepthStencilId : u32
	{
		ID_01,
		ID_02,
		ID_03,
		ID_04,

		ID_NUM,
		ID_BEGIN	= ID_01,
		ID_END		= ID_NUM-1,
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_DEPTH_STENCIL_ID_H__
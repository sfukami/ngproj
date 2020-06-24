/*!
* @file		ngDX12RenderTargetId.h
* @brief	DX12レンダーターゲットID
* @date		2018-05-12
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_RENDER_TARGET_ID_H__
#define __NG_GRAPHIC_DX12_RENDER_TARGET_ID_H__

namespace ng
{
	/*!
	* DX12レンダーターゲットID
	*/
	enum class eDX12RenderTargetId : u32
	{
		ID_01,
		ID_02,
		ID_03,
		ID_04,
		ID_05,
		ID_06,
		ID_07,
		ID_08,

		ID_NUM,
		ID_BEGIN	= ID_01,
		ID_END		= ID_NUM - 1,
		ID_BACK_BUFFER_01	= ID_01,	//!< バックバッファ1
		ID_BACK_BUFFER_02	= ID_02,	//!< バックバッファ2
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_RENDER_TARGET_ID_H__
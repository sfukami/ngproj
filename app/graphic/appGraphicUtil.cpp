/*!
* @file		appGraphicUtil.cpp
* @brief	グラフィック ユーティリティ
* @date		2020-07-19
* @author	s.fukami
*/

#include "ngLibGraphic/graphic/dx12/ngDX12.h"
#include "appGraphicUtil.h"

namespace app
{
namespace GraphicUtil
{
	ng::CDX12CommandList* GetDX12CommandList(eGraphicCommandListId id)
	{
		return ng::DX12Util::GetCommandList(static_cast<ng::u32>(id));
	}
	
}	// namespace GraphicUtil
}	// namespace app
/*!
* @file		appGraphicUtil.h
* @brief	グラフィック ユーティリティ
* @date		2020-07-19
* @author	s.fukami
*/

#ifndef __APP_GRAPHIC_UTIL_H__
#define __APP_GRAPHIC_UTIL_H__

#include "command/appGraphicCommandListId.h"

namespace ng
{
	class CDX12CommandList;
}

namespace app
{
namespace GraphicUtil
{
	/*!
	* @brief					DX12コマンドリスト取得
	* @param id					グラフィックコマンドリストID
	*/
	ng::CDX12CommandList* GetDX12CommandList(eGraphicCommandListId id);

}	// namespace GraphicUtil
}	// namespace app

#endif	// __APP_GRAPHIC_UTIL_H__
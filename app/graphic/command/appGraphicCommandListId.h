/*!
* @file		appGraphicCommandListId.h
* @brief	グラフィックコマンドリストID
* @date		2020-07-04
* @author	s.fukami
*/

#ifndef __APP_GRAPHIC_COMMAND_LIST_H__
#define __APP_GRAPHIC_COMMAND_LIST_H__

namespace app
{
	/*!
	* @brief					グラフィックコマンドリストID
	*/
	enum class eGraphicCommandListId : unsigned int
	{
		ID_0,
		ID_1,

		NUM,
		MAIN	= ID_0,		//!< メイン
		IMGUI	= ID_1,		//!< ImGui
	};

}	// namespace app

#endif	// __APP_GRAPHIC_COMMAND_LIST_H__
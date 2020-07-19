/*!
* @file		appRenderParam.h
* @brief	描画パラメータ
* @date		2020-07-19
* @author	s.fukami
*/

#ifndef __APP_RENDER_PARAM_H__
#define __APP_RENDER_PARAM_H__

#include "ngLibGraphic/render/ngRenderParam.h"
#include "../command/appGraphicCommandListId.h"

namespace app
{
	/*!
	* @brief					描画パラメータ
	*/
	struct RenderParam : public ng::RenderParam
	{
		RenderParam()
			: cmdListId(eGraphicCommandListId::MAIN)
		{ }

		eGraphicCommandListId cmdListId;	//!< グラフィックコマンドリストID
	};

}	// namespace app

#endif	// __APP_RENDER_PARAM_H__
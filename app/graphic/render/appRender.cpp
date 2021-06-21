/*!
* @file		appRender.cpp
* @brief	描画オブジェクト インターフェース
* @date		2021-06-21
* @author	s.fukami
*/

#include "appRender.h"

namespace app
{
	IRender::IRender()
	{
	}
	IRender::~IRender()
	{
	}

	void IRender::Render(const RenderParam& param)
	{
		if(!IsEnable()) return;

		_render(param);
	}

}	// namespace app
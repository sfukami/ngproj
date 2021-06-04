/*!
* @file		appDebugMenuItem.cpp
* @brief	デバッグメニュー項目 基底クラス
* @date		2021-06-01
* @author	s.fukami
*/

#include "appDebugMenuItem.h"

namespace app
{
	CDebugMenuItem::CDebugMenuItem()
	{
	}
	CDebugMenuItem::~CDebugMenuItem()
	{
	}

	void CDebugMenuItem::Update()
	{
		_update();
	}

	void CDebugMenuItem::Render()
	{
		_render();
	}

	void CDebugMenuItem::_update()
	{
	}

	void CDebugMenuItem::_render()
	{
	}

}	// namespace app
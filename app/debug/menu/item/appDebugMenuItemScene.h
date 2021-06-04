/*!
* @file		appDebugMenuItemScene.h
* @brief	デバッグメニュー項目 シーン関連
* @date		2021-06-01
* @author	s.fukami
*/

#ifndef __APP_DEBUG_MENU_ITEM_SCENE_H__
#define __APP_DEBUG_MENU_ITEM_SCENE_H__

#include "appDebugMenuItem.h"

namespace app
{
	/*!
	* @brief					デバッグメニュー項目 シーン関連
	*/
	class CDebugMenuItemScene : public CDebugMenuItem
	{
	public:
		CDebugMenuItemScene();
		~CDebugMenuItemScene();

	private:
		/*! 更新 */
		void _update();

		/*! 描画 */
		void _render();

	private:
		int m_sceneCategory;	//!< シーンの分類
	};

}	// namespace app

#endif	// __APP_DEBUG_MENU_ITEM_SCENE_H__
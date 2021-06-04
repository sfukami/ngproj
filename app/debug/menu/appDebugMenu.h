/*!
* @file		appDebugMenu.h
* @brief	デバッグメニュー
* @date		2021-05-31
* @author	s.fukami
*/

#ifndef __APP_DEBUG_MENU_H__
#define __APP_DEBUG_MENU_H__

#include "ngLibCore/container/list/ngIntrusiveList.h"
#include "item/appDebugMenuItem.h"
#include "item/appDebugMenuItemScene.h"

namespace app
{
	/*!
	* @brief					デバッグメニュー
	*/
	class CDebugMenu
	{
	public:
		CDebugMenu();
		~CDebugMenu();

		/*!
		* @brief					セットアップ
		*/
		void Setup();

		/*!
		* @brief					シャットダウン
		*/
		void Shutdown();

		/*!
		* @brief					更新
		*/
		void Update();

		/*!
		* @brief					描画
		*/
		void Render();

	private:
		using ItemList = ng::CIntrusiveList<CDebugMenuItem>;	//!< デバッグメニュー項目リスト

	private:
		ItemList m_itemList;	//!< デバッグメニュー項目リスト
		bool m_isOpened;	//!< デバッグメニューが開いているか
		bool m_isFirstUncollapsed;	//!< 初回の折り畳み展開されたか
		// メニュー項目
		CDebugMenuItemScene m_itemScene;	//!< デバッグメニュー項目 シーン関連
	};

}	// namespace app

#endif	// __APP_DEBUG_MENU_H__
/*!
* @file		appDebugMenuItem.h
* @brief	デバッグメニュー項目 基底クラス
* @date		2021-06-01
* @author	s.fukami
*/

#ifndef __APP_DEBUG_MENU_ITEM_H__
#define __APP_DEBUG_MENU_ITEM_H__

#include "ngLibCore/container/list/intrusive/ngIntrusiveListNode.h"

namespace app
{
	/*!
	* @brief					デバッグメニュー項目
	*/
	class CDebugMenuItem : public ng::CIntrusiveListNode<CDebugMenuItem>
	{
	public:
		CDebugMenuItem();
		virtual ~CDebugMenuItem();

		/*!
		* @brief					更新
		*/
		void Update();

		/*!
		* @brief					描画
		*/
		void Render();

	private:
		/*! 更新 */
		virtual void _update();

		/*! 描画 */
		virtual void _render();
	};

}	// namespace app

#endif	// __APP_DEBUG_MENU_ITEM_H__
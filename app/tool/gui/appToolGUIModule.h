/*!
* @file		appToolGUIModule.h
* @brief	ツールGUI機能
* @date		2020-07-06
* @author	s.fukami
*/

#ifndef __APP_TOOL_GUI_MODULE_H__
#define __APP_TOOL_GUI_MODULE_H__

#include "ngLibCore/traits/ngNonInstantiable.h"

namespace app
{
	class CToolGUI;
}

namespace app
{
	/*!
	* @brief					ツールGUI機能
	*/
	class CToolGUIModule : public ng::CNonInstantiable
	{
		friend class CApplication;

	public:
		/*!
		* @brief					ツールGUI描画
		*/
		static void RenderToolGUI();

	private:
		/*! ツールGUIのインスタンスを設定 */
		static void SetToolGUI(CToolGUI* pToolGUI);

		/*! 有効か */
		static bool _isValid();
		
	private:
		static CToolGUI* s_pToolGUI;	//!< ツールGUIへの参照
	};

}	// namespace app

#endif	// __APP_TOOL_GUI_MODULE_H__
/*!
* @file		ngImGuiComboItem.h
* @brief	ImGui コンボボックス項目
* @date		2021-06-04
* @author	s.fukami
*/

#ifndef __NG_APP_IMGUI_COMBO_ITEM_H__
#define __NG_APP_IMGUI_COMBO_ITEM_H__

#include "ngLibCore/action/ngAction.h"

namespace ng
{
	/*!
	* @brief					ImGui コンボボックス項目
	*/
	class NG_DECL CComboItem
	{
	public:
		using ActionType = ng::CAction<void>;	//!< 登録する関数のアクション

	public:
		/*!
		* @brief					コンストラクタ
		* @param name				名称
		* @param pFunc				登録する関数
		*/
		CComboItem(const char* name, ActionType::FuncType pFunc);
		virtual ~CComboItem();

		/*!
		* @brief					登録した関数を実行
		*/
		void DoAction();
		void DoAction() const;

		/*! 名称取得 */
		const char* GetName() const;

	private:
		char m_name[256];	//!< 名前
		ActionType m_action;	//!< 登録した関数のアクション
	};

	/*! ImGuiコンボボックス 項目取得関数 */
	NG_DECL bool ComboItemGetter(void* data, int idx, const char** out_text);

}	// namespace ng

#endif	// __NG_APP_IMGUI_COMBO_ITEM_H__
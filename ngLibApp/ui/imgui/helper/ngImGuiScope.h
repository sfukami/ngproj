/*!
* @file		ngImGuiScope.h
* @brief	ImGui各種スコープ
* @date		2021-05-31
* @author	s.fukami
*/

#ifndef __NG_APP_IMGUI_SCOPE_H__
#define __NG_APP_IMGUI_SCOPE_H__

#include "../imgui_src/imgui.h"

namespace ng
{
	/*!
	* @brief					ImGuiスコープ メニューバー
	*/
	class NG_DECL CImGuiMenuBarScope
	{
	public:
		CImGuiMenuBarScope();
		~CImGuiMenuBarScope();

		/*! bool型変換演算子 */
		explicit operator bool() const;

	private:
		bool m_enable;	//!< 有効か
	};

	/*!
	* @brief					ImGuiスコープ メニュー
	*/
	class NG_DECL CImGuiMenuScope
	{
	public:
		CImGuiMenuScope(const char* label, bool enabled = true);
		~CImGuiMenuScope();

		/*! bool型変換演算子 */
		explicit operator bool() const;

	private:
		bool m_enable;	//!< 有効か
	};

	/*!
	* @brief					ImGuiスコープ ツリー
	*/
	class NG_DECL CImGuiTreeScope
	{
	public:
		CImGuiTreeScope(const char* label, bool isOpened = false);
		~CImGuiTreeScope();

		/*! bool型変換演算子 */
		explicit operator bool() const;

	private:
		bool m_enable;	//!< 有効か
	};

	/*!
	* @brief					ImGuiスコープ 子ウィンドウ
	*/
	class NG_DECL CImGuiChildWindowScope
	{
	public:
		CImGuiChildWindowScope(const char* id, const ImVec2& pos, bool border = false, ImGuiWindowFlags flags = 0);
		~CImGuiChildWindowScope();

		/*! bool型変換演算子 */
		explicit operator bool() const;

	private:
		bool m_enable;	//!< 有効か
	};

}	// namespace ng

#endif	// __NG_APP_IMGUI_SCOPE_H__
/*!
* @file		ngImGuiScope.cpp
* @brief	ImGui各種スコープ
* @date		2021-05-31
* @author	s.fukami
*/

#include "ngImGuiScope.h"
#include "../imgui_src/imgui.h"

namespace ng
{
	CImGuiMenuBarScope::CImGuiMenuBarScope()
	{
		m_enable = ImGui::BeginMenuBar();
	}
	CImGuiMenuBarScope::~CImGuiMenuBarScope()
	{
		if(m_enable) {
			ImGui::EndMenuBar();
		}
	}

	CImGuiMenuBarScope::operator bool() const
	{
		return m_enable;
	}

	CImGuiMenuScope::CImGuiMenuScope(const char* label, bool enabled)
	{
		m_enable = ImGui::BeginMenu(label, enabled);
	}
	CImGuiMenuScope::~CImGuiMenuScope()
	{
		if(m_enable) {
			ImGui::EndMenu();
		}
	}

	CImGuiMenuScope::operator bool() const
	{
		return m_enable;
	}

	CImGuiTreeScope::CImGuiTreeScope(const char* label, bool isOpened)
	{
		ImGui::SetNextTreeNodeOpen(isOpened, ImGuiCond_::ImGuiCond_Once);
		m_enable = ImGui::TreeNode(label);
	}
	CImGuiTreeScope::~CImGuiTreeScope()
	{
		if(m_enable) {
			ImGui::TreePop();
		}
	}

	CImGuiTreeScope::operator bool() const
	{
		return m_enable;
	}

	CImGuiChildWindowScope::CImGuiChildWindowScope(const char* id, const ImVec2& pos, bool border, ImGuiWindowFlags flags)
	{
		m_enable = ImGui::BeginChild(id, pos, border, flags);
	}
	CImGuiChildWindowScope::~CImGuiChildWindowScope()
	{
		// ※成否問わず呼び出す
		//if(m_enable)
		{
			ImGui::EndChild();
		}
	}

	CImGuiChildWindowScope::operator bool() const
	{
		return m_enable;
	}

}	// namespace ng
/*!
* @file		ngImGuiWrapper.cpp
* @brief	ImGuiラッパー
* @date		2021-05-26
* @author	s.fukami
*/

#include "ngLibApp/common/ngCommon.h"
#include "ngImGuiWrapper.h"
#include "../imgui_src/imgui.h"

namespace ng
{
	int CImGui::m_styleColorCount = 0;

	bool CImGui::BeginWindow(
		const char* name, const ImVec2& pos, const ImVec2& size, bool collapsed, bool* pIsOpened, ImGuiWindowFlags flags
		)
	{
		ImGui::SetNextWindowPos(pos, ImGuiCond_::ImGuiCond_Once);
		ImGui::SetNextWindowSize(size, ImGuiCond_::ImGuiCond_Once);
		ImGui::SetNextWindowCollapsed(collapsed, ImGuiCond_::ImGuiCond_Once);

		return ImGui::Begin(name, pIsOpened, flags);
	}
	void CImGui::EndWindow()
	{
		ImGui::End();
	}

	bool CImGui::BeginChildWindow(const char* id, const ImVec2& pos, bool border, ImGuiWindowFlags flags)
	{
		return ImGui::BeginChild(id, pos, border, flags);
	}
	void CImGui::EndChildWindow()
	{
		ImGui::EndChild();
	}

	void CImGui::PushStyleColor(ImGuiCol index, ImU32 color)
	{
		ImGui::PushStyleColor(index, color);
		m_styleColorCount++;
	}
	void CImGui::PushStyleColor(ImGuiCol index, const ImVec4& color)
	{
		ImGui::PushStyleColor(index, color);
		m_styleColorCount++;
	}
	void CImGui::PushStyleColor(ImGuiCol index, eColorCode code)
	{
		PushStyleColor(index, UnderlyingCast(code));
		m_styleColorCount++;
	}
	void CImGui::PopStyleColor(int count)
	{
		if(count > m_styleColorCount) count = m_styleColorCount;

		ImGui::PopStyleColor(count);
		m_styleColorCount -= count;
	}
	void CImGui::ClearStyleColor()
	{
		PopStyleColor(m_styleColorCount);
	}

}	// namespace ng
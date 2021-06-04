/*!
* @file		ngImGuiWrapper.h
* @brief	ImGuiラッパー
* @date		2021-05-26
* @author	s.fukami
*/

#ifndef __NG_APP_IMGUI_WRAPPER_H__
#define __NG_APP_IMGUI_WRAPPER_H__

#include "ngLibCore/traits/ngNonInstantiable.h"
#include "ngLibCore/color/ngColorCode.h"
#include "../imgui_src/imgui.h"

namespace ng
{
	/*!
	* @brief					ImGuiラッパー
	*/
	class CImGui : public CNonInstantiable
	{
	public:
		/*!
		* @brief					Window関連
		*/
		static bool BeginWindow(
			const char* name, const ImVec2& pos, const ImVec2& size, bool collapsed = false, bool* pIsOpened = nullptr, ImGuiWindowFlags flags = 0
			);
		static void EndWindow();

		static bool BeginChildWindow(const char* id, const ImVec2& pos, bool border = false, ImGuiWindowFlags flags = 0);
		static void EndChildWindow();

		/*!
		* @brief					StyleColor関連
		*/
		static void PushStyleColor(ImGuiCol index, ImU32 color);
		static void PushStyleColor(ImGuiCol index, const ImVec4& color);
		static void PushStyleColor(ImGuiCol index, eColorCode code);
		static void PopStyleColor(int count = 1);
		static void ClearStyleColor();

	private:
		static int m_styleColorCount;	//!< StyleColorプッシュカウンタ
	};

}	// namespace ng

#endif	// __NG_APP_IMGUI_WRAPPER_H__
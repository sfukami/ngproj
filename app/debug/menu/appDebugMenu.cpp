/*!
* @file		appDebugMenu.cpp
* @brief	デバッグメニュー
* @date		2021-05-31
* @author	s.fukami
*/

#include "ngLibApp/ui/imgui/ngImGui.h"
#include "app/input/appInputModule.h"
#include "appDebugMenu.h"

namespace app
{
	CDebugMenu::CDebugMenu()
		: m_isOpened(true)
		, m_isFirstUncollapsed(false)
	{
	}
	CDebugMenu::~CDebugMenu()
	{
	}

	void CDebugMenu::Setup()
	{
		m_itemList.PushBack(m_itemScene);
	}

	void CDebugMenu::Shutdown()
	{
		m_itemList.Clear();
	}

	void CDebugMenu::Update()
	{
		// キー入力によるデバッグメニュー表示切替
		if(CInputModule::IsValidKeyboard()) {
			if(CInputModule::CheckKeyboardInput(ng::eKeyCode::D, ng::eInputState::PRESSED)) {
				m_isOpened = !m_isOpened;
			}
		}

		if(m_isOpened) {
			for(ItemList::NodeType* pNode = m_itemList.Begin(); pNode != m_itemList.End(); pNode = pNode->GetNext())
			{
				pNode->GetElem().Update();
			}
		}
	}

	void CDebugMenu::Render()
	{
		// デバッグメニュー ウィンドウ表示
		if(m_isOpened) {
			ng::CImGui::BeginWindow(
				"DebugMenu", ImVec2(5, 5), ImVec2(100, 100), true, &m_isOpened, ImGuiWindowFlags_MenuBar
				);

			// 初回の折り畳み展開時はウィンドウサイズを拡張する
			if(!m_isFirstUncollapsed) {
				if(!ImGui::IsWindowCollapsed()) {
					m_isFirstUncollapsed = true;
					ImGui::SetWindowSize(ImVec2(300, 450));
				}
			}

			for(ItemList::NodeType* pNode = m_itemList.Begin(); pNode != m_itemList.End(); pNode = pNode->GetNext())
			{
				pNode->GetElem().Render();
			}

			ng::CImGui::EndWindow();
		}
	}

}	// namespace app
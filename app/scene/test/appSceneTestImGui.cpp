/*!
* @file		appSceneImGuiTest.cpp
* @brief	シーン ImGuiテスト
* @date		2020-06-30
* @author	s.fukami
*/

#include "app/common/appCommon.h"
#include "appSceneTestImGui.h"
#include "../../memory/appMemoryModule.h"
#include "../../graphic/appGraphicModule.h"
#include "../../graphic/pipeline/appGraphicPipelineDefault.h"
#include "ngLibApp/ui/imgui/ngImGui.h"

namespace app
{
	CSceneTestImGui::CSceneTestImGui()
	{
	}
	CSceneTestImGui::~CSceneTestImGui()
	{
	}

	bool CSceneTestImGui::Initialize()
	{
		m_pPipeline = NG_NEW(APP_MEMALLOC_APPLICATION) CGraphicPipelineDefault();

		if(m_pPipeline->Initialize()) {
			CGraphicModule::SetGraphicPipeline(m_pPipeline);
		} else {
			NG_ERRLOG("Game", "グラフィックパイプラインの初期化に失敗しました.");
			NG_SAFE_DELETE(APP_MEMALLOC_APPLICATION, m_pPipeline);
			return false;
		}

		return true;
	}

	void CSceneTestImGui::Update(float deltaTime)
	{
	}

	void CSceneTestImGui::Render()
	{
		_renderGUIWindow();
	}

	void CSceneTestImGui::Finalize()
	{
		if(m_pPipeline != nullptr) {
			NG_SAFE_DELETE(APP_MEMALLOC_APPLICATION, m_pPipeline);
		}
	}

	void CSceneTestImGui::_renderGUIWindow()
	{
		// ImGui で遊ぶ
		// 参考:https://qiita.com/Ushio/items/446d78c881334919e156

		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.f, 0.7f, 0.2f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.f, 0.3f, 0.1f, 1.f));

		ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_::ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(320, 400), ImGuiCond_::ImGuiCond_Once);

		// ウィンドウ
		ImGui::Begin("window", nullptr, ImGuiWindowFlags_MenuBar);

		// メニュー
		if(ImGui::BeginMenuBar()) {
			if(ImGui::BeginMenu("File")) {
				if(ImGui::MenuItem("Save")) {
				}
				if(ImGui::MenuItem("Load")) {
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::Text("test");

		// スライダー & テキストボックス
		ImGui::SetNextTreeNodeOpen(true, ImGuiCond_::ImGuiCond_Once);
		if(ImGui::TreeNode("tree")) {
			static float slider = 0;
			static char text[8] = "";

			ImGui::SliderFloat("slider", &slider, 0.f, 1.f);
			ImGui::InputText("textbox", text, sizeof(text));
			if(ImGui::Button("clear")) {
				slider = 0;
				::strcpy_s(text, "");
			}

			ImGui::TreePop();
		}

		// リスト
		{
			static int count = 0;

			if(ImGui::Button("add")) {
				count++;
			}
			if(ImGui::Button("remove")) {
				if(count > 0) count--;
			}

			ImGui::BeginChild("child", ImVec2(250, 100), true, ImGuiWindowFlags_NoTitleBar);
			for(int i = 0; i < count; i++)
			{
				ImGui::Text("item [%d]", i);
			}
			ImGui::EndChild();
		}

		// チェックボックス & ラジオボタン
		{
			static bool isEnable = false;
			ImGui::Checkbox("enable", &isEnable);

			if(isEnable) {
				enum {
					MODE_1, MODE_2,
				};
				static int mode = MODE_1;
				ImGui::RadioButton("mode 1", &mode, MODE_1);
				ImGui::SameLine();
				ImGui::RadioButton("mode 2", &mode, MODE_2);
			}
		}

		ImGui::End();

		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
	}

}	// namespace app
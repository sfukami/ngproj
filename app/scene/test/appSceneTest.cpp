/*!
* @file		appSceneTest.cpp
* @brief	シーン テスト
* @date		2020-06-30
* @author	s.fukami
*/

#include "app/common/appCommon.h"
#include "appSceneTest.h"
#include "../../memory/appMemoryModule.h"
#include "../../input/appInputModule.h"
#include "../../graphic/appGraphicModule.h"
// test
#include "../../graphic/pipeline/test/appGraphicPipelineClearBuffer.h"
#include "../../graphic/pipeline/test/appGraphicPipelinePolygon.h"
#include "ngLibApp/ui/imgui/imgui_src/imgui.h"

namespace app
{
	CSceneTest::CSceneTest()
	{
	}
	CSceneTest::~CSceneTest()
	{
	}

	bool CSceneTest::Initialize()
	{
		m_pPipeline = NG_NEW(APP_MEMALLOC_APPLICATION) 
			//CGraphicPipelineClearBuffer()
			CGraphicPipelinePolygon()
			;
		if(m_pPipeline->Initialize()) {
			CGraphicModule::SetGraphicPipeline(m_pPipeline);
		} else {
			NG_ERRLOG("Game", "グラフィックパイプラインの初期化に失敗しました.");
			NG_SAFE_DELETE(APP_MEMALLOC_APPLICATION, m_pPipeline);
			return false;
		}

		return true;
	}

	void CSceneTest::Update(float deltaTime)
	{
		// test
		{
			// Keyboard
			if(CInputModule::CheckKeyboardInput(ng::eKeyCode::A, ng::eInputState::PRESSED)) {
				ng::DPrintf("key A pressed.\n");
			}
			if(CInputModule::CheckKeyboardInput(ng::eKeyCode::A, ng::eInputState::RELEASED)) {
				ng::DPrintf("key A released.\n");
			}
			if(CInputModule::CheckKeyboardInput(ng::eKeyCode::A, ng::eInputState::HELD)) {
				ng::DPrintf("key A held.\n");
			}
			// Mouse
			if(CInputModule::CheckMouseInput(ng::eMouseCode::LEFT, ng::eInputState::PRESSED)) {
				ng::DPrintf("button Left pressed.\n");
			}
			if(CInputModule::CheckMouseInput(ng::eMouseCode::LEFT, ng::eInputState::RELEASED)) {
				ng::DPrintf("button Left released.\n");
			}
			if(CInputModule::CheckMouseInput(ng::eMouseCode::LEFT, ng::eInputState::HELD)) {
				ng::DPrintf("button Left held.\n");
			}
		}
	}

	void CSceneTest::Render()
	{
		//test
		ImGui::SetNextWindowSize(ImVec2(320, 100), ImGuiCond_::ImGuiCond_Once);
		ImGui::Begin("config 1");
		ImGui::Text("fugafuga");
		ImGui::End();
	}

	void CSceneTest::Finalize()
	{
		if(m_pPipeline != nullptr) {
			NG_SAFE_DELETE(APP_MEMALLOC_APPLICATION, m_pPipeline);
		}
	}

}	// namespace app
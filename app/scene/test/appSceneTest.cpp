/*!
* @file		appSceneTest.cpp
* @brief	シーン テスト
* @date		2020-06-30
* @author	s.fukami
*/

#include "appSceneTest.h"

// test
#include "ngLibCore/system/ngSysUtil.h"
#include "../../graphic/pipeline/test/appGraphicPipelineClearBuffer.h"
#include "../../graphic/pipeline/test/appGraphicPipelinePolygon.h"
#include "../../graphic/appGraphicModule.h"
#include "../../input/appInputModule.h"

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
		// TODO: 仮にシステムアロケータを使用する
		m_pPipeline = NG_NEW(NG_SYSALLOC_GRAPHIC) CGraphicPipelinePolygon();
		if(m_pPipeline->Initialize()) {
			CGraphicModule::SetGraphicPipeline(m_pPipeline);
		} else {
			NG_ERRLOG("Game", "グラフィックパイプラインの初期化に失敗しました.");
			NG_SAFE_DELETE(NG_SYSALLOC_GRAPHIC, m_pPipeline);
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
	}

	void CSceneTest::Finalize()
	{
		if(m_pPipeline != nullptr) {
			NG_SAFE_DELETE(NG_SYSALLOC_GRAPHIC, m_pPipeline);
		}
	}

}	// namespace app
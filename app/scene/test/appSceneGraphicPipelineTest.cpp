/*!
* @file		appSceneGraphicPipelineTest.h
* @brief	シーン グラフィックパイプラインテスト
* @date		2021-05-10
* @author	s.fukami
*/

#include "app/common/appCommon.h"
#include "appSceneGraphicPipelineTest.h"
#include "../../memory/appMemoryModule.h"
#include "../../graphic/appGraphicModule.h"
// test
#include "../../graphic/pipeline/test/appGraphicPipelineClearBuffer.h"
#include "../../graphic/pipeline/test/appGraphicPipelinePolygon.h"

namespace app
{
	CSceneGraphicPipelineTest::CSceneGraphicPipelineTest()
	{
	}
	CSceneGraphicPipelineTest::~CSceneGraphicPipelineTest()
	{
	}

	bool CSceneGraphicPipelineTest::Initialize()
	{
		m_pPipeline = NG_NEW(APP_GET_MEMALLOC(APPLICATION))
			//CGraphicPipelineClearBuffer()
			CGraphicPipelinePolygon()
			;

		// グラフィックパイプライン初期化
		if(m_pPipeline->Initialize()) {
			CGraphicModule::SetGraphicPipeline(m_pPipeline);
		} else {
			NG_ERRLOG("Game", "グラフィックパイプラインの初期化に失敗しました.");
			NG_SAFE_DELETE(APP_GET_MEMALLOC(APPLICATION), m_pPipeline);
			return false;
		}

		return true;
	}

	void CSceneGraphicPipelineTest::Update(float deltaTime)
	{
	}

	void CSceneGraphicPipelineTest::Render()
	{
	}

	void CSceneGraphicPipelineTest::Finalize()
	{
		if(m_pPipeline != nullptr) {
			NG_SAFE_DELETE(APP_GET_MEMALLOC(APPLICATION), m_pPipeline);
		}
	}

}	// namespace app
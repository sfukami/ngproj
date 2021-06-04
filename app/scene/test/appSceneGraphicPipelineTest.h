/*!
* @file		appSceneGraphicPipelineTest.h
* @brief	シーン グラフィックパイプラインテスト
* @date		2021-05-10
* @author	s.fukami
*/

#ifndef __APP_SCENE_GRAPHIC_PIPELINE_TEST_H__
#define __APP_SCENE_GRAPHIC_PIPELINE_TEST_H__

#include "../appScene.h"

namespace app
{
	class CGraphicPipeline;
}

namespace app
{
	/*!
	* @brief					シーン テスト
	*/
	class CSceneGraphicPipelineTest : public IScene
	{
	public:
		CSceneGraphicPipelineTest();
		~CSceneGraphicPipelineTest();

		/*!
		* @brief					初期化
		* @return					成否
		*/
		bool Initialize();

		/*!
		* @brief					更新
		* @param deltaTime			フレーム更新間隔
		*/
		void Update(float deltaTime);

		/*!
		* @brief					描画
		*/
		void Render();

		/*!
		* @brief					終了処理
		*/
		void Finalize();

		/*!
		* @brief					名称取得
		*/
		const char* GetName() const;
		
	private:
		CGraphicPipeline* m_pPipeline;	//!< グラフィックパイプライン
	};

}	// namespace app

#endif	// __APP_SCENE_GRAPHIC_PIPELINE_TEST_H__
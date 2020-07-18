﻿/*!
* @file		appSceneTestGame.h
* @brief	シーン ゲームテスト
* @date		2020-07-15
* @author	s.fukami
*/

#ifndef __APP_SCENE_TEST_GAME_H__
#define __APP_SCENE_TEST_GAME_H__

#include "../appScene.h"
#include "app/game/appGame.h"

namespace app
{
	class CGraphicPipeline;
}

namespace app
{
	/*!
	* @brief					シーン ゲームテスト
	*/
	class CSceneTestGame : public IScene
	{
	public:
		CSceneTestGame();
		~CSceneTestGame();

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

	private:
		CGraphicPipeline* m_pPipeline;	//!< グラフィックパイプライン
		CGame m_game;	//!< ゲーム
	};

}	// namespace app

#endif	// __APP_SCENE_TEST_GAME_H__
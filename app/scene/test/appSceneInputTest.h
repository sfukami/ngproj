/*!
* @file		appSceneInputTest.h
* @brief	シーン 入力テスト
* @date		2021-05-10
* @author	s.fukami
*/

#ifndef __APP_SCENE_INPUT_TEST_H__
#define __APP_SCENE_INPUT_TEST_H__

#include "../appScene.h"

namespace app
{
	/*!
	* @brief					シーン 入力テスト
	*/
	class CSceneInputTest : public IScene
	{
	public:
		CSceneInputTest();
		~CSceneInputTest();

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
	};

}	// namespace app

#endif	// __APP_SCENE_INPUT_TEST_H__
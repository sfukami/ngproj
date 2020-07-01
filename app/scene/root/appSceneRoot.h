/*!
* @file		appSceneRoot.h
* @brief	シーン ルート
* @date		2020-06-30
* @author	s.fukami
*/

#ifndef __APP_SCENE_ROOT_H__
#define __APP_SCENE_ROOT_H__

#include "../appScene.h"

namespace app
{
	/*!
	* @brief					シーン ルート
	*/
	class CSceneRoot : public IScene
	{
	public:
		CSceneRoot();
		~CSceneRoot();

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

#endif	// __APP_SCENE_ROOT_H__
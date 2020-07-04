/*!
* @file		appSceneModule.h
* @brief	シーン機能
* @date		2020-07-01
* @author	s.fukami
*/

#ifndef __APP_SCENE_MODULE_H__
#define __APP_SCENE_MODULE_H__

#include "appSceneId.h"
#include "appSceneManager.h"

namespace app
{
	class CSceneManager;
}

namespace app
{
	/*!
	* @brief					シーン機能
	*/
	class CSceneModule
	{
		friend class CGame;

	public:
		CSceneModule() = delete;
		~CSceneModule() = delete;
		/*!
		* @brief					シーン切り替え（フレーム終了時）
		* @param sceneId			シーンID
		* @tparam scenePtr			登録するシーン
		*/
		static void RequestChangeScene(eSceneId sceneId, ng::CSharedPtr<IScene>& scenePtr);

		/*!
		* @brief					シーン切り替え
		* @param sceneId			シーンID
		* @tparam scenePtr			登録するシーン
		* @return					成否
		*/
		static bool ChangeScene(eSceneId sceneId, ng::CSharedPtr<IScene>& scenePtr);

	private:
		/*! シーン管理のインスタンスを設定 */
		static void SetSceneManager(CSceneManager* pSceneMngr);

		/*! 有効か */
		static bool _isValid();
		
	private:
		static CSceneManager* s_pSceneMngr;	//!< シーン管理への参照
	};

}	// namespace app

#endif	// __APP_SCENE_MODULE_H__
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
		* @brief					シーン切り替え
		* @tparam Scene				登録するシーン
		* @param sceneId			シーンID
		* @return					成否
		*/
		template <class Scene>
		static bool ChangeScene(eSceneId sceneId);

	private:
		/*! シーン管理のインスタンスを設定 */
		static void SetSceneManager(CSceneManager* pSceneMngr);

	private:
		static CSceneManager* s_pSceneMngr;	//!< シーン管理への参照
	};

	template <class Scene>
	bool CSceneModule::ChangeScene(eSceneId sceneId)
	{
		return s_pSceneMngr->RegisterScene<Scene>(static_cast<unsigned int>(sceneId));
	}

}	// namespace app

#endif	// __APP_SCENE_MODULE_H__
/*!
* @file		appSceneManager.h
* @brief	シーン管理
* @date		2020-06-30
* @author	s.fukami
*/

#ifndef __APP_SCENE_MANAGER_H__
#define __APP_SCENE_MANAGER_H__

#include "ngLibCore/container/array/ngFixedArray.h"

namespace ng
{
	class IMemoryAllocator;
}
namespace app
{
	class IScene;
}

namespace app
{
	/*!
	* @brief					シーン管理
	*/
	class CSceneManager
	{
	public:
		CSceneManager();
		~CSceneManager();

		/*!
		* @brief					初期化
		* @param sceneMax			シーン最大数
		* @return					成否
		*/
		bool Initialize(unsigned int sceneMax);
		
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
		* @brief					シーン登録
		* @tparam Scene				登録するシーン
		* @param index				シーンのインデックス
		* @return					成否
		*/
		template <class Scene>
		bool RegisterScene(unsigned int index);

		/*!
		* @brief					シーン削除
		* @param index				シーンのインデックス
		*/
		void DeleteScene(unsigned int index);
		
	private:
		/*! 初期化済みか */
		bool _isInit() const;

		/*! シーン登録 */
		bool _registerScene(unsigned int index, IScene* pScene);

		/*! メモリアロケータ取得 */
		ng::IMemoryAllocator& _getMemAlloc() const;

	private:
		ng::CFixedArray<IScene*> m_sceneArr;	//!< シーン配列
		bool m_isInit;	//!< 初期化済みか
	};

	template <class Scene>
	bool CSceneManager::RegisterScene(unsigned int index)
	{
		IScene* pScene = NG_NEW(_getMemAlloc()) Scene();
		return _registerScene(index, pScene);
	}

}	// namespace app

#endif	// __APP_SCENE_MANAGER_H__
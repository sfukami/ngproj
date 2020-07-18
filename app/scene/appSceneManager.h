/*!
* @file		appSceneManager.h
* @brief	シーン管理
* @date		2020-06-30
* @author	s.fukami
*/

#ifndef __APP_SCENE_MANAGER_H__
#define __APP_SCENE_MANAGER_H__

#include "ngLibCore/memory/pointer/ngSharedPtr.h"
#include "ngLibCore/container/array/ngFixedArray.h"
#include "app/job/appJobManager.h"

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
		* @param alloc				利用するメモリアロケータ
		* @return					成否
		*/
		bool Initialize(unsigned int sceneMax, ng::IMemoryAllocator& alloc);
		
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
		* @brief					シーン切り替えリクエスト
		* @param index				シーンのインデックス
		* @param scenePtr			登録するシーン
		*/
		void RequestChangeScene(unsigned int index, ng::CSharedPtr<IScene>& scenePtr);

		/*!
		* @brief					シーン切り替えリクエスト実行
		*/
		void ExecuteChangeScene();
		
		/*!
		* @brief					シーン登録
		* @param index				シーンのインデックス
		* @param scenePtr			登録するシーン
		* @return					成否
		*/
		bool RegisterScene(unsigned int index, ng::CSharedPtr<IScene>& scenePtr);

		/*!
		* @brief					シーン削除
		* @param index				シーンのインデックス
		*/
		void DeleteScene(unsigned int index);

	private:
		/*! 初期化済みか */
		bool _isInit() const;

	private:
		ng::CFixedArray<ng::CSharedPtr<IScene> > m_sceneArr;	//!< シーン配列
		bool m_isInit;	//!< 初期化済みか

		CJobManager m_jobMngr;	//!< ジョブ管理
	};

}	// namespace app

#endif	// __APP_SCENE_MANAGER_H__
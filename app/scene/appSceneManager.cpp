/*!
* @file		appSceneManager.cpp
* @brief	シーン管理
* @date		2020-06-30
* @author	s.fukami
*/

#include "ngLibCore/job/ngJob.h"
#include "appSceneManager.h"
#include "appScene.h"
#include "app/memory/appMemoryUtil.h"

namespace app
{
	//! ジョブスロット
	enum eJobSlot
	{
		CHANGE_SCENE,	//!< シーン切り替え

		NUM
	};

	CSceneManager::CSceneManager()
		: m_isInit(false)
	{
	}

	CSceneManager::~CSceneManager()
	{
		Finalize();
	}

	bool CSceneManager::Initialize(unsigned int sceneMax, ng::IMemoryAllocator& alloc)
	{
		NG_ASSERT(!_isInit());

		NG_ERRCODE err = NG_ERRCODE_DEFAULT;

		// シーン配列初期化
		if(NG_FAILED(err = m_sceneArr.Initialize(alloc, sceneMax))) {
			NG_ERRLOG_C("SceneManager", err, "シーン配列の初期化に失敗しました.");
			return false;
		}

		// ジョブ管理初期化
		{
			unsigned int jobMax[] = {1};
			if(!m_jobMngr.Initialize(NG_ARRAY_SIZE(jobMax), jobMax, alloc)) {
				NG_ERRLOG("SceneManager", "ジョブ管理の初期化に失敗しました.");
				return false;
			}
		}

		m_isInit = true;

		return true;
	}

	void CSceneManager::Update(float deltaTime)
	{
		if(!_isInit()) return;

		for(unsigned int i = 0; i < m_sceneArr.Size(); i++)
		{
			ng::CSharedPtr<IScene>& p = m_sceneArr[i];
			if(p) {
				p->Update(deltaTime);
			}
		}
	}

	void CSceneManager::Render()
	{
		if(!_isInit()) return;

		for(unsigned int i = 0; i < m_sceneArr.Size(); i++)
		{
			ng::CSharedPtr<IScene>& p = m_sceneArr[i];
			if(p) {
				p->Render();
			}
		}
	}

	void CSceneManager::Finalize()
	{
		for(unsigned int i = 0; i < m_sceneArr.Size(); i++)
		{
			DeleteScene(i);
		}

		m_sceneArr.Finalize();
		m_jobMngr.Finalize();

		m_isInit = false;
	}

	void CSceneManager::RequestChangeScene(unsigned int index, ng::CSharedPtr<IScene>& scenePtr)
	{
		if(!_isInit()) return;
		if(!scenePtr) return;

		NG_ASSERT(index < m_sceneArr.Size());

		/*! シーン切り替えジョブ */
		class CJobChangeScene : public ng::IJob
		{
		public:
			CJobChangeScene(CSceneManager* pSceneMngr, unsigned int index, ng::CSharedPtr<IScene>& scenePtr)
				: m_pSceneMngr(pSceneMngr), m_index(index), m_scenePtr(scenePtr)
			{ }
			void Execute()
			{
				m_pSceneMngr->RegisterScene(m_index, m_scenePtr);
				// ※スタックアロケータを使用する前提
				// デストラクタが呼ばれないため、明示的に解放する
				m_scenePtr.reset();
			}

		private:
			CSceneManager* m_pSceneMngr;
			unsigned int m_index;
			ng::CSharedPtr<IScene> m_scenePtr;
		};

		// シーン切り替えジョブ追加
		m_jobMngr.EnqueueJob(eJobSlot::CHANGE_SCENE, 
			NG_NEW(APP_MEMALLOC_WORK) CJobChangeScene(this, index, scenePtr)
			);
	}

	void CSceneManager::ExecuteChangeScene()
	{
		if(!_isInit()) return;

		m_jobMngr.ExecuteJob(eJobSlot::CHANGE_SCENE);
	}

	bool CSceneManager::RegisterScene(unsigned int index, ng::CSharedPtr<IScene>& scenePtr)
	{
		if(!_isInit()) return false;
		if(!scenePtr) return false;

		NG_ASSERT(index < m_sceneArr.Size());

		DeleteScene(index);

		if(!scenePtr->Initialize()) {
			NG_ERRLOG("SceneManager", "シーンの初期化に失敗しました.");
			scenePtr->Finalize();
			return false;
		}
		m_sceneArr[index] = scenePtr;

		return true;
	}

	void CSceneManager::DeleteScene(unsigned int index)
	{
		if(!_isInit()) return;

		NG_ASSERT(index < m_sceneArr.Size());

		ng::CSharedPtr<IScene>& p = m_sceneArr[index];
		if(p) {
			p->Finalize();
			p.reset();
		}
	}

	bool CSceneManager::_isInit() const
	{
		return m_isInit;
	}

}	// namespace app
/*!
* @file		appSceneManager.cpp
* @brief	シーン管理
* @date		2020-06-30
* @author	s.fukami
*/

#include "appSceneManager.h"
#include "appScene.h"

namespace app
{
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

		if(NG_FAILED(err = m_sceneArr.Initialize(sceneMax, alloc))) {
			NG_ERRLOG_C("SceneManager", err, "シーン管理の初期化に失敗しました.");
			return false;
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

		m_isInit = false;
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
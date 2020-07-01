/*!
* @file		appSceneManager.cpp
* @brief	シーン管理
* @date		2020-06-30
* @author	s.fukami
*/

#include "appSceneManager.h"
#include "appScene.h"

// test
#include "ngLibCore/system/ngSysUtil.h"

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

	bool CSceneManager::Initialize(unsigned int sceneMax)
	{
		NG_ASSERT(!_isInit());

		NG_ERRCODE err = NG_ERRCODE_DEFAULT;

		if(NG_FAILED(err = m_sceneArr.Initialize(sceneMax, _getMemAlloc()))) {
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
			IScene* pScene = m_sceneArr[i];
			if(pScene != nullptr) {
				pScene->Update(deltaTime);
			}
		}
	}

	void CSceneManager::Render()
	{
		if(!_isInit()) return;

		for(unsigned int i = 0; i < m_sceneArr.Size(); i++)
		{
			IScene* pScene = m_sceneArr[i];
			if(pScene != nullptr) {
				pScene->Render();
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

	void CSceneManager::DeleteScene(unsigned int index)
	{
		if(!_isInit()) return;

		NG_ASSERT(index < m_sceneArr.Size());

		IScene* pScene = m_sceneArr[ index ];
		if(pScene != nullptr) {
			pScene->Finalize();

			NG_SAFE_DELETE(NG_SYSALLOC_MAINSYS, pScene);
			m_sceneArr[ index ] = nullptr;
		}
	}

	bool CSceneManager::_isInit() const
	{
		return m_isInit;
	}

	bool CSceneManager::_registerScene(unsigned int index, IScene* pScene)
	{
		NG_ASSERT(_isInit());
		NG_ASSERT(index < m_sceneArr.Size());

		if(!pScene->Initialize()) {
			return false;
		}

		m_sceneArr[ index ] = pScene;

		return true;
	}

	ng::IMemoryAllocator& CSceneManager::_getMemAlloc() const
	{
		return NG_SYSALLOC_MAINSYS;
	}

}	// namespace app
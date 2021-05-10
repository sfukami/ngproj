/*!
* @file		appSceneModule.cpp
* @brief	シーン機能
* @date		2020-07-01
* @author	s.fukami
*/

#include "ngLibCore/job/ngJob.h"
#include "app/common/appCommon.h"
#include "appSceneModule.h"
#include "../job/appJobModule.h"

namespace app
{
	CSceneManager* CSceneModule::s_pSceneMngr = nullptr;

	void CSceneModule::RequestChangeScene(eSceneId sceneId, ng::CSharedPtr<IScene>& scenePtr)
	{
		class CJobChangeScene : public ng::IJob
		{
		public:
			CJobChangeScene(eSceneId sceneId, ng::CSharedPtr<IScene>& scenePtr)
				: m_sceneId(sceneId), m_scenePtr(scenePtr)
			{ }
			void Execute()
			{
				CSceneModule::ChangeScene(m_sceneId, m_scenePtr);
			}

		private:
			eSceneId m_sceneId;
			ng::CSharedPtr<IScene> m_scenePtr;
		};

		auto jobPtr = NG_MAKE_SHARED_PTR(ng::IJob, APP_GET_MEMALLOC(WORK), CJobChangeScene(sceneId, scenePtr));
		CJobModule::AddJob(jobPtr, eJobProcess::END_OF_FRAME);
	}

	bool CSceneModule::ChangeScene(eSceneId sceneId, ng::CSharedPtr<IScene>& scenePtr)
	{
		if(_isValid()) {
			return s_pSceneMngr->RegisterScene(static_cast<unsigned int>(sceneId), scenePtr);
		}

		return true;
	}

	void CSceneModule::SetSceneManager(CSceneManager* pSceneMngr)
	{
		s_pSceneMngr = pSceneMngr;
	}

	bool CSceneModule::_isValid()
	{
		return (s_pSceneMngr != nullptr);
	}

}	// namespace app
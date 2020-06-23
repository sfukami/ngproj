/*!
* @file		ngCoreSystem.cpp
* @brief	NGライブラリ コアシステム
* @date		2018-02-12
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "ngCoreSystem.h"

namespace ng
{
	CCoreSystem CCoreSystem::m_instance;

	CCoreSystem::SetupParam::SetupParam()
	{
	}

	CCoreSystem::CCoreSystem()
	{
	}

	CCoreSystem::~CCoreSystem()
	{
	}

	NG_ERRCODE CCoreSystem::Setup(const SetupParam& param)
	{
		NG_ERRCODE ret = eNG_S_OK;

		// システムメモリ初期化
		{
			if(NG_FAILED(ret = m_sysMem.Initialize(param.sysMemInitParam))) {
				NG_ERRLOG_C("CoreSystem", ret, "システムメモリの初期化に失敗");
				return ret;
			}
		}

		return ret;
	}

	void CCoreSystem::Shutdown()
	{
		m_sysMem.Finalize();

		CCoreSystem::DestroyInstance();
	}

	IMemoryAllocator* CCoreSystem::GetSysMemAlloc(eSystemMemoryType type)
	{
		return m_sysMem.GetAllocator(type);
	}

	CCoreSystem* CCoreSystem::_createInstance()
	{
		return &m_instance;
	}

	void CCoreSystem::_destroyInstance(CCoreSystem* pInst)
	{
		// 空定義
	}

}	// namespace ng
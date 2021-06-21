/*!
* @file		ngResourceManager.cpp
* @brief	リソース管理
* @date		2020-07-20
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "ngResourceManager.h"
#include "ngResourceHandleIf.h"

namespace ng
{
	CResourceManager::CResourceManager()
		: m_isInit(false)
	{
	}

	CResourceManager::~CResourceManager()
	{
		Finalize();
	}

	NG_ERRCODE CResourceManager::Initialize(IMemoryAllocator& alloc, u32 resMax)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// リソース格納マップ初期化
		if(NG_FAILED(ret = m_resMap.Initialize(alloc, resMax))) {
			NG_ERRLOG_C("ResourceManager", ret, "リソース格納マップの初期化に失敗しました.");
			return ret;
		}

		m_isInit = true;

		return ret;
	}

	void CResourceManager::Finalize()
	{
		m_resMap.Finalize();

		m_isInit = false;
	}

	bool CResourceManager::Add(const char* pKey, CSharedPtr<IResource>& resPtr, IResourceHandle* pHandle)
	{
		NG_ASSERT(_isInit());

		// リソースをマップへ追加
		if(!m_resMap.Add(pKey, resPtr)) {
			NG_WARNLOG("ResourceManager", "リソースの追加に失敗しました. key:%s", pKey);
			return false;
		}

		// リソースハンドルへリソースを設定
		if(pHandle) {
			pHandle->SetResource(resPtr);
		}

		return true;
	}

	bool CResourceManager::Get(const char* pKey, IResourceHandle& handle) const
	{
		if(!TryGet(pKey, handle)) {
			NG_WARNLOG("ResourceManager", "リソースの取得に失敗しました. key:%s", pKey);
			return false;
		}

		return true;
	}

	bool CResourceManager::TryGet(const char* pKey, IResourceHandle& handle) const
	{
		NG_ASSERT(_isInit());

		// マップからリソースを取得
		CSharedPtr<IResource> spRes;
		if(!m_resMap.Get(pKey, spRes)) {
			return false;
		}

		// リソースハンドルへハンドルを設定
		handle.SetResource(spRes);

		return true;
	}

	bool CResourceManager::_isInit() const
	{
		return m_isInit;
	}

}	// namespace ng
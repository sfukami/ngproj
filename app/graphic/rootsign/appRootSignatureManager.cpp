/*!
* @file		appRootSignatureManager.cpp
* @brief	ルートシグネチャ管理
* @date		2020-07-26
* @author	s.fukami
*/

#include "ngLibGraphic/graphic/dx12/rootsign/ngDX12RootSignature.h"
#include "appRootSignatureManager.h"
#include "appRootSignatureInfo.h"

namespace app
{
	CRootSignatureManager::CRootSignatureManager()
	{
	}
	CRootSignatureManager::~CRootSignatureManager()
	{
		Finalize();
	}

	bool CRootSignatureManager::Initialize(ng::IMemoryAllocator& alloc, ng::CDX12Device& device)
	{
		// ルートシグネチャ情報からDX12ルートシグネチャを生成し追加
		const unsigned int rootSignInfoNum = GetRootSignatureInfoNum();

		for(unsigned int i = 0; i < rootSignInfoNum; i++)
		{
			const RootSignatureInfo* pRootSignInfo = GetRootSignatureInfo(i);
			NG_ASSERT_NOT_NULL(pRootSignInfo);
			
			auto rootSignPtr = NG_MAKE_SHARED_PTR(ng::CDX12RootSignature, alloc);
			m_rootSignMap.Add(pRootSignInfo->name, rootSignPtr);
		}

		return true;
	}

	void CRootSignatureManager::Finalize()
	{
		m_rootSignMap.Clear();
	}

}	// namespace app
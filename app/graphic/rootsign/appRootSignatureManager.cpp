/*!
* @file		appRootSignatureManager.cpp
* @brief	ルートシグネチャ管理
* @date		2020-07-26
* @author	s.fukami
*/

#include "ngLibCore/memory/pointer/ngWeakPtr.h"
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

			NG_ERRCODE err = NG_ERRCODE_DEFAULT;
			if(NG_SUCCEEDED(err = rootSignPtr->Create(device, *pRootSignInfo->pDesc))) {
				m_rootSignMap.Add(pRootSignInfo->name, rootSignPtr);
			}
			else {
				NG_ERRLOG_C("RootSignatureManager", err, "DX12ルートシグネチャの生成に失敗しました. name:%s", pRootSignInfo->name);
			}
		}

		return true;
	}

	void CRootSignatureManager::Finalize()
	{
		m_rootSignMap.Clear();
	}

	bool CRootSignatureManager::Get(const char* name, ng::CWeakPtr<ng::CDX12RootSignature>& dstPtr) const
	{
		ng::CSharedPtr<ng::CDX12RootSignature> sp;

		if(!m_rootSignMap.Get(name, sp)) {
			return false;
		}

		dstPtr = sp;

		return true;
	}

}	// namespace app
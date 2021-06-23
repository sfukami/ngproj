/*!
* @file		appRootSignatureManager.cpp
* @brief	ルートシグネチャ管理
* @date		2020-07-26
* @author	s.fukami
*/

#include "ngLibCore/memory/pointer/ngWeakPtr.h"
#include "ngLibGraphic/graphic/dx12/rootsign/ngDX12RootSignature.h"
#include "appRootSignatureManager.h"
#include "desc/appRootSignatureDescDef.h"

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
		//! DX12ルートシグネチャ生成関数設定マクロ
		#define _MAKE_CREATE_ROOT_SIGNATURE_FUNC(_desc) \
			&CRootSignatureManager::_createRootSignature<_desc>

		//! DX12ルートシグネチャ生成関数テーブル
		using FuncType = bool(CRootSignatureManager::*)(ng::IMemoryAllocator&, ng::CDX12Device&);
		const FuncType funcTbl[] = {
			_MAKE_CREATE_ROOT_SIGNATURE_FUNC(CRootSignatureDescSprite),
			_MAKE_CREATE_ROOT_SIGNATURE_FUNC(CRootSignatureDescSpriteT0),
			_MAKE_CREATE_ROOT_SIGNATURE_FUNC(CRootSignatureDescModel),
		};

		// 各DX12ルートシグネチャ生成
		bool result = true;
		for(int i = 0; i < NG_ARRAY_SIZE(funcTbl); i++)
		{
			result &= (this->*funcTbl[i])(alloc, device);
		}

		return result;
	}

	void CRootSignatureManager::Finalize()
	{
		m_rootSignMap.Clear();
	}

	bool CRootSignatureManager::Get(const char* name, ng::CWeakPtr<ng::CDX12RootSignature>& dstPtr) const
	{
		const MapType::INodeType* pNode = m_rootSignMap.Find(name);

		if(pNode == nullptr) {
			return false;
		}

		dstPtr = ng::CWeakPtr<ng::CDX12RootSignature>(pNode->GetValue());

		return true;
	}

	template <class T>
	bool CRootSignatureManager::_createRootSignature(ng::IMemoryAllocator& alloc, ng::CDX12Device& device)
	{
		auto rootSignPtr = NG_MAKE_SHARED_PTR(ng::CDX12RootSignature, alloc);

		T desc;
		NG_ERRCODE err = rootSignPtr->Create(device, desc);
		if(NG_SUCCEEDED(err)) {
			if(!m_rootSignMap.Add(desc.GetName(), rootSignPtr)) {
				NG_ERRLOG("RootSignatureManager", "DX12ルートシグネチャの登録に失敗しました. name:%s", desc.GetName());
			}
		} else {
			NG_ERRLOG_C("RootSignatureManager", err, "DX12ルートシグネチャの生成に失敗しました. name:%s", desc.GetName());
		}

		return NG_SUCCEEDED(err);
	}

}	// namespace app
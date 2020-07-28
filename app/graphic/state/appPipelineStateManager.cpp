/*!
* @file		appPipelineStateManager.cpp
* @brief	パイプラインステート管理
* @date		2020-07-29
* @author	s.fukami
*/

#include "ngLibGraphic/graphic/dx12/pipeline/ngDX12PipelineState.h"
#include "ngLibGraphic/graphic/dx12/ngDX12Util.h"
#include "appPipelineStateManager.h"

namespace app
{
	CPipelineStateManager::CPipelineStateManager()
	{
	}
	CPipelineStateManager::~CPipelineStateManager()
	{
		Finalize();
	}

	void CPipelineStateManager::Finalize()
	{
		m_stateMap.Clear();
	}

	bool CPipelineStateManager::Add(const char* name, const ng::CSharedPtr<ng::CDX12PipelineState>& statePtr)
	{
		NG_ASSERT_NOT_NULL(statePtr);

		if(!m_stateMap.Add(name, statePtr)) {
			NG_ERRLOG("PipelineStateManager", "パイプラインステートの追加に失敗しました. name:%s", name);
			return false;
		}

		return true;
	}

	bool CPipelineStateManager::CreateAndAdd(ng::IMemoryAllocator& alloc, const char* name, const ng::CDX12PipelineStateDesc& stateDesc)
	{
		auto statePtr = NG_MAKE_SHARED_PTR(ng::CDX12PipelineState, alloc);
		NG_ASSERT_NOT_NULL(statePtr);

		ng::CDX12Device* pDX12Device = ng::DX12Util::GetDevice();
		NG_ASSERT_NOT_NULL(pDX12Device);

		// DX12パイプラインステート生成
		NG_ERRCODE err = NG_ERRCODE_DEFAULT;
		if(NG_FAILED(err = statePtr->Create(*pDX12Device, stateDesc))) {
			NG_ERRLOG_C("PipelineStateManager", err, "DX12パイプラインステートの生成に失敗しました. name:%s", name);
			return false;
		}

		return Add(name, statePtr);
	}

	bool CPipelineStateManager::Get(const char* name, ng::CSharedPtr<ng::CDX12PipelineState>& dstPtr)
	{
		return m_stateMap.Get(name, dstPtr);
	}

}	// namespace app
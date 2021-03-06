﻿/*!
* @file		appGraphicModule.cpp
* @brief	グラフィック機能
* @date		2020-07-01
* @author	s.fukami
*/

#include "appGraphicModule.h"
#include "appGraphic.h"
#include "appGraphicUtil.h"
#include "app/memory/appMemoryUtil.h"
#include "rootsign/appRootSignatureManager.h"
#include "state/appPipelineStateManager.h"
#include "shader/effect/factory/appShaderEffectFactory.h"

namespace app
{
	CGraphic* CGraphicModule::s_pGraphic = nullptr;

	void CGraphicModule::SetGraphicPipeline(CGraphicPipeline* pPipeline)
	{
		if(!_isValid()) return;

		s_pGraphic->SetPipeline(pPipeline);
	}

	bool CGraphicModule::GetRootSignature(const char* name, ng::CWeakPtr<ng::CDX12RootSignature>& dstPtr)
	{
		if(!_isValid()) return false;

		const CRootSignatureManager& rootSignMngr = s_pGraphic->GetRootSignatureManager();

		return rootSignMngr.Get(name, dstPtr);
	}

	bool CGraphicModule::GetPipelineState(const char* name, ng::CWeakPtr<ng::CDX12PipelineState>& dstPtr)
	{
		if(!_isValid()) return false;

		const CPipelineStateManager& plStateMngr = s_pGraphic->GetPipelineStateManager();

		return plStateMngr.Get(name, dstPtr);
	}

	bool CGraphicModule::CreateAndAddPipelineState(const char* name, const ng::CDX12PipelineStateDesc& stateDesc)
	{
		if(!_isValid()) return false;

		CPipelineStateManager& plStateMngr = s_pGraphic->GetPipelineStateManager();

		return plStateMngr.CreateAndAdd(app::GraphicUtil::GetGraphicMemAlloc(), name, stateDesc);
	}

	bool CGraphicModule::CreateShaderEffect(const char* name, ng::CSharedPtr<CShaderEffect>& dstPtr)
	{
		if(!_isValid()) return false;

		const CShaderEffectFactory& shEffFac = s_pGraphic->GetShaderEffectFactory();

		return shEffFac.Create(app::GraphicUtil::GetGraphicMemAlloc(), name, dstPtr);
	}

	bool CGraphicModule::_isValid()
	{
		return (s_pGraphic != nullptr);
	}

	void CGraphicModule::SetGraphic(CGraphic* pGraphic)
	{
		s_pGraphic = pGraphic;
	}

}	// namespace app
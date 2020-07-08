/*!
* @file		ngRenderSystem.cpp
* @brief	描画システム
* @date		2020-07-07
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "ngLibCore/system/ngSysUtil.h"
#include "ngRenderSystem.h"

namespace ng
{
	CRenderSystem::CRenderSystem()
		: m_isSorted(false)
	{
	}

	CRenderSystem::~CRenderSystem()
	{
		Finalize();
	}

	NG_ERRCODE CRenderSystem::Initialize(u32 commandMax)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// 描画コマンド用のメモリアロケータを初期化
		size_type allocSize = sizeof(CRenderCommand) * commandMax;
		if(NG_FAILED(ret = m_cmdAlloc.Initialize("render_command", NG_SYSALLOC_GRAPHIC, allocSize))) {
			NG_ERRLOG_C("RenderSystem", ret, "描画コマンド用のメモリアロケータの初期化に失敗しました.");
			return ret;
		}

		return ret;
	}

	void CRenderSystem::Finalize()
	{
		m_cmdList.Clear();
		m_cmdAlloc.Finalize();
	}
	
	void CRenderSystem::AddCommand(CRenderCommand& command)
	{
		m_cmdList.PushBack(command);

		m_isSorted = false;
	}

	void CRenderSystem::ExecuteCommand()
	{
		// ソート済みでない場合はソート
		if(!m_isSorted) {
			_sortCommandList();
		}

		// 全描画コマンド実行
		for(auto pNode = m_cmdList.Begin(); pNode != m_cmdList.End(); pNode = pNode->GetNext())
		{
			pNode->GetElem().Execute();
		}
	}

	void CRenderSystem::ClearCommand()
	{
		m_cmdList.Clear();
		m_cmdAlloc.Clear();
	}

	void CRenderSystem::_sortCommandList()
	{
		m_isSorted = true;
	}

}	// namespace ng
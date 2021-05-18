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

		// 描画コマンドバッファ初期化
		for(int i = 0; i < static_cast<int>(BufferIndex::NUM); i++)
		{
			CRenderCommandBuffer& cmdBuf = m_cmdBuf.GetBuffer(static_cast<BufferIndex>(i));
			if(NG_FAILED(ret = cmdBuf.Initialize(NG_SYSALLOC_GRAPHIC, commandMax))) {
				NG_ERRLOG_C("RenderSystem", ret, "描画コマンドバッファの初期化に失敗しました. index:%d", i);
				return ret;
			}
		}

		return ret;
	}

	void CRenderSystem::Finalize()
	{
		for(int i = 0; i < static_cast<int>(BufferIndex::NUM); i++)
		{
			m_cmdBuf.GetBuffer(static_cast<BufferIndex>(i)).Finalize();
		}
	}

	void CRenderSystem::AddCommand(const RenderCommand& command)
	{
		m_isSorted = false;
		m_cmdBuf.GetCurrBuffer().AddCommand(command);
	}

	void CRenderSystem::ExecuteCommand(const RenderParam* pParam)
	{
		CRenderCommandBuffer& cmdBuf = m_cmdBuf.GetCurrBuffer();
		if(!m_isSorted) {
			cmdBuf.SortCommand();
			m_isSorted = true;
		}

		cmdBuf.ExecuteCommand(pParam);
	}

	void CRenderSystem::ClearCommand()
	{
		m_cmdBuf.GetCurrBuffer().ClearCommand();
	}

	CRenderSystem::CCommandBuffer::CCommandBuffer()
		: m_currIndex(BufferIndex::PRIMARY)
	{
	}

	CRenderSystem::CCommandBuffer::~CCommandBuffer()
	{
	}

	void CRenderSystem::CCommandBuffer::SetCurrBuffer(BufferIndex index)
	{
		m_currIndex = index;
	}

	void CRenderSystem::CCommandBuffer::SwapBuffer()
	{
		if(m_currIndex == BufferIndex::PRIMARY)
			m_currIndex = BufferIndex::SECONDARY;
		else
			m_currIndex = BufferIndex::PRIMARY;
	}

	CRenderCommandBuffer& CRenderSystem::CCommandBuffer::GetCurrBuffer()
	{
		return GetBuffer(m_currIndex);
	}

	const CRenderCommandBuffer& CRenderSystem::CCommandBuffer::GetCurrBuffer() const
	{
		return GetBuffer(m_currIndex);
	}

	CRenderCommandBuffer& CRenderSystem::CCommandBuffer::GetBuffer(BufferIndex index)
	{
		return m_cmdBufs[static_cast<int>(index)];
	}

	const CRenderCommandBuffer& CRenderSystem::CCommandBuffer::GetBuffer(BufferIndex index) const
	{
		return m_cmdBufs[static_cast<int>(index)];
	}

}	// namespace ng
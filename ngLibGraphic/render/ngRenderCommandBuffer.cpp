/*!
* @file		ngRenderCommandBuffer.cpp
* @brief	描画コマンドバッファ
* @date		2020-05-12
* @author	s.fukami
*/

#include <algorithm>
#include "ngLibCore/common/ngCommon.h"
#include "ngRenderCommandBuffer.h"
#include "ngRenderCommand.h"

namespace ng
{
	CRenderCommandBuffer::CRenderCommandBuffer()
		: m_pCmdBuf(nullptr), m_cmdMax(0), m_cmdNum(0)
	{
	}

	CRenderCommandBuffer::~CRenderCommandBuffer()
	{
		Finalize();
	}

	NG_ERRCODE CRenderCommandBuffer::Initialize(IMemoryAllocator& alloc, u32 commandMax)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// 描画コマンド用のメモリアロケータを初期化
		size_type allocSize = sizeof(RenderCommand) * commandMax;
		if(NG_FAILED(ret = m_cmdAlloc.Initialize("render_command", alloc, allocSize))) {
			NG_ERRLOG_C("RenderCommandBuffer", ret, "描画コマンド用のメモリアロケータの初期化に失敗しました.");
			return ret;
		}

		m_cmdMax = commandMax;

		// 描画コマンドのバッファの先頭アドレスを設定
		m_pCmdBuf = PointerCast<RenderCommand*>(m_cmdAlloc.GetMemory());

		return ret;
	}

	void CRenderCommandBuffer::Finalize()
	{
		m_pCmdBuf = nullptr;

		m_cmdAlloc.Finalize();
	}

	void CRenderCommandBuffer::AddCommand(const RenderCommand& command)
	{
		if(m_cmdNum >= m_cmdMax) {
			NG_WARNLOG("RenderCommandBuffer", "描画コマンドの最大数を超えたため、描画コマンドの追加に失敗しました. cmdMax:%d", m_cmdMax);
			return;
		}

		m_pCmdBuf[ m_cmdNum ] = command;
		m_cmdNum++;
	}

	void CRenderCommandBuffer::SortCommand()
	{
		struct Compare
		{
			bool operator()(const RenderCommand& lhs, const RenderCommand& rhs)
			{
				return lhs.order > rhs.order;
			}
		};

		std::sort(m_pCmdBuf, m_pCmdBuf + m_cmdNum, Compare());
	}

	void CRenderCommandBuffer::ExecuteCommand(const RenderParam* pParam)
	{
		for(u32 i = 0; i < m_cmdNum; i++)
		{
			m_pCmdBuf[i].Execute(pParam);
		}
	}

	void CRenderCommandBuffer::ClearCommand()
	{
		m_cmdAlloc.Clear();

		m_cmdNum = 0;
	}

}	// namespace ng
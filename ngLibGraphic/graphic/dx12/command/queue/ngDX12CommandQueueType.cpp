/*!
* @file		ngDX12CommandQueueType.cpp
* @brief	DX12コマンドキュータイプ
* @date		2018-02-12
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "ngDX12CommandQueueType.h"

namespace ng
{
	// DX12コマンドリストタイプ
	static const D3D12_COMMAND_LIST_TYPE g_DX12CommandListTypeTable[] = {
		D3D12_COMMAND_LIST_TYPE_DIRECT,			// eDX12_COMMAND_QUEUE_TYPE_GRAPHIC
	//	D3D12_COMMAND_LIST_TYPE_BUNDLE,			// eDX12_COMMAND_QUEUE_TYPE_BUNDLE
		D3D12_COMMAND_LIST_TYPE_COMPUTE,		// eDX12_COMMAND_QUEUE_TYPE_COMPUTE
		D3D12_COMMAND_LIST_TYPE_COPY,			// eDX12_COMMAND_QUEUE_TYPE_COPY
	//	D3D12_COMMAND_LIST_TYPE_VIDEO_DECODE,
	//	D3D12_COMMAND_LIST_TYPE_VIDEO_PROCESS,
	};
}

namespace ng
{
	NG_DECL D3D12_COMMAND_LIST_TYPE DX12ToCommandListType(eDX12CommandQueueType type)
	{
		NG_ASSERT(type < eDX12CommandQueueType::NUM);
		
		return g_DX12CommandListTypeTable[static_cast<int>(type)];
	}

}	// namespace ng
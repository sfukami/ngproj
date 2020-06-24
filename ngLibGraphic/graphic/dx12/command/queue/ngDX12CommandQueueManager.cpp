/*!
* @file		ngDX12CommandQueueManager.cpp
* @brief	DX12コマンドキューマネージャ
* @date		2018-02-18
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "../../common/ngDX12Common.h"
#include "ngDX12CommandQueueManager.h"
#include "ngDX12CommandQueue.h"

namespace ng
{
	CDX12CommandQueueManager::CDX12CommandQueueManager()
	{
	}

	CDX12CommandQueueManager::~CDX12CommandQueueManager()
	{
		Finalize();
	}

	NG_ERRCODE CDX12CommandQueueManager::Initialize(CDX12Device& device)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// グラフィックコマンドキュー
		{
			if(NG_FAILED(ret = _createCommandQueue(device, eDX12CommandQueueType::GRAPHIC))) {
				NG_ERRLOG_C("DX12CommandQueueManager", ret, "グラフィックコマンドキューの生成に失敗しました.");
				return ret;
			}
		}
		// コンピュートコマンドキュー
		{
			if(NG_FAILED(ret = _createCommandQueue(device, eDX12CommandQueueType::COMPUTE))) {
				NG_ERRLOG_C("DX12CommandQueueManager", ret, "コンピュートコマンドキューの生成に失敗しました.");
				return ret;
			}
		}
		// コピーコマンドキュー
		{
			if(NG_FAILED(ret = _createCommandQueue(device, eDX12CommandQueueType::COPY))) {
				NG_ERRLOG_C("DX12CommandQueueManager", ret, "コピーコマンドキューの生成に失敗しました.");
				return ret;
			}
		}

		return ret;
	}

	void CDX12CommandQueueManager::Finalize()
	{
		for(int i = 0; i < static_cast<int>(eDX12CommandQueueType::NUM); i++)
		{
			_deleteCommandQueue(static_cast<eDX12CommandQueueType>(i));
		}
	}

	CDX12CommandQueue* CDX12CommandQueueManager::GetCommandQueue(eDX12CommandQueueType type)
	{
		NG_ASSERT(type < eDX12CommandQueueType::NUM);

		return m_queueArr[static_cast<int>(type)];
	}
	const CDX12CommandQueue* CDX12CommandQueueManager::GetCommandQueue(eDX12CommandQueueType type) const
	{
		return const_cast<CDX12CommandQueueManager*>(this)->GetCommandQueue(type);
	}

	NG_ERRCODE CDX12CommandQueueManager::_createCommandQueue(CDX12Device& device, eDX12CommandQueueType type)
	{
		NG_ASSERT(type < eDX12CommandQueueType::NUM);

		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// DX12コマンドキュー生成
		CDX12CommandQueue* pQueue = NG_NEW(NG_SYSALLOC_GRAPHIC) CDX12CommandQueue();
		if(NG_FAILED(ret = pQueue->Create(device, DX12ToCommandListType(type)))) {
			return ret;
		}

		m_queueArr[static_cast<int>(type)] = pQueue;

		return ret;
	}

	void CDX12CommandQueueManager::_deleteCommandQueue(eDX12CommandQueueType type)
	{
		NG_ASSERT(type < eDX12CommandQueueType::NUM);

		CDX12CommandQueue* pQueue = GetCommandQueue(type);
		if(pQueue != nullptr) {
			pQueue->Destroy();
			NG_DELETE(NG_SYSALLOC_GRAPHIC, pQueue);
			m_queueArr[static_cast<int>(type)] = nullptr;
		}
	}

}	// namespace ng
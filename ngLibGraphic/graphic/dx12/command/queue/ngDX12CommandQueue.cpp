/*!
* @file		ngDX12CommandQueue.cpp
* @brief	DX12コマンドキュー
* @date		2017-09-18
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "ngLibCore/math/ngMath.h"
#include "../../common/ngDX12Common.h"
#include "../../device/ngDX12Device.h"
#include "ngDX12CommandQueue.h"
#include "../list/ngDX12CommandList.h"
#include "../../fence/ngDX12Fence.h"

namespace ng
{
	CDX12CommandQueue::CDX12CommandQueue()
		: m_pIQueue(nullptr)
		, m_nextFenceValue(1)
		, m_fenceEvHndl(nullptr)
	{
	}

	CDX12CommandQueue::~CDX12CommandQueue()
	{
		Destroy();
	}

	NG_ERRCODE CDX12CommandQueue::Create(
		CDX12Device& device,
		D3D12_COMMAND_LIST_TYPE type,
		u32 priority
		)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;
		ID3D12Device* pIDevice = device.Interface();

		// DX12コマンドキュー生成
		D3D12_COMMAND_QUEUE_DESC desc = {};
		desc.Type = type;
		desc.Priority = priority;
		desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

		if(NG_FAILED(ret = pIDevice->CreateCommandQueue(&desc, IID_PPV_ARGS(&m_pIQueue)))) {
			NG_DXERR("DX12CommandQueue", ret, CreateCommandQueue, "DX12コマンドキューの生成に失敗しました.");
			return ret;
		}

		// DX12フェンス生成
		if(NG_FAILED(ret = m_fence.Create(device))) {
			return ret;
		}

		// イベントのハンドル生成
		m_fenceEvHndl = ::CreateEvent(nullptr, false, false, nullptr);
		if(m_fenceEvHndl == INVALID_HANDLE_VALUE) {
			ret = E_HANDLE;
			NG_ERRLOG_C("DX12CommandQueue", ret, "フェンス待機用イベントオブジェクトへのハンドルの生成に失敗しました.");
			return ret;
		}

		return ret;
	}

	void CDX12CommandQueue::ExecuteCommandLists(CDX12CommandList* ppCommandLists[], u32 num)
	{
		ID3D12CommandList* pLists[NG_DX12_COMMAND_LIST_MAX];
		num = Clamp<u32>(num, 0, NG_ARRAY_SIZE(pLists));

		for(u32 i = 0; i < num; i++)
		{
			pLists[i] = ppCommandLists[i]->Interface();
		}

		m_pIQueue->ExecuteCommandLists(num, pLists);
	}
	void CDX12CommandQueue::ExecuteCommandList(CDX12CommandList& commandList)
	{
		ID3D12CommandList* pCommandList = commandList.Interface();
		m_pIQueue->ExecuteCommandLists(1, &pCommandList);
	}

	void CDX12CommandQueue::WaitForFence()
	{
		const u64 fenceValue = m_nextFenceValue;
		_signal(m_fence, fenceValue);
		m_nextFenceValue++;

		if(m_fence.GetCompletedValue() < fenceValue) {
			// 指定値到達でイベントを発火する
			m_fence.SetEventOnCompletion(fenceValue, m_fenceEvHndl);
			// それまで待機
			::WaitForSingleObject(m_fenceEvHndl, INFINITE);
		}
	}

	void CDX12CommandQueue::Destroy()
	{
		NG_SAFE_RELEASE(m_pIQueue);

		if(
			m_fenceEvHndl != nullptr &&
			m_fenceEvHndl != INVALID_HANDLE_VALUE
			) {
			::CloseHandle(m_fenceEvHndl);
			m_fenceEvHndl = nullptr;
		}
	}

	bool CDX12CommandQueue::IsValid() const
	{
		return (m_pIQueue != nullptr);
	}

	ID3D12CommandQueue* CDX12CommandQueue::Interface()
	{
		return m_pIQueue;
	}
	const ID3D12CommandQueue* CDX12CommandQueue::Interface() const
	{
		return m_pIQueue;
	}

	NG_ERRCODE CDX12CommandQueue::_signal(CDX12Fence& fence, u64 value)
	{
		return m_pIQueue->Signal(fence.Interface(), value);
	}

}	// namespace ng
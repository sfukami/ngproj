/*!
* @file		ngDX12CommandList.cpp
* @brief	DX12コマンドリスト
* @date		2017-09-24
* @author	s.fukami
*/

#include <d3d12.h>
#include "ngLibCore/common/ngCommon.h"
#include "ngLibCore/math/ngMath.h"
#include "../../common/ngDX12Common.h"
#include "../../device/ngDX12Device.h"
#include "../allocator/ngDX12CommandAllocator.h"
#include "../../rootsign/ngDX12RootSignature.h"
#include "../../pipeline/ngDX12PipelineState.h"
#include "../../barrier/ngDX12ResourceBarrier.h"
#include "../../descriptor/ngDX12DescriptorHeap.h"
#include "../../viewport/ngDX12Viewport.h"
#include "../../scissor/ngDX12Scissor.h"
#include "ngDX12CommandList.h"

namespace ng
{
	CDX12CommandList::CDX12CommandList()
		: m_pIList(nullptr)
		, m_pCmdAlloc(nullptr)
	{
	}

	CDX12CommandList::~CDX12CommandList()
	{
		Destroy();
	}

	NG_ERRCODE CDX12CommandList::Create(
		CDX12Device& device,
		CDX12CommandAllocator& allocator
		)
	{
		NG_ASSERT(!IsValid());

		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// DX12コマンドリスト生成
		if(NG_FAILED(ret = device.Interface()->CreateCommandList(
			0,
			allocator.GetCommandListType(),
			allocator.Interface(),
			nullptr,
			IID_PPV_ARGS(&m_pIList)
			))) {
			NG_DXERRLOG("DX12CommandList", ret, CreateCommandList, "コマンドリストの生成に失敗しました.");
			return ret;
		}

		Close();

		m_pCmdAlloc = &allocator;

		return ret;
	}
	
	NG_ERRCODE CDX12CommandList::Close()
	{
		return m_pIList->Close();
	}

	NG_ERRCODE CDX12CommandList::Reset()
	{
		NG_ASSERT(IsValid());

		return m_pIList->Reset(m_pCmdAlloc->Interface(), nullptr);
	}
	NG_ERRCODE CDX12CommandList::Reset(CDX12PipelineState& state)
	{
		NG_ASSERT(IsValid());

		return m_pIList->Reset(m_pCmdAlloc->Interface(), state.Interface());
	}

	void CDX12CommandList::SetRootSignature(CDX12RootSignature& signature)
	{
		m_pIList->SetGraphicsRootSignature(signature.Interface());
	}

	void CDX12CommandList::SetViewports(const CDX12Viewport* ppViewports[], u32 num)
	{
		NG_ASSERT(IsValid());
		NG_ASSERT(num < NG_DX12_VIEWPORT_MAX_PER_PIPELINE);

		D3D12_VIEWPORT viewports[NG_DX12_VIEWPORT_MAX_PER_PIPELINE];
		num = Clamp<u32>(num, 0, NG_ARRAY_SIZE(viewports));

		for(u32 i = 0; i < num; i++)
		{
			viewports[i] = ppViewports[i]->GetViewport();
		}

		m_pIList->RSSetViewports(num, viewports);
	}
	void CDX12CommandList::SetViewport(const CDX12Viewport& viewport)
	{
		if(!IsValid()) return;

		m_pIList->RSSetViewports(1, &viewport.GetViewport());
	}

	void CDX12CommandList::SetScissorRects(const CDX12Scissor* ppScissors[], u32 num)
	{
		NG_ASSERT(IsValid());
		NG_ASSERT(num < NG_DX12_SCISSORRECT_MAX_PER_PIPELINE);

		CD3DX12_RECT rects[NG_DX12_SCISSORRECT_MAX_PER_PIPELINE];
		num = Clamp<u32>(num, 0, NG_ARRAY_SIZE(rects));

		for(u32 i = 0; i < num; i++)
		{
			rects[i] = ppScissors[i]->GetScissorRect();
		}

		m_pIList->RSSetScissorRects(num, rects);
	}
	void CDX12CommandList::SetScissorRect(const CDX12Scissor& scissor)
	{
		NG_ASSERT(IsValid());

		m_pIList->RSSetScissorRects(1, &scissor.GetScissorRect());
	}

	void CDX12CommandList::ResourceBarriers(const CDX12ResourceBarrier* ppBarriers[], u32 num)
	{
		NG_ASSERT(IsValid());
		NG_ASSERT(num < NG_DX12_RESOURCE_BARRIER_SET_MAX_AT_ONCE);

		D3D12_RESOURCE_BARRIER barriers[NG_DX12_RESOURCE_BARRIER_SET_MAX_AT_ONCE];
		num = Clamp<u32>(num, 0, NG_ARRAY_SIZE(barriers));

		for(u32 i = 0; i < num; i++)
		{
			barriers[i] = ppBarriers[i]->GetResourceBarrier();
		}

		m_pIList->ResourceBarrier(num, barriers);
	}
	void CDX12CommandList::ResourceBarrier(const CDX12ResourceBarrier& barrier)
	{
		NG_ASSERT(IsValid());

		m_pIList->ResourceBarrier(1, &barrier.GetResourceBarrier());
	}

	void CDX12CommandList::SetRenderTargets(
		const D3D12_CPU_DESCRIPTOR_HANDLE pRTVDescriptorHndls[],
		u32 RTVNum,
		const D3D12_CPU_DESCRIPTOR_HANDLE* pDSVDescriptorHndl
		)
	{
		NG_ASSERT(IsValid());

		m_pIList->OMSetRenderTargets(RTVNum, pRTVDescriptorHndls, FALSE, pDSVDescriptorHndl);
	}
	void CDX12CommandList::SetRenderTarget(
		const D3D12_CPU_DESCRIPTOR_HANDLE& RTVDescriptorHndl,
		const D3D12_CPU_DESCRIPTOR_HANDLE* pDSVDescriptorHndl
		)
	{
		NG_ASSERT(IsValid());

		m_pIList->OMSetRenderTargets(1, &RTVDescriptorHndl, FALSE, pDSVDescriptorHndl);
	}

	void CDX12CommandList::ClearRenderTarget(
		const D3D12_CPU_DESCRIPTOR_HANDLE& RTVDescriptorHndl,
		const float colorRGBA[4],
		const D3D12_RECT pRects[],
		u32 rectNum
		)
	{
		NG_ASSERT(IsValid());

		m_pIList->ClearRenderTargetView(RTVDescriptorHndl, colorRGBA, rectNum, pRects);
	}

	void CDX12CommandList::ClearDepthStencil(
		const D3D12_CPU_DESCRIPTOR_HANDLE& DSVDescriptorHndl,
		D3D12_CLEAR_FLAGS flags,
		float depth,
		u8 stencil,
		const D3D12_RECT pRects[],
		u32 rectNum
		)
	{
		NG_ASSERT(IsValid());

		m_pIList->ClearDepthStencilView(DSVDescriptorHndl, D3D12_CLEAR_FLAG_DEPTH, depth, stencil, rectNum, pRects);
	}

	void CDX12CommandList::SetDescriptorHeaps(CDX12DescriptorHeap* const ppDescriptorHeaps[], u32 num)
	{
		ID3D12DescriptorHeap* ppIDescriptorHeaps[ NG_DX12_DESCRIPTOR_HEAP_MAX ];
		
		for(u32 i = 0; i < num; i++)
		{
			ppIDescriptorHeaps[i] = ppDescriptorHeaps[i]->Interface();
		}

		m_pIList->SetDescriptorHeaps(num, ppIDescriptorHeaps);
	}
	void CDX12CommandList::SetDescriptorHeap(CDX12DescriptorHeap& descriptorHeap)
	{
		ID3D12DescriptorHeap* const ppIDescriptorHeaps[] = {descriptorHeap.Interface()};
		m_pIList->SetDescriptorHeaps(1, ppIDescriptorHeaps);
	}

	void CDX12CommandList::SetGraphicsRootDescriptorTable(
		u32 index,
		const D3D12_GPU_DESCRIPTOR_HANDLE& handle
		)
	{
		m_pIList->SetGraphicsRootDescriptorTable(index, handle);
	}

	void CDX12CommandList::Destroy()
	{
		NG_SAFE_RELEASE(m_pIList);

		m_pCmdAlloc = nullptr;
	}
	
	bool CDX12CommandList::IsValid() const
	{
		return (m_pIList != nullptr);
	}

	CDX12CommandList::DX12IfType* CDX12CommandList::Interface()
	{
		return m_pIList;
	}
	const CDX12CommandList::DX12IfType* CDX12CommandList::Interface() const
	{
		return m_pIList;
	}

}	// namespace ng
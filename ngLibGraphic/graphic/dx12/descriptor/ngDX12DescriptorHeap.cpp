/*!
* @file		ngDX12DescriptorHeap.cpp
* @brief	DX12ディスクリプタヒープ
* @date		2017-09-19
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "../common/ngDX12Common.h"
#include "../device/ngDX12Device.h"
#include "ngDX12DescriptorHeap.h"

namespace ng
{
	CDX12DescriptorHeap::CDX12DescriptorHeap()
		: m_pIDescriptorHeap(nullptr)
		, m_incrementSize(0)
	{
	}

	CDX12DescriptorHeap::~CDX12DescriptorHeap()
	{
		Destroy();
	}

	NG_ERRCODE CDX12DescriptorHeap::Create(
		CDX12Device& device,
		D3D12_DESCRIPTOR_HEAP_TYPE type,
		u32 descriptorNum,
		D3D12_DESCRIPTOR_HEAP_FLAGS flags
		)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;
		ID3D12Device* pIDevice = device.Interface();

		D3D12_DESCRIPTOR_HEAP_DESC desc = {};
		desc.Type = type;
		desc.NumDescriptors = descriptorNum;
		desc.Flags = flags;
		//desc.NodeMask = 

		// DX12ディスクリプタヒープ生成
		if(NG_FAILED(ret = pIDevice->CreateDescriptorHeap(
			&desc,
			IID_PPV_ARGS(&m_pIDescriptorHeap)
			))) {
			NG_DXERRLOG("DX12DescriptorHeap", ret, CreateDescriptorHeap, "DX12ディスクリプタヒープの作成に失敗しました.");
		}

		m_incrementSize = pIDevice->GetDescriptorHandleIncrementSize(type);

		return ret;
	}

	void CDX12DescriptorHeap::Destroy()
	{
		NG_SAFE_RELEASE(m_pIDescriptorHeap);
	}

	bool CDX12DescriptorHeap::IsValid() const
	{
		return (m_pIDescriptorHeap != nullptr);
	}

	D3D12_CPU_DESCRIPTOR_HANDLE CDX12DescriptorHeap::GetCPUDescriptorHandleForHeapStart() const
	{
		if(!IsValid()) {
			return D3D12_CPU_DESCRIPTOR_HANDLE();
		}

		return m_pIDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	}

	CD3DX12_CPU_DESCRIPTOR_HANDLE CDX12DescriptorHeap::GetCPUDescriptorHandle(int index) const
	{
		return CD3DX12_CPU_DESCRIPTOR_HANDLE(
			GetCPUDescriptorHandleForHeapStart(),
			index, m_incrementSize
			);
	}

	D3D12_GPU_DESCRIPTOR_HANDLE CDX12DescriptorHeap::GetGPUDescriptorHandleForHeapStart() const
	{
		if(!IsValid()) {
			return D3D12_GPU_DESCRIPTOR_HANDLE();
		}

		return m_pIDescriptorHeap->GetGPUDescriptorHandleForHeapStart();
	}

	CD3DX12_GPU_DESCRIPTOR_HANDLE CDX12DescriptorHeap::GetGPUDescriptorHandle(int index) const
	{
		return CD3DX12_GPU_DESCRIPTOR_HANDLE(
			GetGPUDescriptorHandleForHeapStart(),
			index, m_incrementSize
			);
	}

	ID3D12DescriptorHeap* CDX12DescriptorHeap::Interface()
	{
		return m_pIDescriptorHeap;
	}
	const ID3D12DescriptorHeap* CDX12DescriptorHeap::Interface() const
	{
		return m_pIDescriptorHeap;
	}

}	// namespace ng
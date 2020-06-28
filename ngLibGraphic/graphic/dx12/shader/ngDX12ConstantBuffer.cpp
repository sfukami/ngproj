/*!
* @file		ngDX12ConstantBuffer.cpp
* @brief	DX12コンスタントバッファ
* @date		2019-08-03
* @author	s.fukami
*/

#include <d3d12.h>
#include "ngLibCore/common/ngCommon.h"
#include "../common/ngDX12Common.h"
#include "../device/ngDX12Device.h"
#include "../descriptor/ngDX12DescriptorHeap.h"
#include "ngDX12ConstantBuffer.h"

namespace ng
{
	CDX12ConstantBuffer::CDX12ConstantBuffer()
		: m_bufSize(0)
	{
	}
	CDX12ConstantBuffer::~CDX12ConstantBuffer()
	{
		Destroy();
	}

	NG_ERRCODE CDX12ConstantBuffer::Create(
		CDX12Device& device,
		const void* pData,
		u32 size
		)
	{
		NG_ASSERT(!IsValid());

		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// 256バイトでアライメントする必要あり
		size = Align(size, 256);

		// プリミティブ描画用リソースを生成
		if(NG_FAILED(ret = m_resource.CreatePrimitiveBuffer(
			device, pData, size
			))) {
			NG_ERRLOG_C("DX12ConstantBuffer", ret, "プリミティブ描画用リソースの生成に失敗しました.")
			return ret;
		}

		m_bufSize = size;

		return ret;
	}

	void CDX12ConstantBuffer::CreateResourceView(
		CDX12Device& device,
		CDX12DescriptorHeap& heap,
		u32 heapIdx
		)
	{
		NG_ASSERT(IsValid());

		// コンスタントバッファビューを作成
		D3D12_CONSTANT_BUFFER_VIEW_DESC viewDesc = {};
		viewDesc.BufferLocation = m_resource.Interface()->GetGPUVirtualAddress();
		viewDesc.SizeInBytes = m_bufSize;

		device.Interface()->CreateConstantBufferView(&viewDesc, heap.GetCPUDescriptorHandle(heapIdx));
	}

	NG_ERRCODE CDX12ConstantBuffer::CopyData(
		const void* pData,
		u32 size
		)
	{
		NG_ASSERT(IsValid());
		
		return m_resource.CopyData(pData, size);
	}

	void CDX12ConstantBuffer::Destroy()
	{
		m_resource.Destroy();
	}

	bool CDX12ConstantBuffer::IsValid() const
	{
		return m_resource.IsValid();
	}

	CDX12Resource& CDX12ConstantBuffer::GetResource()
	{
		return m_resource;
	}
	const CDX12Resource& CDX12ConstantBuffer::GetResource() const
	{
		return m_resource;
	}

	const u32 CDX12ConstantBuffer::GetBufferSize() const
	{
		return m_bufSize;
	}

}	// namespace ng
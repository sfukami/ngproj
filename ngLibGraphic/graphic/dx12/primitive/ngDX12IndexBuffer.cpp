/*!
* @file		ngDX12IndexBuffer.cpp
* @brief	DX12インデックスバッファ
* @date		2019-07-25
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "../common/ngDX12Common.h"
#include "ngDX12IndexBuffer.h"

namespace ng
{
	CDX12IndexBuffer::CDX12IndexBuffer()
		: m_indexNum(0)
	{
	}

	CDX12IndexBuffer::~CDX12IndexBuffer()
	{
		Destroy();
	}

	NG_ERRCODE CDX12IndexBuffer::Create(
		CDX12Device& device,
		const void* pIndices,
		u32 size
		)
	{
		NG_ASSERT(!IsValid());

		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// プリミティブ描画用リソースを生成
		if(NG_FAILED(ret = m_resource.CreatePrimitiveBuffer(
			device, pIndices, size
			))) {
			NG_ERRLOG_C("DX12IndexBuffer", ret, "DX12インデックスバッファの生成に失敗しました.");
			return ret;
		}

		m_indexNum = size/sizeof(u32);

		// 頂点バッファビュー記述を設定
		m_view.BufferLocation = m_resource.Interface()->GetGPUVirtualAddress();
		m_view.SizeInBytes = size;
		m_view.Format = DXGI_FORMAT_R32_UINT;

		return ret;
	}

	void CDX12IndexBuffer::Destroy()
	{
		m_resource.Destroy();
	}

	bool CDX12IndexBuffer::IsValid() const
	{
		return m_resource.IsValid();
	}

	CDX12Resource& CDX12IndexBuffer::GetResource()
	{
		return m_resource;
	}
	const CDX12Resource& CDX12IndexBuffer::GetResource() const
	{
		return m_resource;
	}

	const D3D12_INDEX_BUFFER_VIEW& CDX12IndexBuffer::GetIndexBufferView() const
	{
		return m_view;
	}

	u32 CDX12IndexBuffer::GetIndexNum() const
	{
		return m_indexNum;
	}

}	// namespace ng
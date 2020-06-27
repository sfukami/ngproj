/*!
* @file		ngDX12VertexBuffer.cpp
* @brief	DX12頂点バッファ
* @date		2018-01-20
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "../common/ngDX12Common.h"
#include "ngDX12VertexBuffer.h"

namespace ng
{
	CDX12VertexBuffer::CDX12VertexBuffer()
		: m_vertexNum(0)
	{
	}

	CDX12VertexBuffer::~CDX12VertexBuffer()
	{
		Destroy();
	}

	NG_ERRCODE CDX12VertexBuffer::Create(
		CDX12Device& device,
		const void* pVertices,
		u32 size,
		u32 stride
		)
	{
		NG_ASSERT(!IsValid());

		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// プリミティブ描画用リソースを生成
		if(NG_FAILED(ret = m_resource.CreatePrimitiveBuffer(
			device, pVertices, size
			))) {
			NG_ERRLOG_C("DX12VertexBuffer", ret, "DX12頂点バッファの生成に失敗しました.");
			return ret;
		}

		m_vertexNum = size/stride;

		// 頂点バッファビュー記述を設定
		m_view.BufferLocation = m_resource.Interface()->GetGPUVirtualAddress();
		m_view.StrideInBytes = stride;
		m_view.SizeInBytes = size;

		return ret;
	}

	void CDX12VertexBuffer::Destroy()
	{
		m_resource.Destroy();
	}

	bool CDX12VertexBuffer::IsValid() const
	{
		return m_resource.IsValid();
	}

	CDX12Resource& CDX12VertexBuffer::GetResource()
	{
		return m_resource;
	}
	const CDX12Resource& CDX12VertexBuffer::GetResource() const
	{
		return m_resource;
	}

	const D3D12_VERTEX_BUFFER_VIEW& CDX12VertexBuffer::GetVertexBufferView() const
	{
		return m_view;
	}

	u32 CDX12VertexBuffer::GetVertexNum() const
	{
		return m_vertexNum;
	}

}	// namespace ng
/*!
* @file		ngDX12Polygon.cpp
* @brief	DX12ポリゴン
* @date		2018-07-27
* @author	s.fukami
*/

#include <d3dx12.h>
#include "ngLibCore/common/ngCommon.h"
#include "../common/ngDX12Common.h"
#include "../command/list/ngDX12CommandList.h"
#include "ngDX12Polygon.h"

namespace ng
{
	CDX12Polygon::CDX12Polygon()
		: m_primitiveTopology(D3D_PRIMITIVE_TOPOLOGY_UNDEFINED)
	{
	}

	CDX12Polygon::~CDX12Polygon()
	{
		Destroy();
	}

	NG_ERRCODE CDX12Polygon::Create(
		CDX12Device& device,
		const void* pVertices,
		u32 vertexDataSize,
		u32 vertexStride,
		D3D_PRIMITIVE_TOPOLOGY primitiveTopology,
		const u32* pIndices,
		u32 indexDataSize
		)
	{
		NG_ASSERT(!IsValid());

		NG_ERRCODE ret = m_vb.Create(
			device, pVertices, vertexDataSize, vertexStride
			);
		if(NG_FAILED(ret)) {
			return ret;
		}

		if(pIndices != nullptr) {
			ret = m_ib.Create(
				device, pIndices, indexDataSize
				);
			if(NG_FAILED(ret)) {
				return ret;
			}
		}

		m_primitiveTopology = primitiveTopology;

		return ret;
	}

	void CDX12Polygon::Render(
		CDX12CommandList& commandList
		) const
	{
		NG_ASSERT(IsValid());

		CDX12CommandList::DX12IfType* pIf = commandList.Interface();

		pIf->IASetPrimitiveTopology(m_primitiveTopology);
		pIf->IASetVertexBuffers(0, 1, &m_vb.GetVertexBufferView());
		if(m_ib.IsValid()) {
			pIf->IASetIndexBuffer(&m_ib.GetIndexBufferView());
			pIf->DrawIndexedInstanced(m_ib.GetIndexNum(), 1, 0, 0, 0);
		}
		else {
			pIf->DrawInstanced(m_vb.GetVertexNum(), 1, 0, 0);
		}
	}

	void CDX12Polygon::Destroy()
	{
		m_ib.Destroy();
		m_vb.Destroy();
	}

	bool CDX12Polygon::IsValid() const
	{
		return m_vb.IsValid();
	}

}	// namespace ng
/*!
* @file		ngDX12MeshSquare.cpp
* @brief	DX12ポリゴン 矩形
* @date		2018-07-27
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "ngDX12ShapeSquare.h"
#include "../ngDX12VertexLayout.h"
#include "ngLibGraphic/model/ngVertexFormat.h"

namespace ng
{
	CDX12ShapeSquare::CDX12ShapeSquare()
	{
	}

	CDX12ShapeSquare::~CDX12ShapeSquare()
	{
		Destroy();
	}

	NG_ERRCODE CDX12ShapeSquare::Create(
		CDX12Device& device
		, float width
		, float height
		, bool isSprite
		)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		float w2 = width * 0.5f;
		float h2 = height * 0.5f;

		if(isSprite) {
			const VertexFormat::Sprite vertices[] = {
				{{ -w2,  h2, 0}, Vector4::ONE, {0, 0}},	// 0
				{{  w2,  h2, 0}, Vector4::ONE, {1, 0}},	// 1
				{{ -w2, -h2, 0}, Vector4::ONE, {0, 1}},	// 2
				{{  w2, -h2, 0}, Vector4::ONE, {1, 1}},	// 3
			};
			ret = _createPolygon(device, vertices, sizeof(vertices), sizeof(vertices[0]));
		} else {
			const VertexFormat::Static vertices[] = {
				{{ -w2,  h2, 0}, Vector3::AXIS_Z, {0, 0}},	// 0
				{{  w2,  h2, 0}, Vector3::AXIS_Z, {1, 0}},	// 1
				{{ -w2, -h2, 0}, Vector3::AXIS_Z, {0, 1}},	// 2
				{{  w2, -h2, 0}, Vector3::AXIS_Z, {1, 1}},	// 3
			};
			ret = _createPolygon(device, vertices, sizeof(vertices), sizeof(vertices[0]));
		}

		return ret;
	}

	void CDX12ShapeSquare::Render(
		CDX12CommandList& commandList
		) const
	{
		m_polygon.Render(commandList);
	}

	void CDX12ShapeSquare::Destroy()
	{
		m_polygon.Destroy();
	}

	const DX12VertexLayout* CDX12ShapeSquare::GetVertexLayout() const
	{
		return &DX12GetVertexLayout(eVertexLayout::STATIC);
	}

	NG_ERRCODE CDX12ShapeSquare::_createPolygon(CDX12Device& device, const void* pVertices, u32 vertexDataSize, u32 vertexStride)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		if(NG_FAILED(ret = m_polygon.Create(
			device,
			pVertices,
			vertexDataSize,
			vertexStride,
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP
			))) {
			NG_ERRLOG_C("DX12ShapeSquare", ret, "DX12ポリゴンの生成に失敗しました.");
			return ret;
		}

		return ret;
	}

}	// namespace ng
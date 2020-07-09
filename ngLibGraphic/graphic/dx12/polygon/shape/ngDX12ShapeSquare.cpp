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
		)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		const VertexFormat::Static vertices[] = {
			{{ -1,  1, 0}, Vector3::ZERO, {0, 0}},	// 0
			{{  1,  1, 0}, Vector3::ZERO, {1, 0}},	// 1
			{{ -1, -1, 0}, Vector3::ZERO, {0, 1}},	// 2
			{{  1, -1, 0}, Vector3::ZERO, {1, 1}},	// 3
		};

		if(NG_FAILED(ret = m_polygon.Create(
			device,
			vertices,
			sizeof(vertices),
			sizeof(vertices[0]),
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP
			))) {
			NG_ERRLOG_C("DX12ShapeSquare", ret, "DX12ポリゴンの生成に失敗しました.");
			return ret;
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

}	// namespace ng
/*
* @file		ngDX12ShapeBox.cpp
* @brief	DX12ポリゴン ボックス
* @date		2018-07-28
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "ngDX12ShapeBox.h"
#include "../ngDX12VertexLayout.h"
#include "ngLibGraphic/model/ngVertexFormat.h"

namespace ng
{
	CDX12ShapeBox::CDX12ShapeBox()
	{

	}

	CDX12ShapeBox::~CDX12ShapeBox()
	{
		Destroy();
	}

	NG_ERRCODE CDX12ShapeBox::Create(
		CDX12Device& device
		, float width
		, float height
		, float depth
		)
	{
		const float w = width * 0.5f, h = height * 0.5f, d = depth * 0.5f;
		const Vector3 nx = Vector3::AXIS_X;
		const Vector3 ny = Vector3::AXIS_Y;
		const Vector3 nz = Vector3::AXIS_Z;
		
		const VertexFormat::Static vertices[] = {
			// near
			{{ -w,  h, -d}, -nz, {0, 0}},		// 0
			{{  w,  h, -d}, -nz, {1, 0}},		// 1
			{{ -w, -h, -d}, -nz, {0, 1}},		// 2
			{{  w, -h, -d}, -nz, {1, 1}},		// 3
			// left
			{{ -w,  h,  d}, -nx, {0, 0}},		// 4
			{{ -w,  h, -d}, -nx, {1, 0}},		// 5
			{{ -w, -h,  d}, -nx, {0, 1}},		// 6
			{{ -w, -h, -d}, -nx, {1, 1}},		// 7
			// top
			{{ -w,  h,  d},  ny, {0, 0}},		// 8
			{{  w,  h,  d},  ny, {1, 0}},		// 9
			{{ -w,  h, -d},  ny, {0, 1}},		// 10
			{{  w,  h, -d},  ny, {1, 1}},		// 11
			// right
			{{  w,  h, -d},  nx, {0, 0}},		// 12
			{{  w,  h,  d},  nx, {1, 0}},		// 13
			{{  w, -h, -d},  nx, {0, 1}},		// 14
			{{  w, -h,  d},  nx, {1, 1}},		// 15
			// bottom
			{{ -w, -h, -d}, -ny, {0, 0}},		// 16
			{{  w, -h, -d}, -ny, {1, 0}},		// 17
			{{ -w, -h,  d}, -ny, {0, 1}},		// 18
			{{  w, -h,  d}, -ny, {1, 1}},		// 19
			// far
			{{  w,  h,  d},  nz, {0, 0}},		// 20
			{{ -w,  h,  d},  nz, {1, 0}},		// 21
			{{  w, -h,  d},  nz, {0, 1}},		// 22
			{{ -w, -h,  d},  nz, {1, 1}},		// 23
		};
		static const u32 indices[] = {
			 0,  1,  2,  1,  3,  2,
			 4,  5,  6,  5,  7,  6,
			 8,  9, 10,  9, 11, 10,
			12, 13, 14, 13, 15, 14,
			16, 17, 18, 17, 19, 18,
			20, 21, 22, 21, 23, 22,
		};

		NG_ERRCODE ret = m_polygon.Create(
			device,
			vertices,
			sizeof(vertices),
			sizeof(vertices[0]),
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
			indices,
			sizeof(indices)
			);

		return ret;
	}

	void CDX12ShapeBox::Render(
		CDX12CommandList& commandList
		) const
	{
		m_polygon.Render(commandList);
	}

	void CDX12ShapeBox::Destroy()
	{
		m_polygon.Destroy();
	}

	const DX12VertexLayout* CDX12ShapeBox::GetVertexLayout() const
	{
		return &DX12GetVertexLayout(eVertexLayout::STATIC);
	}

}	// namespace ng
/*!
* @file		ngCamera.cpp
* @brief	カメラ
* @date		2019-08-07
* @author	s.fukami
*/

#include "ngLibCore/geometry/vector/ngVectorOp.h"
#include "ngLibCore/geometry/matrix/ngMatrixOp.h"
#include "ngCamera.h"

namespace ng
{
	CCamera::CCamera()
		: m_pos(0, 0, 0)
		, m_at(0, 0, -1)
		, m_up(0, 1, 0)
		, m_view(Matrix4::IDENTITY)
		, m_coordSys(eCoordSys::LEFT_HAND)
	{
	}
	CCamera::~CCamera()
	{
	}

	void CCamera::CalcViewMatrix()
	{
		if(m_coordSys == eCoordSys::LEFT_HAND) {
			MatrixOp::ViewLH(m_view, m_pos, m_at, m_up);
		}
		else if(m_coordSys == eCoordSys::RIGHT_HAND) {
			MatrixOp::ViewRH(m_view, m_pos, m_at, m_up);
		}
	}

	void CCamera::SetPos(const Vector3& pos)
	{
		m_pos = pos;
	}
	const Vector3& CCamera::GetPos() const
	{
		return m_pos;
	}

	void CCamera::SetAtPos(const Vector3& at)
	{
		m_at = at;
	}
	const Vector3& CCamera::GetAtPos() const
	{
		return m_at;
	}

	void CCamera::SetUpVec(const Vector3& up)
	{
		m_up = up;
	}
	const Vector3& CCamera::GetUpVec() const
	{
		return m_up;
	}
	
	void CCamera::MoveStraightToAtPos(float length)
	{
		Vector3 dir;
		VectorOp::Normalize(dir, m_at-m_pos);
		m_pos += dir * length;
	}

	void CCamera::RotateAroundAtPos(float radH, float radV)
	{
		Vector3 toAt = m_at-m_pos;
		// TODO: 回転に違和感.ワールドX軸周りの回転とする
		/*
		// カメラのX方向の軸を算出
		Vector3 side;
		VectorOp::Cross(side, toAt, m_up);
		side.y = 0;
		VectorOp::Normalize(side, side);
		*/

		Matrix4 rotHMat, rotVMat;
		MatrixOp::RotationAxis(rotHMat, Vector3::AXIS_Y, radH);
		//MatrixOp::RotationAxis(rotVMat, side, radV);
		MatrixOp::RotationAxis(rotVMat, Vector3::AXIS_X, radV);
		MatrixOp::Multiply(rotHMat, rotHMat, rotVMat);

		VectorOp::Transform(toAt, toAt, rotHMat);
		VectorOp::Transform(m_up, m_up, rotHMat);

		m_pos = m_at - toAt;
	}

	const Matrix4& CCamera::GetViewMatrix() const
	{
		return m_view;
	}

	void CCamera::SetCoordSys(eCoordSys coordSys)
	{
		m_coordSys = coordSys;
	}
	eCoordSys CCamera::GetCoordSys() const
	{
		return m_coordSys;
	}

}	// namespace ng
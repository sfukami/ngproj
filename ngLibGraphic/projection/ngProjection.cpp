/*!
* @file		ngProjection.cpp
* @brief	射影変換
* @date		2019-08-07
* @author	s.fukami
*/

#include "ngLibCore/math/ngMath.h"
#include "ngLibCore/geometry/matrix/ngMatrixOp.h"
#include "ngProjection.h"

namespace ng
{
	CProjection::CProjection()
		: m_width(480)
		, m_height(640)
		, m_near(0.1f)
		, m_far(100.f)
		, m_fov(DegreeToRadian(45.f))
		, m_proj(Matrix4::IDENTITY)
		, m_coordSys(eCoordSys::LEFT_HAND)
		, m_projMethod(PERSPECTIVE)
	{

	}
	CProjection::~CProjection()
	{

	}

	void CProjection::CalcProjMatrix()
	{
		if(m_projMethod == PERSPECTIVE) {
			if(m_coordSys == eCoordSys::LEFT_HAND) {
				MatrixOp::ProjPersLH(
					m_proj,
					m_fov,
					m_width / (f32)m_height,
					m_near,
					m_far
					);
			}
			else if(m_coordSys == eCoordSys::RIGHT_HAND) {
				MatrixOp::ProjPersRH(
					m_proj,
					m_fov,
					m_width / (f32)m_height,
					m_near,
					m_far
					);
			}
		}
		else if(m_projMethod == ORTHOGONAL) {
			if(m_coordSys == eCoordSys::LEFT_HAND) {
				MatrixOp::ProjOrthoLH(
					m_proj,
					(f32)m_width,
					(f32)m_height,
					m_near,
					m_far
					);
			}
			else if(m_coordSys == eCoordSys::RIGHT_HAND) {
				MatrixOp::ProjOrthoRH(
					m_proj,
					(f32)m_width,
					(f32)m_height,
					m_near,
					m_far
					);
			}
		}
	}

	void CProjection::SetWidth(int width)
	{
		m_width = width;
	}
	int CProjection::GetWidth() const
	{
		return m_width;
	}

	void CProjection::SetHeight(int height)
	{
		m_height = height;
	}
	int CProjection::GetHeight() const
	{
		return m_height;
	}

	void CProjection::SetNear(float _near)
	{
		m_near = _near;
	}
	float CProjection::GetNear() const
	{
		return m_near;
	}

	void CProjection::SetFar(float _far)
	{
		m_far = _far;
	}
	float CProjection::GetFar() const
	{
		return m_far;
	}

	void CProjection::SetFOV(float rad)
	{
		m_fov = rad;
	}
	float CProjection::GetFOV() const
	{
		return m_fov;
	}

	const Matrix4& CProjection::GetProjMatrix() const
	{
		return m_proj;
	}

	void CProjection::SetCoordSys(eCoordSys coordSys)
	{
		m_coordSys = coordSys;
	}
	eCoordSys CProjection::GetCoordSys() const
	{
		return m_coordSys;
	}

	void CProjection::SetProjMethod(eProjMethod projMethod)
	{
		m_projMethod = projMethod;
	}
	CProjection::eProjMethod CProjection::GetProjMethod() const
	{
		return m_projMethod;
	}

}	// namespace ng
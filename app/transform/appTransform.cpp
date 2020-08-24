/*!
* @file		appTransform.cpp
* @brief	トランスフォーム
* @date		2020-08-23
* @author	s.fukami
*/

#include "appTransform.h"

namespace app
{
	CTransform::CTransform()
		: m_scale(ng::Vector3::ONE)
		, m_rotation(ng::Quaternion::IDENTITY)
	{
	}
	CTransform::~CTransform()
	{
	}

	void CTransform::SetPosition(const ng::Vector3& position)
	{
		m_position = position;
	}

	void CTransform::SetScale(const ng::Vector3& scale)
	{
		m_scale = scale;
	}

	void CTransform::SetRotation(const ng::Quaternion& rotation)
	{
		m_rotation = rotation;
	}

	const ng::Vector3& CTransform::GetPosition() const
	{
		return m_position;
	}

	const ng::Vector3& CTransform::GetScale() const
	{
		return m_scale;
	}

	const ng::Quaternion& CTransform::GetRotation() const
	{
		return m_rotation;
	}

	void CTransform::CalcWorldMatrix(ng::Matrix4& dst)
	{
		// スケーリング
		ng::MatrixOp::Scaling(dst, m_scale.x, m_scale.y, m_scale.z);

		// 回転
		ng::Matrix4 rMat;
		ng::QuaternionOp::ToMatrix(rMat, m_rotation);
		ng::MatrixOp::Multiply(dst, dst, rMat);

		// 移動
		dst.m41 = m_position.x;
		dst.m42 = m_position.y;
		dst.m43 = m_position.z;
	}

}	// namespace app
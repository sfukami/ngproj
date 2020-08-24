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
		, m_isChanged(true)
	{
	}
	CTransform::~CTransform()
	{
	}

	void CTransform::SetPosition(const ng::Vector3& position)
	{
		m_position = position;
		m_isChanged = true;
	}

	void CTransform::SetScale(const ng::Vector3& scale)
	{
		m_scale = scale;
		m_isChanged = true;
	}

	void CTransform::SetRotation(const ng::Quaternion& rotation)
	{
		m_rotation = rotation;
		m_isChanged = true;
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

	const ng::Matrix4& CTransform::GetWorldMatrix()
	{
		if(m_isChanged) {
			_calcWorldMatrix();
			m_isChanged = false;
		}

		return m_worldMat;
	}

	void CTransform::_calcWorldMatrix()
	{
		// スケーリング
		ng::MatrixOp::Scaling(m_worldMat, m_scale.x, m_scale.y, m_scale.z);

		// 回転
		ng::Matrix4 rMat;
		ng::QuaternionOp::ToMatrix(rMat, m_rotation);
		ng::MatrixOp::Multiply(m_worldMat, m_worldMat, rMat);

		// 移動
		m_worldMat.m41 = m_position.x;
		m_worldMat.m42 = m_position.y;
		m_worldMat.m43 = m_position.z;
	}

}	// namespace app
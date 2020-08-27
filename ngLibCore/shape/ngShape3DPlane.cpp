/*!
* @file		ngShape3DPlane.cpp
* @brief	3D形状 無限平面
* @date		2019-07-19
* @author	s.fukami
*/

#include "ngLibCore/shape/ngShape3DPlane.h"
#include "ngLibCore/geometry/vector/ngVectorOp.h"
#include "ngLibCore/collision/ngCollision3DOp.h"

namespace ng
{
	void Shape3DPlane::CalcPlane(const Vector3& p1, const Vector3& p2, const Vector3& p3)
	{
		VectorOp::Cross(normal, p2-p1, p3-p1);
		VectorOp::Normalize(normal, normal);
		distance = VectorOp::Dot(normal, p1);
	}

	bool Shape3DPlane::CheckHit(const Shape3DBox& other) const
	{
		return CollisionOp::CheckHitBoxAndPlane(other, *this);
	}
	bool Shape3DPlane::CheckHit(const Shape3DSphere& other) const
	{
		return CollisionOp::CheckHitSphereAndPlane(other, *this);
	}
	bool Shape3DPlane::CheckHit(const Shape3DOBB& other) const
	{
		return CollisionOp::CheckHitOBBAndPlane(other, *this);
	}

}	// namespace ng

/*!
* @file		ngShape3DSphere.cpp
* @brief	3D形状 球
* @date		2016-02-10
* @author	s.fukami
*/

#include "ngShape3DSphere.h"
#include "ngLibCore/collision/ngCollision3DOp.h"

namespace ng
{
	bool Shape3DSphere::CheckHit(const struct Shape3DSphere& other) const
	{
		return CollisionOp::CheckHitSpheres(*this, other);
	}
	bool Shape3DSphere::CheckHit(const struct Shape3DBox& other) const
	{
		return CollisionOp::CheckHitBoxAndSphere(other, *this);
	}
	bool Shape3DSphere::CheckHit(const struct Vector3& other) const
	{
		return CollisionOp::CheckHitSphereAndPos(*this, other);
	}
	bool Shape3DSphere::CheckHit(const Shape3DPlane& other) const
	{
		return CollisionOp::CheckHitSphereAndPlane(*this, other);
	}

}	// namespace ng

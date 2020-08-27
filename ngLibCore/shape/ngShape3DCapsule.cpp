/*!
* @file		ngShape3DCapsule.cpp
* @brief	3D形状 カプセル（球スイープ）
* @date		2019-07-19
* @author	s.fukami
*/

#include "ngShape3DCapsule.h"
#include "ngLibCore/collision/ngCollision3DOp.h"

namespace ng
{
	bool Shape3DCapsule::CheckHit(const struct Shape3DCapsule& other) const
	{
		return CollisionOp::CheckHitCapsules(*this, other);
	}
	bool Shape3DCapsule::CheckHit(const struct Shape3DSphere& other) const
	{
		return CollisionOp::CheckHitSphereAndCapsule(other, *this);
	}
	bool Shape3DCapsule::CheckHit(const struct Vector3& other) const
	{
		return CollisionOp::CheckHitCapsuleAndPos(*this, other);
	}

}	// namespace ng

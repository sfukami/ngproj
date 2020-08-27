/*!
* @file		ngShape2DCapsule.cpp
* @brief	2D形状 カプセル（球スイープ）
* @date		2019-07-12
* @author	s.fukami
*/

#include "ngShape2DCapsule.h"
#include "ngLibCore/collision/ngCollision2DOp.h"

namespace ng
{
	bool Shape2DCapsule::CheckHit(const struct Shape2DCapsule& other) const
	{
		return CollisionOp::CheckHitCapsules(*this, other);
	}
	bool Shape2DCapsule::CheckHit(const struct Shape2DCircle& other) const
	{
		return CollisionOp::CheckHitCircleAndCapsule(other, *this);
	}
	bool Shape2DCapsule::CheckHit(const struct Vector2& other) const
	{
		return CollisionOp::CheckHitCapsuleAndPos(*this, other);
	}

}	// namespace ng

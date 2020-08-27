/*!
* @file		ngShape3DBox.cpp
* @brief	3D形状 Box(AABB)
* @date		2016-02-10
* @author	s.fukami
*/

#include "ngShape3DBox.h"
#include "ngLibCore/collision/ngCollision3DOp.h"

namespace ng
{
	bool Shape3DBox::CheckHit(const Shape3DBox& other) const
	{
		return CollisionOp::CheckHitBoxes(*this, other);
	}
	bool Shape3DBox::CheckHit(const Shape3DSphere& other) const
	{
		return CollisionOp::CheckHitBoxAndSphere(*this, other);
	}
	bool Shape3DBox::CheckHit(const Vector3& other) const
	{
		return CollisionOp::CheckHitBoxAndPos(*this, other);
	}
	bool Shape3DBox::CheckHit(const Shape3DPlane& other) const
	{
		return CollisionOp::CheckHitBoxAndPlane(*this, other);
	}

}	// namespace ng

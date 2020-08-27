/*!
* @file		ngShape2DCircle.h
* @brief	2D形状 円
* @date		2015-10-10
* @author	s.fukami
*/

#include "ngShape2DCircle.h"
#include "ngLibCore/collision/ngCollision2DOp.h"

namespace ng
{
	bool Shape2DCircle::CheckHit(const Shape2DCircle& other) const
	{
		return CollisionOp::CheckHitCircles(*this, other);
	}
	bool Shape2DCircle::CheckHit(const Shape2DSquare& other) const
	{
		return CollisionOp::CheckHitSquareAndCircle(other, *this);
	}
	bool Shape2DCircle::CheckHit(const Vector2& other) const
	{
		return CollisionOp::CheckHitCircleAndPos(*this, other);
	}

}	// namespace ng

/*!
* @file		ngShape2DSquare.cpp
* @brief	2D形状 矩形
* @date		2015-10-10
* @author	s.fukami
*/

#include "ngShape2DSquare.h"
#include "ngLibCore/collision/ngCollision2DOp.h"

namespace ng
{
	bool Shape2DSquare::CheckHit(const Shape2DSquare& other) const
	{
		return CollisionOp::CheckHitSquares(*this, other);
	}
	bool Shape2DSquare::CheckHit(const Shape2DCircle& other) const
	{
		return CollisionOp::CheckHitSquareAndCircle(*this, other);
	}
	bool Shape2DSquare::CheckHit(const Vector2& other) const
	{
		return CollisionOp::CheckHitSquareAndPos(*this, other);
	}

}	// namespace ng
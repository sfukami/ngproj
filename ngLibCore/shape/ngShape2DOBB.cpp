/*!
* @file		ngShape2DOBB.cpp
* @brief	2D形状 OBB
* @date		2019-07-15
* @author	s.fukami
*/

#include "ngShape2DOBB.h"
#include "ngLibCore/geometry/vector/ngVectorOp.h"
#include "ngLibCore/collision/ngCollision2DOp.h"

namespace ng
{
	void Shape2DOBB::UpdateAxis()
	{
		VectorOp::Rotate(axisY, Vector2::AXIS_Y, rotation);
		VectorOp::Rotate(axisX, Vector2::AXIS_X, rotation);
	}

	bool Shape2DOBB::CheckHit(const Shape2DOBB& other) const
	{
		return CollisionOp::CheckHitOBBs(*this, other);
	}

}	// namespace ng

/*!
* @file		ngShape3DOBB.cpp
* @brief	3D形状 OBB
* @date		2016-03-08
* @author	s.fukami
*/

#include "ngShape3DOBB.h"
#include "ngLibCore/geometry/vector/ngVectorOp.h"
#include "ngLibCore/geometry/quaternion/ngQuaternion.h"
#include "ngLibCore/geometry/quaternion/ngQuaternionOp.h"
#include "ngLibCore/collision/ngCollision3DOp.h"

namespace ng
{
	void Shape3DOBB::UpdateAxis()
	{
		Quaternion q;
		QuaternionOp::FromEulerAngle(q, rotY, rotX, rotZ);
		QuaternionOp::Rotate(axisY, Vector3::AXIS_Y, q);
		QuaternionOp::Rotate(axisX, Vector3::AXIS_X, q);
		VectorOp::Cross(axisX, axisY, axisZ);
	}

	bool Shape3DOBB::CheckHit(const Shape3DOBB& other) const
	{
		return CollisionOp::CheckHitOBBs(*this, other);
	}
	bool Shape3DOBB::CheckHit(const Shape3DPlane& other) const
	{
		return CollisionOp::CheckHitOBBAndPlane(*this, other);
	}

}	// namespace ng

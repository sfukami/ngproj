/*!
* @file		ngShape3DSegment.cpp
* @brief	2D形状 線分
* @date		2019-07-19
* @author	s.fukami
*/

#include "ngShape3DSegment.h"
#include "ngLibCore/geometry/ngGeomMath.h"
#include "ngLibCore/geometry/vector/ngVectorOp.h"

namespace ng
{
	Vector3 Shape3DSegment::Center() const
	{
		return (begin+end)*0.5f;
	}

	float Shape3DSegment::Length() const
	{
		return VectorOp::Length(Vector());
	}
	float Shape3DSegment::LengthSq() const
	{
		return VectorOp::LengthSq(Vector());
	}

	float Shape3DSegment::CalcShotestDistSq(
		const Shape3DSegment& opponent,
		float* pS, float* pT, Vector3* pSPos, Vector3* pTPos
		) const
	{
		return GeomMath::CalcShotestDistSqSegments(
			begin, end, opponent.begin, opponent.end,
			pS, pT, pSPos, pTPos
			);
	}

}	// namespace ng

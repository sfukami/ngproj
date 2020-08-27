/*!
* @file		ngShape2DSegment.cpp
* @brief	2D形状 線分
* @date		2019-07-12
* @author	s.fukami
*/

#include "ngShape2DSegment.h"
#include "ngLibCore/geometry/ngGeomMath.h"
#include "ngLibCore/geometry/vector/ngVectorOp.h"

namespace ng
{
	Vector2 Shape2DSegment::Center() const
	{
		return (begin+end)*0.5f;
	}

	float Shape2DSegment::Length() const
	{
		return VectorOp::Length(Vector());
	}
	float Shape2DSegment::LengthSq() const
	{
		return VectorOp::LengthSq(Vector());
	}

	float Shape2DSegment::CalcShotestDistSq(
		const Shape2DSegment& opponent,
		float* pS, float* pT, Vector2* pSPos, Vector2* pTPos
		) const
	{
		return GeomMath::CalcShotestDistSqSegments(
			begin, end, opponent.begin, opponent.end,
			pS, pT, pSPos, pTPos
			);
	}

}	// namespace ng

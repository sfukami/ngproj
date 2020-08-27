/*!
* @file		ngCollision2DOp.cpp
* @brief	2D衝突判定
* @date		2015-10-21
* @author	s.fukami
*/

#include "ngCollision2DOp.h"
#include "ngLibCore/math/ngMath.h"
#include "ngLibCore/geometry/ngGeomMath.h"
#include "ngLibCore/geometry/vector/ngVectorOp.h"
#include "ngLibCore/geometry/vector/ngVector2.h"
#include "ngLibCore/shape/ngShape2DSquare.h"
#include "ngLibCore/shape/ngShape2DCircle.h"
#include "ngLibCore/shape/ngShape2DCapsule.h"
#include "ngLibCore/shape/ngShape2DSegment.h"
#include "ngLibCore/shape/ngShape2DOBB.h"

namespace ng
{
	namespace CollisionOp
	{
		bool CheckHitSquares(const Shape2DSquare& s1, const Shape2DSquare& s2)
		{
			Vector2 min1, max1, min2, max2;
			s1.MinPos(min1);
			s1.MaxPos(max1);
			s2.MinPos(min2);
			s2.MaxPos(max2);

			if(
				max1.x < min2.x ||
				max1.y < min2.y ||
				min1.x > max2.x ||
				min1.y > max2.y
				) {
				return false;
			}
			return true;
		}
		bool CheckHitSquareAndPos(const Shape2DSquare& s, const Vector2& pos)
		{
			Vector2 min, max;
			s.MinPos(min);
			s.MaxPos(max);

			if(
				max.x < pos.x ||
				max.y < pos.y ||
				min.x > pos.x ||
				min.y > pos.y
				) {
				return false;
			}
			return true;
		}

		bool CheckHitCircles(const Shape2DCircle& c1, const Shape2DCircle& c2)
		{
			float radsum = c1.radius+c2.radius;
			return (VectorOp::LengthSq(c1.center-c2.center) < radsum*radsum);
		}
		bool CheckHitCircleAndPos(const Shape2DCircle& c, const Vector2& pos)
		{
			return (VectorOp::LengthSq(c.center-pos) < c.RadiusSq());
		}

		bool CheckHitCapsules(const Shape2DCapsule& c1, const Shape2DCapsule& c2)
		{
			float radsum = c1.radius+c2.radius;
			float lenSq = GeomMath::CalcShotestDistSqSegments(
				c1.segment.begin, c1.segment.end, c2.segment.begin, c2.segment.end
				);
			return (lenSq < radsum*radsum);
		}
		bool CheckHitCapsuleAndPos(const Shape2DCapsule& c, const Vector2& pos)
		{
			float lenSq = GeomMath::CalcShotestDistSqSegmentAndPos(c.segment.begin, c.segment.end, pos);
			return (lenSq < c.RadiusSq());
		}

		bool _checkNotOverlapedOnSeparateAxis(
			const Vector2& cv, const Vector2& sepAxis, float lenOnAxis, const Vector2& vw, const Vector2& vh
			)
		{
			return (
				lenOnAxis + Abs(VectorOp::Dot(vw, sepAxis)) + Abs(VectorOp::Dot(vh, sepAxis)) <
				Abs(VectorOp::Dot(cv, sepAxis))
				);
		}
		bool CheckHitOBBs(const Shape2DOBB& oa, const Shape2DOBB& ob)
		{
			Vector2 ab = ob.center-oa.center;
			Vector2 vecWa = oa.axisX*oa.width;
			Vector2 vecHa = oa.axisY*oa.height;
			Vector2 vecWb = ob.axisX*ob.width;
			Vector2 vecHb = ob.axisY*ob.height;

			// 分離軸:oa_X軸
			if(_checkNotOverlapedOnSeparateAxis(ab, oa.axisX, oa.WidthDiv2(), vecWb, vecHb)) { return false; }
			// 分離軸:oa_Y軸
			if(_checkNotOverlapedOnSeparateAxis(ab, oa.axisY, oa.HeightDiv2(), vecWb, vecHb)) { return false; }
			// 分離軸:ob_X軸
			if(_checkNotOverlapedOnSeparateAxis(ab, ob.axisX, ob.WidthDiv2(), vecWa, vecHa)) { return false; }
			// 分離軸:ob_Y軸
			if(_checkNotOverlapedOnSeparateAxis(ab, ob.axisY, ob.HeightDiv2(), vecWa, vecHa)) { return false; }

			return true;
		}

		bool CheckHitSquareAndCircle(const Shape2DSquare& s, const Shape2DCircle& c)
		{
			// TODO: 最短距離算出した場合とどちらが早いか要検証
			/*
				矩形と円の位置関係を4パターンに場合分け
				傾きが無いため内積不要
					  1
					-----
				  3 |   | 4
					-----
					  2
			*/
			const Vector2& cc = c.center;
			const float top = s.Top();
			const float btm = s.Bottom();
			const float left = s.Left();
			const float right = s.Right();
			float lenSq = 0.f;

			// 1
			if(cc.y >= top) {
				if(cc.x < left)			lenSq = VectorOp::LengthSq(cc, s.TopLeftPos());
				else if(cc.x > right)	lenSq = VectorOp::LengthSq(cc, s.TopRightPos());
				else					lenSq = Square(cc.y-top);
			}
			// 2
			else if(cc.y <= btm) {
				if(cc.x < left)			lenSq = VectorOp::LengthSq(cc, s.BottomLeftPos());
				else if(cc.x > right)	lenSq = VectorOp::LengthSq(cc, s.BottomRightPos());
				else					lenSq = Square(btm-cc.y);
			}
			// 3
			else if(cc.x <= left) {
				if(cc.y > top)			lenSq = VectorOp::LengthSq(cc, s.TopLeftPos());
				else if(cc.x < btm)		lenSq = VectorOp::LengthSq(cc, s.BottomLeftPos());
				else					lenSq = Square(left-cc.x);
			}
			// 4
			else if(cc.x >= right) {
				if(cc.y > top)			lenSq = VectorOp::LengthSq(cc, s.TopRightPos());
				else if(cc.x < btm)		lenSq = VectorOp::LengthSq(cc, s.BottomRightPos());
				else					lenSq = Square(cc.x-right);
			}
			// 円中心が矩形内にある
			else {
				return true;
			}

			return (lenSq <= c.RadiusSq());
		}

		bool CheckHitCircleAndCapsule(const Shape2DCircle& circle, const Shape2DCapsule& capsule)
		{
			float lenSq = GeomMath::CalcShotestDistSqSegmentAndPos(
				capsule.segment.begin, capsule.segment.end, circle.center
				);

			float radsum = circle.radius + capsule.radius;
			return (lenSq < radsum*radsum);
		}

	}	// namespace CollisionOp
}	// namespace ng

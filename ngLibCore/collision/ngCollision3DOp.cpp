/*!
* @file		ngCollision3DOp.cpp
* @brief	3D衝突判定
* @date		2016-02-21
* @author	s.fukami
*/

#include "ngCollision3DOp.h"
#include "ngLibCore/math/ngMath.h"
#include "ngLibCore/geometry/ngGeomMath.h"
#include "ngLibCore/geometry/vector/ngVectorOp.h"
#include "ngLibCore/geometry/vector/ngVector3.h"
#include "ngLibCore/shape/ngShape3DBox.h"
#include "ngLibCore/shape/ngShape3DSphere.h"
#include "ngLibCore/shape/ngShape3DCapsule.h"
#include "ngLibCore/shape/ngShape3DSegment.h"
#include "ngLibCore/shape/ngShape3DOBB.h"
#include "ngLibCore/shape/ngShape3DPlane.h"

namespace ng
{ 
	namespace CollisionOp
	{
		bool CheckHitBoxes(const Shape3DBox& b1, const Shape3DBox& b2)
		{
			Vector3 min1, max1, min2, max2;
			b1.MinPos(min1);
			b1.MaxPos(max1);
			b2.MinPos(min2);
			b2.MaxPos(max2);

			if(
				max1.x < min2.x ||
				max1.y < min2.y ||
				max1.z < min2.z ||
				min1.x > max2.x ||
				min1.y > max2.y ||
				min1.z > max2.z
				) {
				return false;
			}
			return true;
		}
		bool CheckHitBoxAndPos(const Shape3DBox& b, const Vector3& pos)
		{
			Vector3 min, max;
			b.MinPos(min);
			b.MaxPos(max);

			if(
				max.x < pos.x ||
				max.y < pos.y ||
				max.z < pos.z ||
				min.x > pos.x ||
				min.y > pos.y ||
				min.z > pos.z
				) {
				return false;
			}
			return true;
		}

		bool CheckHitSpheres(const Shape3DSphere& s1, const Shape3DSphere& s2)
		{
			float radsum = s1.radius+s2.radius;
			return (VectorOp::LengthSq(s2.center-s1.center) < radsum*radsum);
		}
		bool CheckHitSphereAndPos(const Shape3DSphere& s, const Vector3& pos)
		{
			return (VectorOp::LengthSq(s.center-pos) < s.RadiusSq());
		}

		bool CheckHitCapsules(const Shape3DCapsule& c1, const Shape3DCapsule& c2)
		{
			float radsum = c1.radius+c2.radius;
			float lenSq = GeomMath::CalcShotestDistSqSegments(
				c1.segment.begin, c1.segment.end, c2.segment.begin, c2.segment.end
				);
			return (lenSq < radsum*radsum);
		}
		bool CheckHitCapsuleAndPos(const Shape3DCapsule& c, const Vector3& pos)
		{
			float lenSq = GeomMath::CalcShotestDistSqSegmentAndPos(c.segment.begin, c.segment.end, pos);
			return (lenSq < c.RadiusSq());
		}

		bool CheckHitBoxAndSphere(const Shape3DBox& b, const Shape3DSphere& s)
		{
			return (
				GeomMath::CalcShotestDistSqAABBAndPos(b.MinPos(), b.MaxPos(), s.center) < s.RadiusSq()
				);
		}

		bool _checkNotOverlapedOnSeparateAxis(
			const Vector3& cv, const Vector3& sepAxis, float lenOnAxis, const Vector3& vw, const Vector3& vh, const Vector3& vd
			)
		{
			return (
				lenOnAxis + Abs(VectorOp::Dot(vw, sepAxis)) + Abs(VectorOp::Dot(vh, sepAxis)) + Abs(VectorOp::Dot(vd, sepAxis)) <
				Abs(VectorOp::Dot(cv, sepAxis))
				);
		}
		bool _checkNotOverlapedOnSeparateAxis(
			const Vector3& cv, const Vector3& axis1, const Vector3& axis2, 
			const Vector3& vw1, const Vector3& vh1, const Vector3& vw2, const Vector3& vh2
			)
		{
			Vector3 crs;
			VectorOp::Cross(crs, axis1, axis2);
			return (
				Abs(VectorOp::Dot(vw1, crs)) + Abs(VectorOp::Dot(vh1, crs)) + 
					Abs(VectorOp::Dot(vw2, crs)) + Abs(VectorOp::Dot(vh2, crs)) <
				Abs(VectorOp::Dot(cv, crs))
				);
		}
		bool CheckHitOBBs(const Shape3DOBB& oa, const Shape3DOBB& ob)
		{
			Vector3 ab = ob.center-oa.center;
			Vector3 vecWa = oa.axisX*oa.width;
			Vector3 vecHa = oa.axisY*oa.height;
			Vector3 vecDa = oa.axisZ*oa.depth;
			Vector3 vecWb = ob.axisX*ob.width;
			Vector3 vecHb = ob.axisY*ob.height;
			Vector3 vecDb = ob.axisZ*ob.depth;

			// 分離軸:oa_X軸
			if(_checkNotOverlapedOnSeparateAxis(ab, oa.axisX, oa.WidthDiv2(), vecWb, vecHb, vecDb)) return false;
			// 分離軸:oa_Y軸
			if(_checkNotOverlapedOnSeparateAxis(ab, oa.axisY, oa.HeightDiv2(), vecWb, vecHb, vecDb)) return false;
			// 分離軸:oa_Z軸
			if(_checkNotOverlapedOnSeparateAxis(ab, oa.axisZ, oa.DepthDiv2(), vecWb, vecHb, vecDb)) return false;
			// 分離軸:ob_X軸
			if(_checkNotOverlapedOnSeparateAxis(ab, ob.axisX, ob.WidthDiv2(), vecWa, vecHa, vecDa)) return false;
			// 分離軸:ob_Y軸
			if(_checkNotOverlapedOnSeparateAxis(ab, ob.axisY, ob.HeightDiv2(), vecWa, vecHa, vecDa)) return false;
			// 分離軸:ob_Z軸
			if(_checkNotOverlapedOnSeparateAxis(ab, ob.axisZ, ob.DepthDiv2(), vecWa, vecHa, vecDa)) return false;
			// 双方の方向ベクトルに垂直な分離軸
			// 分離軸:外積_X軸X軸
			if(_checkNotOverlapedOnSeparateAxis(ab, oa.axisX, ob.axisX, vecHa, vecDa, vecHb, vecDb)) return false;
			// 分離軸:外積_X軸Y軸
			if(_checkNotOverlapedOnSeparateAxis(ab, oa.axisX, ob.axisY, vecHa, vecDa, vecWb, vecDb)) return false;
			// 分離軸:外積_X軸Z軸
			if(_checkNotOverlapedOnSeparateAxis(ab, oa.axisX, ob.axisZ, vecHa, vecDa, vecWb, vecHb)) return false;
			// 分離軸:外積_Y軸X軸
			if(_checkNotOverlapedOnSeparateAxis(ab, oa.axisY, ob.axisX, vecWa, vecDa, vecHb, vecDb)) return false;
			// 分離軸:外積_Y軸Y軸
			if(_checkNotOverlapedOnSeparateAxis(ab, oa.axisY, ob.axisY, vecWa, vecDa, vecWb, vecDb)) return false;
			// 分離軸:外積_Y軸Z軸
			if(_checkNotOverlapedOnSeparateAxis(ab, oa.axisY, ob.axisZ, vecWa, vecDa, vecWb, vecHb)) return false;
			// 分離軸:外積_Z軸X軸
			if(_checkNotOverlapedOnSeparateAxis(ab, oa.axisZ, ob.axisX, vecWa, vecHa, vecHb, vecDb)) return false;
			// 分離軸:外積_Z軸Y軸
			if(_checkNotOverlapedOnSeparateAxis(ab, oa.axisZ, ob.axisY, vecWa, vecHa, vecWb, vecDb)) return false;
			// 分離軸:外積_Z軸Z軸
			if(_checkNotOverlapedOnSeparateAxis(ab, oa.axisZ, ob.axisZ, vecWa, vecHa, vecWb, vecHb)) return false;

			return true;
		}

		bool CheckHitSphereAndCapsule(const Shape3DSphere& s, const Shape3DCapsule& c)
		{
			float lenSq = GeomMath::CalcShotestDistSqSegmentAndPos(
				c.segment.begin, c.segment.end, s.center
				);

			float radsum = s.radius + c.radius;
			return (lenSq < radsum*radsum);
		}

		bool CheckHitBoxAndPlane(const Shape3DBox& b, const Shape3DPlane& p)
		{
			float r = b.WidthDiv2()*Abs(p.normal.x) + b.HeightDiv2()*Abs(p.normal.y) + b.DepthDiv2()*Abs(p.normal.z);
			float dist = Abs(VectorOp::Dot(p.normal, b.center) - p.distance);
			return (dist <= r);
		}

		bool CheckHitSphereAndPlane(const Shape3DSphere& s, const Shape3DPlane& p)
		{
			float dist = Abs(VectorOp::Dot(p.normal, s.center) - p.distance);
			return (dist <= s.radius);
		}

		bool CheckHitOBBAndPlane(const Shape3DOBB& o, const Shape3DPlane& p)
		{
			float r =
				o.WidthDiv2()*Abs(VectorOp::Dot(p.normal, o.axisX)) + 
				o.HeightDiv2()*Abs(VectorOp::Dot(p.normal, o.axisY)) + 
				o.DepthDiv2()*Abs(VectorOp::Dot(p.normal, o.axisZ))
				;
			float dist = Abs(VectorOp::Dot(p.normal, o.center) - p.distance);
			return (dist <= r);
		}

	}	// namespace CollisionOp
}	// namespace ng

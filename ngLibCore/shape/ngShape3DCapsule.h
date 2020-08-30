/*!
* @file		ngShape3DCapsule.h
* @brief	3D形状 カプセル（球スイープ）
* @date		2019-07-19
* @author	s.fukami
*/

#ifndef __NG_CORE_SHAPE_3D_CAPSULE_H__
#define __NG_CORE_SHAPE_3D_CAPSULE_H__

#include "ngLibCore/geometry/vector/ngVector3.h"
#include "ngShape3DSegment.h"

namespace ng
{
	struct Vector3;
}

namespace ng
{
	/*!
	* @brief					3D形状 カプセル（球スイープ）
	*/
	struct NG_DECL Shape3DCapsule
	{
		Shape3DSegment segment;	//!< 中心を通る線分
		float radius;			//!< 線分を囲う円の半径

		/*! コンストラクタ */
		Shape3DCapsule() { }
		explicit Shape3DCapsule(const Shape3DCapsule& src)
			: Shape3DCapsule(src.segment, src.radius) { }
		Shape3DCapsule(const Shape3DSegment& _segment, float _radius)
			: segment(_segment), radius(_radius) { }
		Shape3DCapsule(const Vector3& _begin, const Vector3& _end, float _radius)
			: Shape3DCapsule(Shape3DSegment(_begin, _end), _radius) { }

		/*! 中心座標取得 */
		Vector3 Center() const { return segment.Center(); }

		/*! 半径取得 */
		float Radius() const { return radius; }
		float RadiusSq() const { return Radius()*Radius(); }
		
		/*! 長さ取得 */
		float Length() const { return segment.Length(); }
		float LengthSq() const { return segment.LengthSq(); }

		/*! 衝突判定 */
		bool CheckHit(const struct Shape3DCapsule& other) const;
		bool CheckHit(const struct Shape3DSphere& other) const;
		bool CheckHit(const struct Vector3& other) const;
	};

}	// namespace ng

#endif	// __NG_CORE_SHAPE_3D_CAPSULE_H__

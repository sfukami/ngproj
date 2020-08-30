/*!
* @file		ngShape2DCapsule.h
* @brief	2D形状 カプセル（球スイープ）
* @date		2019-07-12
* @author	s.fukami
*/

#ifndef __NG_CORE_SHAPE_2D_CAPSULE_H__
#define __NG_CORE_SHAPE_2D_CAPSULE_H__

#include "ngLibCore/geometry/vector/ngVector2.h"
#include "ngShape2DSegment.h"

namespace ng
{
	struct Vector2;
}

namespace ng
{
	/*!
	* @brief					2D形状 カプセル（球スイープ）
	*/
	struct NG_DECL Shape2DCapsule
	{
		Shape2DSegment segment;	//!< 中心を通る線分
		float radius;			//!< 線分を囲う円の半径

		/*! コンストラクタ */
		Shape2DCapsule() { }
		explicit Shape2DCapsule(const Shape2DCapsule& src)
			: Shape2DCapsule(src.segment, src.radius) { }
		Shape2DCapsule(const Shape2DSegment& _segment, float _radius)
			: segment(_segment), radius(_radius) { }
		Shape2DCapsule(const Vector2& _begin, const Vector2& _end, float _radius)
			: Shape2DCapsule(Shape2DSegment(_begin, _end), _radius) { }

		/*! 中心座標取得 */
		Vector2 Center() const { return segment.Center(); }

		/*! 半径取得 */
		float Radius() const { return radius; }
		float RadiusSq() const { return Radius()*Radius(); }
		
		/*! 長さ取得 */
		float Length() const { return segment.Length(); }
		float LengthSq() const { return segment.LengthSq(); }

		/*! 衝突判定 */
		bool CheckHit(const struct Shape2DCapsule& other) const;
		bool CheckHit(const struct Shape2DCircle& other) const;
		bool CheckHit(const struct Vector2& other) const;
	};

}	// namespace ng

#endif	// __NG_CORE_SHAPE_2D_CAPSULE_H__

/*!
* @file		ngShape2DCircle.h
* @brief	2D形状 円
* @date		2015-10-10
* @author	s.fukami
*/

#ifndef __NG_CORE_SHAPE_2D_CIRCLE_H__
#define __NG_CORE_SHAPE_2D_CIRCLE_H__

#include "ngLibCore/geometry/vector/ngVector2.h"

namespace ng
{
	struct Shape2DSquare;
	struct Vector2;
}

namespace ng
{
	/*!
	* @brief					2D形状 円
	*/
	struct NG_DECL Shape2DCircle
	{
		Vector2 center;		//!< 中心座標
		float radius;		//!< 半径

		/*! コンストラクタ */
		Shape2DCircle() 
			: radius(0.0f) { }
		explicit Shape2DCircle(const Shape2DCircle& src)
			: Shape2DCircle(src.center, src.radius) { }
		Shape2DCircle(const Vector2& _center, float _radius)
			: center(_center), radius(_radius) { }

		/*! 中心座標取得 */
		const Vector2& Center() const { return center; }

		/*! 半径取得 */
		float Radius() const { return radius; }
		float RadiusSq() const { return Radius()*Radius(); }

		/*! 衝突判定 */
		bool CheckHit(const Shape2DCircle& other) const;
		bool CheckHit(const Shape2DSquare& other) const;
		bool CheckHit(const Vector2& other) const;
	};

}	// namespace ng

#endif	// __NG_CORE_SHAPE_2D_CIRCLE_H__

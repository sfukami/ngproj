/*!
* @file		ngShape3DSphere.h
* @brief	3D形状 球
* @date		2016-02-10
* @author	s.fukami
*/

#ifndef __NG_CORE_SHAPE_3D_SPHERE_H__
#define __NG_CORE_SHAPE_3D_SPHERE_H__

#include "ngLibCore/geometry/vector/ngVector3.h"

namespace ng
{
	struct Shape3DBox;
	struct Shape3DPlane;
	struct Vector3;
}

namespace ng
{
	/*!
	* 3D形状 球
	*/
	struct NG_DECL Shape3DSphere
	{
		Vector3 center;		//!< 中心座標
		float radius;		//!< 半径

		/*! コンストラクタ */
		Shape3DSphere()
			: radius(0.0f) { }
		explicit Shape3DSphere(const Shape3DSphere& src)
			: Shape3DSphere(src.center, src.radius) { }
		Shape3DSphere(const Vector3& _center, float _radius)
			: center(_center), radius(_radius) { }

		/*! 中心座標取得 */
		const Vector3& Center() const { return center; }

		/*! 半径取得 */
		float Radius() const { return radius; }
		float RadiusSq() const { return Radius()*Radius(); }

		/*! 衝突判定 */
		bool CheckHit(const Shape3DSphere& other) const;
		bool CheckHit(const Shape3DBox& other) const;
		bool CheckHit(const Vector3& other) const;
		bool CheckHit(const Shape3DPlane& other) const;
	};

}	// namespace ng

#endif	// __NG_CORE_SHAPE_3D_SPHERE_H__

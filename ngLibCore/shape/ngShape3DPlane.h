/*!
* @file		ngShape3DPlane.h
* @brief	3D形状 無限平面
* @date		2019-07-19
* @author	s.fukami
*/

#ifndef __NG_CORE_SHAPE_3D_PLANE_H__
#define __NG_CORE_SHAPE_3D_PLANE_H__

#include "ngLibCore/geometry/vector/ngVector3.h"

namespace ng
{
	struct Shape3DBox;
	struct Shape3DSphere;
	struct Shape3DOBB;
}

namespace ng
{
	/*!
	* @brief					3D形状 無限平面
	*/
	struct NG_DECL Shape3DPlane
	{
		Vector3 normal;		//!< 法線
		float distance;		//!< 原点から平面までの最短距離

		/*! コンストラクタ */
		Shape3DPlane()
			: distance(0.0f) { }
		explicit Shape3DPlane(const Shape3DPlane& src)
			: normal(src.normal), distance(src.distance) { }
		Shape3DPlane(const Vector3& _normal, float _distance)
			: normal(_normal), distance(_distance) { }

		/*! 頂点から算出を算出 */
		void CalcPlane(const Vector3& p1, const Vector3& p2, const Vector3& p3);

		/*! 衝突判定 */
		bool CheckHit(const Shape3DBox& other) const;
		bool CheckHit(const Shape3DSphere& other) const;
		bool CheckHit(const Shape3DOBB& other) const;
	};

}	// namespace ng

#endif	// __NG_CORE_SHAPE_3D_PLANE_H__
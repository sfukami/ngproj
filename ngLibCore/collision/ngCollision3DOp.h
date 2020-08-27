/*!
* @file		ngCollision3DOp.h
* @brief	3D衝突判定
* @date		2016-02-21
* @author	s.fukami
*/

#ifndef __NG_CORE_COLLISION_DETECTION_3D_H__
#define __NG_CORE_COLLISION_DETECTION_3D_H__

namespace ng
{
	struct Vector3;
	struct Shape3DBox;
	struct Shape3DSphere;
	struct Shape3DOBB;
	struct Shape3DCapsule;
	struct Shape3DPlane;
}

namespace ng
{
	namespace CollisionOp
	{
		/*!
		* 3D衝突判定 Box
		*/
		bool CheckHitBoxes(const Shape3DBox& b1, const Shape3DBox& b2);
		bool CheckHitBoxAndPos(const Shape3DBox& b, const Vector3& pos);

		/*!
		* 3D衝突判定 球
		*/
		bool CheckHitSpheres(const Shape3DSphere& s1, const Shape3DSphere& s2);
		bool CheckHitSphereAndPos(const Shape3DSphere& s, const Vector3& pos);

		/*!
		* 3D衝突判定 カプセル
		*/
		bool CheckHitCapsules(const Shape3DCapsule& c1, const Shape3DCapsule& c2);
		bool CheckHitCapsuleAndPos(const Shape3DCapsule& c, const Vector3& pos);

		/*!
		* 3D衝突判定 Box-球
		*/
		bool CheckHitBoxAndSphere(const Shape3DBox& b, const Shape3DSphere& s);

		/*!
		* 3D衝突判定 OBB
		*/
		bool CheckHitOBBs(const Shape3DOBB& o1, const Shape3DOBB& o2);

		/*!
		* 3D衝突判定 球-カプセル
		*/
		bool CheckHitSphereAndCapsule(const Shape3DSphere& s, const Shape3DCapsule& c);

		/*!
		* 3D衝突判定 Box-無限平面
		*/
		bool CheckHitBoxAndPlane(const Shape3DBox& b, const Shape3DPlane& p);

		/*!
		* 3D衝突判定 球-無限平面
		*/
		bool CheckHitSphereAndPlane(const Shape3DSphere& s, const Shape3DPlane& p);

		/*!
		* 3D衝突判定 OBB-無限平面
		*/
		bool CheckHitOBBAndPlane(const Shape3DOBB& o, const Shape3DPlane& p);

	}	// namespace CollisionOp
}	// namespace ng

#endif	// __NG_CORE_COLLISION_DETECTION_3D_H__

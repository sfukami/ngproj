/*!
* @file		ngCollision2DOp.h
* @brief	2D衝突判定
* @date		2015-10-21
* @author	s.fukami
*/

#ifndef __NG_CORE_COLLISION_DETECTION_2D_H__
#define __NG_CORE_COLLISION_DETECTION_2D_H__

namespace ng
{
	struct Vector2;
	struct Shape2DSquare;
	struct Shape2DCircle;
	struct Shape2DCapsule;
	struct Shape2DOBB;
}

namespace ng
{
	namespace CollisionOp
	{
		/*!
		* 2D衝突判定 矩形
		*/
		bool CheckHitSquares(const Shape2DSquare& s1, const Shape2DSquare& s2);
		bool CheckHitSquareAndPos(const Shape2DSquare& s, const Vector2& pos);

		/*!
		* 2D衝突判定 円
		*/
		bool CheckHitCircles(const Shape2DCircle& c1, const Shape2DCircle& c2);
		bool CheckHitCircleAndPos(const Shape2DCircle& c, const Vector2& pos);

		/*!
		* 2D衝突判定 カプセル
		*/
		bool CheckHitCapsules(const Shape2DCapsule& c1, const Shape2DCapsule& c2);
		bool CheckHitCapsuleAndPos(const Shape2DCapsule& c, const Vector2& pos);

		/*!
		* 2D衝突判定 OBB
		*/
		bool CheckHitOBBs(const Shape2DOBB& o1, const Shape2DOBB& o2);

		/*!
		* 2D衝突判定 矩形-円
		*/
		bool CheckHitSquareAndCircle(const Shape2DSquare& s, const Shape2DCircle& c);

		/*!
		* 2D衝突判定 円-カプセル
		*/
		bool CheckHitCircleAndCapsule(const Shape2DCircle& circle, const Shape2DCapsule& capsule);

	}	// namespace CollisionOp
}	// namespace ng

#endif	// __NG_CORE_COLLISION_DETECTION_2D_H__

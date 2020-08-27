/*!
* @file		ngShape3DSegment.h
* @brief	3D形状 線分
* @date		2019-07-19
* @author	s.fukami
*/

#ifndef __NG_CORE_SHAPE_3D_SEGMENT_H__
#define __NG_CORE_SHAPE_3D_SEGMENT_H__

#include "ngLibCore/geometry/vector/ngVector3.h"

namespace ng
{
	struct Vector3;
}

namespace ng
{
	/*!
	* 3D形状 線分
	*/
	struct NG_DECL Shape3DSegment
	{
		Vector3 begin, end;		//!< 始点、終点座標

		/*! コンストラクタ */
		Shape3DSegment() { }
		explicit Shape3DSegment(const Shape3DSegment& src)
			: Shape3DSegment(src.begin, src.end) { }
		Shape3DSegment(const Vector3& _begin, const Vector3& _end)
			: begin(_begin), end(_end) { }

		/*! 始点->終点 ベクトル取得 */
		Vector3 Vector() const { return (end-begin); }

		/*! 中心座標取得 */
		Vector3 Center() const;

		/*! 長さ取得 */
		float Length() const;
		float LengthSq() const;

		/*!
		* @brief					線分同士の最近傍点、最短距離（平方）を算出
		* @param opponent			もう一方の線分
		* @param pS					線分1 交差点までのスケールの格納先
		* @param pT					線分2 交差点までのスケールの格納先
		* @param pSPos				線分1 交差点の格納先
		* @param pTPos				線分2 交差点の格納先
		* @return					最短距離（平方）
		*/
		float CalcShotestDistSq(
			const Shape3DSegment& opponent,
			float* pS = nullptr, float* pT = nullptr, Vector3* pSPos = nullptr, Vector3* pTPos = nullptr
			) const;
	};

}	// namespace ng

#endif	// __NG_CORE_SHAPE_3D_SEGMENT_H__

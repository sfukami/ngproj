/*!
* @file		ngShape2DSegment.h
* @brief	2D形状 線分
* @date		2019-07-12
* @author	s.fukami
*/

#ifndef __NG_CORE_SHAPE_2D_SEGMENT_H__
#define __NG_CORE_SHAPE_2D_SEGMENT_H__

#include "ngLibCore/geometry/vector/ngVector2.h"

namespace ng
{
	struct Vector2;
}

namespace ng
{
	/*!
	* @brief					2D形状 線分
	*/
	struct NG_DECL Shape2DSegment
	{
		Vector2 begin, end;		//!< 始点、終点座標

		/*! コンストラクタ */
		Shape2DSegment() { }
		explicit Shape2DSegment(const Shape2DSegment& src)
			: Shape2DSegment(src.begin, src.end) { }
		Shape2DSegment(const Vector2& _begin, const Vector2& _end)
			: begin(_begin), end(_end) { }

		/*! 始点->終点 ベクトル取得 */
		Vector2 Vector() const { return (end-begin); }

		/*! 中心座標取得 */
		Vector2 Center() const;

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
			const Shape2DSegment& opponent,
			float* pS = nullptr, float* pT = nullptr, Vector2* pSPos = nullptr, Vector2* pTPos = nullptr
			) const;
	};

}	// namespace ng

#endif	// __NG_CORE_SHAPE_2D_SEGMENT_H__

/*!
* @file		ngGeomMath.h
* @brief	幾何計算
* @date		2019-07-12
* @author	s.fukami
*/

#ifndef __NG_CORE_GEOM_MATH_H__
#define __NG_CORE_GEOM_MATH_H__

namespace ng
{
	struct Vector2;
	struct Vector3;
}

namespace ng
{
	namespace GeomMath
	{
		/*!
		* @brief					線分と点の最近傍点を算出
		* @param beg				線分 始点
		* @param end				線分 終点
		* @param pos				点の座標
		* @param pT					最近傍点までのスケールの格納先
		* @param pC					最近傍点の格納先
		*/
		template <class Vec>
		NG_DECL void CalcClosestPosSegmentAndPos(
			const Vec& beg, const Vec& end, const Vec& pos, float* pT, Vec* pC = nullptr
			);

		/*!
		* @brief					線分と点の最近傍点、最短距離（平方）を算出
		* @param beg				線分 始点
		* @param end				線分 終点
		* @param pos				点の座標
		* @param pT					最近傍点までのスケールの格納先
		* @param pC					最近傍点の格納先
		* @return					最短距離（平方）
		*/
		template<class Vec>
		NG_DECL float CalcShotestDistSqSegmentAndPos(
			const Vec& beg, const Vec& end, const Vec& pos, float* pT = nullptr, Vec* pC = nullptr
			);

		/*!
		* @brief					線分同士の最近傍点、最短距離（平方）を算出
		* @param beg1				線分1 始点
		* @param end1				線分1 終点
		* @param beg2				線分2 始点
		* @param end2				線分2 終点
		* @param pS					線分1 最近傍点までのスケールの格納先
		* @param pT					線分2 最近傍点までのスケールの格納先
		* @param pC1				線分1 最近傍点の格納先
		* @param pC2				線分2 最近傍点の格納先
		*/
		template <class Vec>
		NG_DECL void CalcClosestPosSegments(
			const Vec& beg1, const Vec& end1, const Vec& beg2, const Vec& end2,
			float* pS, float* pT = nullptr, Vec* pC1 = nullptr, Vec* pC2 = nullptr
			);

		/*!
		* @brief					線分同士の最近傍点、最短距離（平方）を算出
		* @param beg1				線分1 始点
		* @param end1				線分1 終点
		* @param beg2				線分2 始点
		* @param end2				線分2 終点
		* @param pS					線分1 最近傍点までのスケールの格納先
		* @param pT					線分2 最近傍点までのスケールの格納先
		* @param pC1				線分1 最近傍点の格納先
		* @param pC2				線分2 最近傍点の格納先
		* @return					最短距離（平方）
		*/
		template <class Vec>
		NG_DECL float CalcShotestDistSqSegments(
			const Vec& beg1, const Vec& end1, const Vec& beg2, const Vec& end2,
			float* pS = nullptr, float* pT = nullptr, Vec* pC1 = nullptr, Vec* pC2 = nullptr
			);

		/*!
		* @brief					AABBと点の最近傍点を算出
		* @param min				AABB の各軸が最小となる点
		* @param max				AABB の各軸が最大となる点
		* @param pos				点の座標
		* @param pClosest			最近傍点の格納先
		*/
		template <class Vec>
		NG_DECL void CalcClosestPosAABBAndPos(
			const Vec& min, const Vec& max, const Vec& pos, Vec* pClosest
			);

		/*!
		* @brief					AABBと点の最短距離（平方）を算出
		* @param min				AABB の各軸が最小となる点
		* @param max				AABB の各軸が最大となる点
		* @param pos				点の座標
		* @return					最短距離（平方）
		*/
		template <class Vec>
		NG_DECL float CalcShotestDistSqAABBAndPos(
			const Vec& min, const Vec& max, const Vec& pos
			);

	}	// GeomMath
}	// namespace ng

#endif	// __NG_CORE_GEOM_MATH_H__

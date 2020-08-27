/*!
* @file		ngGeomMath.cpp
* @brief	幾何計算
* @date		2019-07-12
* @author	s.fukami
*/

#include "ngGeomMath.h"
#include "vector/ngVector2.h"
#include "vector/ngVector3.h"
#include "vector/ngVectorOp.h"
#include "ngLibCore/math/ngMath.h"

namespace ng
{
	namespace GeomMath
	{
		#define ExplicitInst(_macro) \
			FwdDecl_##_macro(Vector2); \
			FwdDecl_##_macro(Vector3);

		// テンプレート関数の明示的インスタンス化
		#define FwdDecl_CalcClosestPosSegmentAndPos(_type) \
			template NG_DECL void CalcClosestPosSegmentAndPos<_type>( \
				const _type&, const _type&, const _type&, float*, _type* \
				);
		ExplicitInst(CalcClosestPosSegmentAndPos);

		#define FwdDecl_CalcShotestDistSqSegmentAndPos(_type) \
			template NG_DECL float CalcShotestDistSqSegmentAndPos<_type>( \
				const _type&, const _type&, const _type&, float*, _type* \
				);
		ExplicitInst(CalcShotestDistSqSegmentAndPos);

		#define FwdDecl_CalcClosestPosSegments(_type) \
			template NG_DECL void CalcClosestPosSegments<_type>( \
				const _type&, const _type&, const _type&, const _type&, \
				float*, float*, _type*, _type* \
				);
		ExplicitInst(CalcClosestPosSegments);

		#define FwdDecl_CalcShotestDistSqSegments(_type) \
			template NG_DECL float CalcShotestDistSqSegments<_type>( \
				const _type&, const _type&, const _type&, const _type&, \
				float*, float*, _type*, _type* \
				);
		ExplicitInst(CalcShotestDistSqSegments);

		#define FwdDecl_CalcClosestPosAABBAndPos(_type) \
			template NG_DECL void CalcClosestPosAABBAndPos<_type>( \
				const _type&, const _type&, const _type&, _type* \
				);
		ExplicitInst(CalcClosestPosAABBAndPos);

		#define FwdDecl_CalcShotestDistSqAABBAndPos(_type) \
			template NG_DECL float CalcShotestDistSqAABBAndPos<_type>( \
			const _type&, const _type&, const _type& \
			);
		ExplicitInst(CalcShotestDistSqAABBAndPos);

		template <class Vec>
		NG_DECL void CalcClosestPosSegmentAndPos(
			const Vec& beg, const Vec& end, const Vec& pos, float* pT, Vec* pC
			)
		{
			/*
				■参考書籍:ゲームプログラミングのためのリアルタイム衝突判定(p128)
			*/
			/*
			Vec sv = end-beg;
			float t = VectorOp::Dot(pos-beg, sv) / VectorOp::Dot(sv);
			t = Clamp01(t);

			if(pT) *pT = t;
			if(pC) *pC = beg + sv*t;
			*/
			// ↑の除算を1つ遅延させる
			Vec sv = end-beg;
			Vec c;
			float t = VectorOp::Dot(pos-beg, sv);

			if(t<0.0f) {
				if(pT) *pT = 1.0f;
				if(pC) *pC = beg;
			}
			else {
				float denom = VectorOp::Dot(sv, sv);
				if(t>=denom) {
					if(pT) *pT = 1.0f;
					if(pC) *pC = end;
				}
				else {
					t = t/denom;
					if(pT) *pT = t;
					if(pC) *pC = beg + sv*t;
				}
			}
		}

		template<class Vec>
		NG_DECL float CalcShotestDistSqSegmentAndPos(
			const Vec& beg, const Vec& end, const Vec& pos, float* pT, Vec* pC
			)
		{
			Vec closest;
			CalcClosestPosSegmentAndPos(beg, end, pos, pT, &closest);
			if(pC) *pC = closest;
			return VectorOp::Dot(pos-closest);
		}

		template <class Vec>
		NG_DECL void CalcClosestPosSegments(
			const Vec& beg1, const Vec& end1, const Vec& beg2, const Vec& end2,
			float* pS, float* pT, Vec* pC1, Vec* pC2
			)
		{
			/*
				■参考書籍:ゲームプログラミングのためのリアルタイム衝突判定(p148)
			*/
			const float EPSILON = NG_FLT_EPSILON;
			Vec d1(end1 - beg1);
			Vec d2(end2 - beg2);
			Vec r(beg1 - beg2);
			float a = VectorOp::Dot(d1, d1);
			float e = VectorOp::Dot(d2, d2);
			float f = VectorOp::Dot(d2, r);
			float s, t;

			// 両線分の縮退具合で分岐
			// 両線分の点に縮退
			if(a<=EPSILON && e<=EPSILON) {
				s = t = 0.0f;
				if(pC1) *pC1 = beg1;
				if(pC2) *pC2 = beg2;
				return;
			}
			// 片方の線分が点に縮退
			else if(a<=EPSILON) {
				s = 0.0f;
				t = Clamp01(f/e);
			}
			else {
				float c = VectorOp::Dot(d1, r);
				// 片方の線分が点に縮退
				if(e<=EPSILON) {
					t = 0.0f;
					s = Clamp01(-c/a);
				}
				// 両線分が線分のまま
				else {
					float b = VectorOp::Dot(d1, d2);
					float denom = a*e - b*b;
					if(denom != 0.0f) {
						s = Clamp01((b*f - c*e)/denom);
					} else {
						s = 0.0f;
					}

					/*
					t = (b*s + f)/e;
					if(t<0.0f) {
						t = 0.0f;
						s = Clamp01(-c/a);
					} else if(t>1.0f) {
						t = 1.0f;
						s = Clamp01((b-c)/a);
					}
					*/
					// ↑の除算を1つ遅延させる
					float tnom = b*s +f;
					if(tnom<0.0f) {
						t = 0.0f;
						s = Clamp01(-c/a);
					}
					else if(tnom>e) {
						t = 1.0f;
						s = Clamp01((b-c)/e);
					}
					else {
						t = tnom/e;
					}
				}
			}

			Vec c1(beg1 + d1*t);
			Vec c2(beg2 + d2*s);

			if(pC1) *pC1 = c1;
			if(pC2) *pC2 = c2;
			if(pS) *pS = s;
			if(pT) *pT = t;
		}

		template <class Vec>
		NG_DECL float CalcShotestDistSqSegments(
			const Vec& beg1, const Vec& end1, const Vec& beg2, const Vec& end2,
			float* pS, float* pT, Vec* pC1, Vec* pC2
			)
		{
			Vec c1, c2;
			CalcClosestPosSegments(beg1, end1, beg2, end2, nullptr, nullptr, &c1, &c2);
			if(pC1) *pC1 = c1;
			if(pC2) *pC2 = c2;
			return VectorOp::Dot(c1-c2);
		}

		template <class Vec>
		NG_DECL void CalcClosestPosAABBAndPos(
			const Vec& min, const Vec& max, const Vec& pos, Vec* pClosest
			)
		{
			for(int i=0; i<Vec::COL; i++)
			{
				if(pos.m[i] < min.m[i])			pClosest->m[i] = min.m[i];
				else if(pos.m[i] > max.m[i])	pClosest->m[i] = max.m[i];
				else 							pClosest->m[i] = pos.m[i];
			}
		}

		template <class Vec>
		NG_DECL float CalcShotestDistSqAABBAndPos(
			const Vec& min, const Vec& max, const Vec& pos
			)
		{
			float ret = 0.0f;
			for(int i=0; i<Vec::COL; i++)
			{
				if(pos.m[i] < min.m[i])			ret += Square(min.m[i]-pos.m[i]);
				else if(pos.m[i] > max.m[i])	ret += Square(pos.m[i]-max.m[i]);

			}

			return ret;
		}

	}	// namespace GeomMath
}	// namespace ng

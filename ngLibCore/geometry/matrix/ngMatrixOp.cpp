/*!
* @file		ngMatrixOp.cpp
* @brief	行列演算
* @date		2015-10-18
* @author	s.fukami
*/

#include "ngMatrixOp.h"
#include "ngMatrix3x3.h"
#include "ngMatrix4x4.h"
#include "../vector/ngVectorOp.h"
#include "../vector/ngVector3.h"
#include "ngLibCore/math/ngMath.h"

namespace ng
{
	namespace MatrixOp
	{
		void Init(
			Matrix3x3& dst
			, f32 _m11, f32 _m12, f32 _m13
			, f32 _m21, f32 _m22, f32 _m23
			, f32 _m31, f32 _m32, f32 _m33
			)
		{
			dst.m11 = _m11; dst.m12 = _m12; dst.m13 = _m13;
			dst.m21 = _m21; dst.m22 = _m22; dst.m23 = _m23;
			dst.m31 = _m31; dst.m32 = _m32; dst.m33 = _m33;
		}

		void Identity(
			Matrix3x3& dst
			)
		{
			dst.m11 = 1.0f; dst.m12 = 0.0f; dst.m13 = 0.0f;
			dst.m21 = 0.0f; dst.m22 = 1.0f; dst.m23 = 0.0f;
			dst.m31 = 0.0f; dst.m32 = 0.0f; dst.m33 = 1.0f;
		}

		void Add(
			Matrix3x3& dst
			, const Matrix3x3& lhs
			, f32 rhs
			)
		{
			dst.m11 = lhs.m11 + rhs;
			dst.m12 = lhs.m12 + rhs;
			dst.m13 = lhs.m13 + rhs;

			dst.m21 = lhs.m21 + rhs;
			dst.m22 = lhs.m22 + rhs;
			dst.m23 = lhs.m23 + rhs;

			dst.m31 = lhs.m31 + rhs;
			dst.m32 = lhs.m32 + rhs;
			dst.m33 = lhs.m33 + rhs;
		}

		void Add(
			Matrix3x3& dst
			, const Matrix3x3& lhs
			, const Matrix3x3& rhs
			)
		{
			dst.m11 = lhs.m11 + rhs.m11;
			dst.m12 = lhs.m12 + rhs.m12;
			dst.m13 = lhs.m13 + rhs.m13;

			dst.m21 = lhs.m21 + rhs.m21;
			dst.m22 = lhs.m22 + rhs.m22;
			dst.m23 = lhs.m23 + rhs.m23;

			dst.m31 = lhs.m31 + rhs.m31;
			dst.m32 = lhs.m32 + rhs.m32;
			dst.m33 = lhs.m33 + rhs.m33;
		}

		void Subtract(
			Matrix3x3& dst
			, const Matrix3x3& lhs
			, f32 rhs
			)
		{
			dst.m11 = lhs.m11 - rhs;
			dst.m12 = lhs.m12 - rhs;
			dst.m13 = lhs.m13 - rhs;

			dst.m21 = lhs.m21 - rhs;
			dst.m22 = lhs.m22 - rhs;
			dst.m23 = lhs.m23 - rhs;

			dst.m31 = lhs.m31 - rhs;
			dst.m32 = lhs.m32 - rhs;
			dst.m33 = lhs.m33 - rhs;
		}

		void Subtract(
			Matrix3x3& dst
			, const Matrix3x3& lhs
			, const Matrix3x3& rhs
			)
		{
			dst.m11 = lhs.m11 - rhs.m11;
			dst.m12 = lhs.m12 - rhs.m12;
			dst.m13 = lhs.m13 - rhs.m13;

			dst.m21 = lhs.m21 - rhs.m21;
			dst.m22 = lhs.m22 - rhs.m22;
			dst.m23 = lhs.m23 - rhs.m23;

			dst.m31 = lhs.m31 - rhs.m31;
			dst.m32 = lhs.m32 - rhs.m32;
			dst.m33 = lhs.m33 - rhs.m33;
		}

		void Multiply(
			Matrix3x3& dst
			, const Matrix3x3& lhs
			, f32 rhs
			)
		{
			dst.m11 = lhs.m11 * rhs;
			dst.m12 = lhs.m12 * rhs;
			dst.m13 = lhs.m13 * rhs;

			dst.m21 = lhs.m21 * rhs;
			dst.m22 = lhs.m22 * rhs;
			dst.m23 = lhs.m23 * rhs;

			dst.m31 = lhs.m31 * rhs;
			dst.m32 = lhs.m32 * rhs;
			dst.m33 = lhs.m33 * rhs;
		}

		void Multiply(
			Matrix3x3& dst
			, const Matrix3x3& lhs
			, const Matrix3x3& rhs
			)
		{
			Matrix3x3 buf;
			buf.m11 = (lhs.m11 * rhs.m11) + (lhs.m12 * rhs.m21) + (lhs.m13 * rhs.m31);
			buf.m12 = (lhs.m11 * rhs.m12) + (lhs.m12 * rhs.m22) + (lhs.m13 * rhs.m32);
			buf.m13 = (lhs.m11 * rhs.m13) + (lhs.m12 * rhs.m23) + (lhs.m13 * rhs.m33);

			buf.m21 = (lhs.m21 * rhs.m11) + (lhs.m22 * rhs.m21) + (lhs.m23 * rhs.m31);
			buf.m22 = (lhs.m21 * rhs.m12) + (lhs.m22 * rhs.m22) + (lhs.m23 * rhs.m32);
			buf.m23 = (lhs.m21 * rhs.m13) + (lhs.m22 * rhs.m23) + (lhs.m23 * rhs.m33);

			buf.m31 = (lhs.m31 * rhs.m11) + (lhs.m32 * rhs.m21) + (lhs.m33 * rhs.m31);
			buf.m32 = (lhs.m31 * rhs.m12) + (lhs.m32 * rhs.m22) + (lhs.m33 * rhs.m32);
			buf.m33 = (lhs.m31 * rhs.m13) + (lhs.m32 * rhs.m23) + (lhs.m33 * rhs.m33);
			dst = buf;
		}

		void Divide(
			Matrix3x3& dst
			, const Matrix3x3& lhs
			, f32 rhs
			)
		{
			dst.m11 = lhs.m11 / rhs;
			dst.m12 = lhs.m12 / rhs;
			dst.m13 = lhs.m13 / rhs;

			dst.m21 = lhs.m21 / rhs;
			dst.m22 = lhs.m22 / rhs;
			dst.m23 = lhs.m23 / rhs;

			dst.m31 = lhs.m31 / rhs;
			dst.m32 = lhs.m32 / rhs;
			dst.m33 = lhs.m33 / rhs;
		}

		f32 Determinant(
			const Matrix3x3& src
			)
		{
			return 
				src.m11 * ((src.m22 * src.m33) - (src.m32 * src.m23)) +
				src.m12 * (( - (src.m21 * src.m33) + (src.m31 * src.m23)) +
				src.m13 * ((src.m21 * src.m32) - src.m31 * src.m22));
		}

		void Inverse(
			Matrix3x3& dst
			, const Matrix3x3& src
			)
		{
			f32 det = Determinant(src);
			if(det == 0.0f)
			{
				det = 1.0f;
			}

			Matrix3x3 buf;
			buf.m11 = (src.m22 * src.m33 - src.m23 * src.m32) / det;
			buf.m12 = - (src.m12 * src.m33 - src.m13 * src.m32) / det;
			buf.m13 = (src.m12 * src.m23 - src.m13 * src.m22) / det;

			buf.m21 = - (src.m21 * src.m33 - src.m23 * src.m31) / det;
			buf.m22 = (src.m11 * src.m33 - src.m13 * src.m31) / det;
			buf.m23 = - (src.m11 * src.m23 - src.m13 * src.m21) / det;

			buf.m31 = (src.m21 * src.m32 - src.m22 * src.m31) / det;
			buf.m32 = - (src.m11 * src.m32 - src.m12 * src.m31) / det;
			buf.m33 = (src.m11 * src.m22 - src.m12 * src.m21) / det;
			dst = buf;
		}

		void Scaling(
			Matrix3x3& dst
			, f32 sx
			, f32 sy
			, f32 sz
			)
		{
			dst.m11 = sx;	dst.m12 = 0.0f; dst.m13 = 0.0f;
			dst.m21 = 0.0f; dst.m22 = sy;	dst.m23 = 0.0f;
			dst.m31 = 0.0f; dst.m32 = 0.0f; dst.m33 = sz;
		}

		void RotationX(
			Matrix3x3& dst
			, f32 rad
			)
		{
			f32 s = Sin(rad);
			f32 c = Cos(rad);

			dst.m11 = 1.0f; dst.m12 = 0.0f; dst.m13 = 0.0f;
			dst.m21 = 0.0f; dst.m22 = c;	dst.m23 = -s;
			dst.m31 = 0.0f; dst.m32 = s;	dst.m33 = c;
		}

		void RotationY(
			Matrix3x3& dst
			, f32 rad
			)
		{
			f32 s = Sin(rad);
			f32 c = Cos(rad);

			dst.m11 = c;	dst.m12 = 0.0f; dst.m13 = s;
			dst.m21 = 0.0f; dst.m22 = 1.0f; dst.m23 = 0.0f;
			dst.m31 = -s;	dst.m32 = 0.0f; dst.m33 = c;
		}

		void RotationZ(
			Matrix3x3& dst
			, f32 rad
			)
		{
			f32 s = Sin(rad);
			f32 c = Cos(rad);

			dst.m11 = c;	dst.m12 = -s;	dst.m13 = 0.0f;
			dst.m21 = s;	dst.m22 = c;	dst.m23 = 0.0f;
			dst.m31 = 0.0f; dst.m32 = 0.0f; dst.m33 = 1.0f;
		}

		void RotationYawPitchRoll(
			Matrix3x3& dst
			, f32 yaw
			, f32 pitch
			, f32 roll
			)
		{
			f32 ys = Sin(yaw);
			f32 yc = Cos(yaw);
			f32 ps = Sin(pitch);
			f32 pc = Cos(pitch);
			f32 rs = Sin(roll);
			f32 rc = Cos(roll);

			dst.m11 = rc * yc - rs * ps * ys;
			dst.m12 = -rs * pc;
			dst.m13 = rc * ys + rs * ps * ys;

			dst.m21 = rs * yc + rc * ps * ys;
			dst.m22 = rc * pc;
			dst.m23 = rs * ys - rc * ps * ys;

			dst.m31 = -pc * ys;
			dst.m32 = ps;
			dst.m33 = pc * yc;
		}

		void Transpose(
			Matrix3x3& dst
			, const Matrix3x3& src
			)
		{
			Matrix3x3 buf;
			buf.m11 = src.m11;
			buf.m12 = src.m21;
			buf.m13 = src.m31;

			buf.m21 = src.m12;
			buf.m22 = src.m22;
			buf.m23 = src.m32;

			buf.m31 = src.m13;
			buf.m32 = src.m23;
			buf.m33 = src.m33;
			dst = buf;
		}

		void Init(
			Matrix4x4& dst
			, f32 _m11, f32 _m12, f32 _m13, f32 _m14
			, f32 _m21, f32 _m22, f32 _m23, f32 _m24
			, f32 _m31, f32 _m32, f32 _m33, f32 _m34
			, f32 _m41, f32 _m42, f32 _m43, f32 _m44
			)
		{
			dst.m11 = _m11; dst.m12 = _m12; dst.m13 = _m13; dst.m14 = _m14;
			dst.m21 = _m21; dst.m22 = _m22; dst.m23 = _m23; dst.m24 = _m24;
			dst.m31 = _m31; dst.m32 = _m32; dst.m33 = _m33; dst.m34 = _m34;
			dst.m41 = _m41; dst.m42 = _m42; dst.m43 = _m43; dst.m44 = _m44;
		}

		void Identity(
			Matrix4x4& dst
			)
		{
			dst.m11 = 1.0f; dst.m12 = 0.0f; dst.m13 = 0.0f; dst.m14 = 0.0f;
			dst.m21 = 0.0f; dst.m22 = 1.0f; dst.m23 = 0.0f; dst.m24 = 0.0f;
			dst.m31 = 0.0f; dst.m32 = 0.0f; dst.m33 = 1.0f; dst.m34 = 0.0f;
			dst.m41 = 0.0f; dst.m42 = 0.0f; dst.m43 = 0.0f; dst.m44 = 1.0f;
		}

		void Add(
			Matrix4x4& dst
			, const Matrix4x4& lhs
			, f32 rhs
			)
		{
			dst.m11 = lhs.m11 + rhs;
			dst.m12 = lhs.m12 + rhs;
			dst.m13 = lhs.m13 + rhs;
			dst.m14 = lhs.m14 + rhs;

			dst.m21 = lhs.m21 + rhs;
			dst.m22 = lhs.m22 + rhs;
			dst.m23 = lhs.m23 + rhs;
			dst.m24 = lhs.m24 + rhs;

			dst.m31 = lhs.m31 + rhs;
			dst.m32 = lhs.m32 + rhs;
			dst.m33 = lhs.m33 + rhs;
			dst.m34 = lhs.m34 + rhs;

			dst.m41 = lhs.m41 + rhs;
			dst.m42 = lhs.m42 + rhs;
			dst.m43 = lhs.m43 + rhs;
			dst.m44 = lhs.m44 + rhs;
		}

		void Add(
			Matrix4x4& dst
			, const Matrix4x4& lhs
			, const Matrix4x4& rhs
			)
		{
			dst.m11 = lhs.m11 + rhs.m11;
			dst.m12 = lhs.m12 + rhs.m12;
			dst.m13 = lhs.m13 + rhs.m13;
			dst.m14 = lhs.m14 + rhs.m14;

			dst.m21 = lhs.m21 + rhs.m21;
			dst.m22 = lhs.m22 + rhs.m22;
			dst.m23 = lhs.m23 + rhs.m23;
			dst.m24 = lhs.m24 + rhs.m24;

			dst.m31 = lhs.m31 + rhs.m31;
			dst.m32 = lhs.m32 + rhs.m32;
			dst.m33 = lhs.m33 + rhs.m33;
			dst.m34 = lhs.m34 + rhs.m34;

			dst.m41 = lhs.m41 + rhs.m41;
			dst.m42 = lhs.m42 + rhs.m42;
			dst.m43 = lhs.m43 + rhs.m43;
			dst.m44 = lhs.m44 + rhs.m44;
		}

		void Subtract(
			Matrix4x4& dst
			, const Matrix4x4& lhs
			, f32 rhs
			)
		{
			dst.m11 = lhs.m11 - rhs;
			dst.m12 = lhs.m12 - rhs;
			dst.m13 = lhs.m13 - rhs;
			dst.m14 = lhs.m14 - rhs;

			dst.m21 = lhs.m21 - rhs;
			dst.m22 = lhs.m22 - rhs;
			dst.m23 = lhs.m23 - rhs;
			dst.m24 = lhs.m24 - rhs;

			dst.m31 = lhs.m31 - rhs;
			dst.m32 = lhs.m32 - rhs;
			dst.m33 = lhs.m33 - rhs;
			dst.m34 = lhs.m34 - rhs;

			dst.m41 = lhs.m41 - rhs;
			dst.m42 = lhs.m42 - rhs;
			dst.m43 = lhs.m43 - rhs;
			dst.m44 = lhs.m44 - rhs;
		}

		void Subtract(
			Matrix4x4& dst
			, const Matrix4x4& lhs
			, const Matrix4x4& rhs
			)
		{
			dst.m11 = lhs.m11 - rhs.m11;
			dst.m12 = lhs.m12 - rhs.m12;
			dst.m13 = lhs.m13 - rhs.m13;
			dst.m14 = lhs.m14 - rhs.m14;

			dst.m21 = lhs.m21 - rhs.m21;
			dst.m22 = lhs.m22 - rhs.m22;
			dst.m23 = lhs.m23 - rhs.m23;
			dst.m24 = lhs.m24 - rhs.m24;

			dst.m31 = lhs.m31 - rhs.m31;
			dst.m32 = lhs.m32 - rhs.m32;
			dst.m33 = lhs.m33 - rhs.m33;
			dst.m34 = lhs.m34 - rhs.m34;

			dst.m41 = lhs.m41 - rhs.m41;
			dst.m42 = lhs.m42 - rhs.m42;
			dst.m43 = lhs.m43 - rhs.m43;
			dst.m44 = lhs.m44 - rhs.m44;
		}

		void Multiply(
			Matrix4x4& dst
			, const Matrix4x4& lhs
			, f32 rhs
			)
		{
			dst.m11 = lhs.m11 * rhs;
			dst.m12 = lhs.m12 * rhs;
			dst.m13 = lhs.m13 * rhs;
			dst.m14 = lhs.m14 * rhs;

			dst.m21 = lhs.m21 * rhs;
			dst.m22 = lhs.m22 * rhs;
			dst.m23 = lhs.m23 * rhs;
			dst.m24 = lhs.m24 * rhs;

			dst.m31 = lhs.m31 * rhs;
			dst.m32 = lhs.m32 * rhs;
			dst.m33 = lhs.m33 * rhs;
			dst.m34 = lhs.m34 * rhs;

			dst.m41 = lhs.m41 * rhs;
			dst.m42 = lhs.m42 * rhs;
			dst.m43 = lhs.m43 * rhs;
			dst.m44 = lhs.m44 * rhs;
		}

		void Multiply(
			Matrix4x4& dst
			, const Matrix4x4& lhs
			, const Matrix4x4& rhs
			)
		{
			Matrix4x4 buf;
			buf.m11 = (lhs.m11 * rhs.m11) + (lhs.m12 * rhs.m21) + (lhs.m13 * rhs.m31) + (lhs.m14 * rhs.m41);
			buf.m12 = (lhs.m11 * rhs.m12) + (lhs.m12 * rhs.m22) + (lhs.m13 * rhs.m32) + (lhs.m14 * rhs.m42);
			buf.m13 = (lhs.m11 * rhs.m13) + (lhs.m12 * rhs.m23) + (lhs.m13 * rhs.m33) + (lhs.m14 * rhs.m43);
			buf.m14 = (lhs.m11 * rhs.m14) + (lhs.m12 * rhs.m24) + (lhs.m13 * rhs.m34) + (lhs.m14 * rhs.m44);

			buf.m21 = (lhs.m21 * rhs.m11) + (lhs.m22 * rhs.m21) + (lhs.m23 * rhs.m31) + (lhs.m24 * rhs.m41);
			buf.m22 = (lhs.m21 * rhs.m12) + (lhs.m22 * rhs.m22) + (lhs.m23 * rhs.m32) + (lhs.m24 * rhs.m42);
			buf.m23 = (lhs.m21 * rhs.m13) + (lhs.m22 * rhs.m23) + (lhs.m23 * rhs.m33) + (lhs.m24 * rhs.m43);
			buf.m24 = (lhs.m21 * rhs.m14) + (lhs.m22 * rhs.m24) + (lhs.m23 * rhs.m34) + (lhs.m24 * rhs.m44);

			buf.m31 = (lhs.m31 * rhs.m11) + (lhs.m32 * rhs.m21) + (lhs.m33 * rhs.m31) + (lhs.m34 * rhs.m41);
			buf.m32 = (lhs.m31 * rhs.m12) + (lhs.m32 * rhs.m22) + (lhs.m33 * rhs.m32) + (lhs.m34 * rhs.m42);
			buf.m33 = (lhs.m31 * rhs.m13) + (lhs.m32 * rhs.m23) + (lhs.m33 * rhs.m33) + (lhs.m34 * rhs.m43);
			buf.m34 = (lhs.m31 * rhs.m14) + (lhs.m32 * rhs.m24) + (lhs.m33 * rhs.m34) + (lhs.m34 * rhs.m44);

			buf.m41 = (lhs.m41 * rhs.m11) + (lhs.m42 * rhs.m21) + (lhs.m43 * rhs.m31) + (lhs.m44 * rhs.m41);
			buf.m42 = (lhs.m41 * rhs.m12) + (lhs.m42 * rhs.m22) + (lhs.m43 * rhs.m32) + (lhs.m44 * rhs.m42);
			buf.m43 = (lhs.m41 * rhs.m13) + (lhs.m42 * rhs.m23) + (lhs.m43 * rhs.m33) + (lhs.m44 * rhs.m43);
			buf.m44 = (lhs.m41 * rhs.m14) + (lhs.m42 * rhs.m24) + (lhs.m43 * rhs.m34) + (lhs.m44 * rhs.m44);
			dst = buf;
		}

		void Divide(
			Matrix4x4& dst
			, const Matrix4x4& lhs
			, f32 rhs
			)
		{
			dst.m11 = lhs.m11 / rhs;
			dst.m12 = lhs.m12 / rhs;
			dst.m13 = lhs.m13 / rhs;
			dst.m14 = lhs.m14 / rhs;

			dst.m21 = lhs.m21 / rhs;
			dst.m22 = lhs.m22 / rhs;
			dst.m23 = lhs.m23 / rhs;
			dst.m24 = lhs.m24 / rhs;

			dst.m31 = lhs.m31 / rhs;
			dst.m32 = lhs.m32 / rhs;
			dst.m33 = lhs.m33 / rhs;
			dst.m34 = lhs.m34 / rhs;

			dst.m41 = lhs.m41 / rhs;
			dst.m42 = lhs.m42 / rhs;
			dst.m43 = lhs.m43 / rhs;
			dst.m44 = lhs.m44 / rhs;
		}

		f32 Determinant(
			const Matrix4x4& src
			)
		{
			return
				src.m11 * ((src.m22 * src.m33 * src.m44) + (src.m23 * src.m34 * src.m42) + (src.m24 * src.m32 * src.m43)) + 
				src.m12 * ((src.m21 * src.m34 * src.m43) + (src.m23 * src.m31 * src.m44) + (src.m24 * src.m33 * src.m41)) + 
				src.m13 * ((src.m21 * src.m32 * src.m44) + (src.m22 * src.m34 * src.m41) + (src.m24 * src.m31 * src.m42)) + 
				src.m14 * ((src.m21 * src.m33 * src.m42) + (src.m22 * src.m31 * src.m43) + (src.m23 * src.m32 * src.m41)) - 
				src.m11 * ((src.m22 * src.m34 * src.m43) + (src.m23 * src.m32 * src.m44) + (src.m24 * src.m33 * src.m42)) - 
				src.m12 * ((src.m21 * src.m33 * src.m44) + (src.m23 * src.m34 * src.m41) + (src.m24 * src.m32 * src.m41)) - 
				src.m13 * ((src.m21 * src.m34 * src.m42) + (src.m22 * src.m31 * src.m44) + (src.m24 * src.m32 * src.m41)) - 
				src.m14 * ((src.m21 * src.m32 * src.m43) + (src.m22 * src.m33 * src.m41) + (src.m23 * src.m31 * src.m42));
		}

		void Inverse(
			Matrix4x4& dst
			, const Matrix4x4& src
			)
		{
			f32 det = Determinant(src);
			if(det == 0.0f)
			{
				det = 1.0f;
			}

			Matrix4x4 buf;
			buf.m11 = 
				(src.m22 * src.m33 * src.m44) + (src.m23 * src.m34 * src.m42) + (src.m24 * src.m32 * src.m43) - 
				(src.m22 * src.m34 * src.m43) - (src.m23 * src.m32 * src.m44) - (src.m24 * src.m33 * src.m42);
			buf.m11 /= det;
			buf.m12 = 
				(src.m12 * src.m34 * src.m43) + (src.m13 * src.m32 * src.m44) + (src.m14 * src.m33 * src.m42) - 
				(src.m12 * src.m33 * src.m44) - (src.m13 * src.m34 * src.m42) - (src.m14 * src.m32 * src.m43);
			buf.m12 /= det;
			buf.m13 = 
				(src.m12 * src.m23 * src.m44) + (src.m13 * src.m24 * src.m42) + (src.m14 * src.m22 * src.m43) - 
				(src.m12 * src.m24 * src.m43) - (src.m13 * src.m22 * src.m44) - (src.m14 * src.m23 * src.m42);
			buf.m13 /= det;
			buf.m14 = 
				(src.m12 * src.m24 * src.m33) + (src.m13 * src.m22 * src.m34) + (src.m14 * src.m23 * src.m32) - 
				(src.m12 * src.m23 * src.m34) - (src.m13 * src.m24 * src.m32) - (src.m14 * src.m22 * src.m33);
			buf.m14 /= det;

			buf.m21 = 
				(src.m21 * src.m34 * src.m43) + (src.m23 * src.m31 * src.m44) + (src.m24 * src.m33 * src.m41) - 
				(src.m21 * src.m33 * src.m44) - (src.m23 * src.m34 * src.m41) - (src.m24 * src.m31 * src.m43);
			buf.m21 /= det;
			buf.m22 = 
				(src.m11 * src.m33 * src.m44) + (src.m13 * src.m34 * src.m41) + (src.m14 * src.m31 * src.m43) - 
				(src.m11 * src.m34 * src.m43) - (src.m13 * src.m31 * src.m44) - (src.m14 * src.m33 * src.m41);
			buf.m22 /= det;
			buf.m23 = 
				(src.m11 * src.m24 * src.m43) + (src.m13 * src.m21 * src.m44) + (src.m14 * src.m23 * src.m41) - 
				(src.m11 * src.m23 * src.m44) - (src.m13 * src.m24 * src.m41) - (src.m14 * src.m21 * src.m43);
			buf.m23 /= det;
			buf.m24 = 
				(src.m11 * src.m23 * src.m34) + (src.m13 * src.m24 * src.m31) + (src.m14 * src.m21 * src.m33) - 
				(src.m11 * src.m24 * src.m33) - (src.m13 * src.m21 * src.m34) - (src.m14 * src.m23 * src.m31);
			buf.m24 /= det;

			buf.m31 = 
				(src.m21 * src.m32 * src.m44) + (src.m22 * src.m34 * src.m41) + (src.m24 * src.m31 * src.m42) - 
				(src.m21 * src.m34 * src.m42) - (src.m22 * src.m31 * src.m44) - (src.m24 * src.m32 * src.m41);
			buf.m31 /= det;
			buf.m32 = 
				(src.m11 * src.m34 * src.m42) + (src.m12 * src.m31 * src.m44) + (src.m14 * src.m32 * src.m41) - 
				(src.m11 * src.m32 * src.m44) - (src.m12 * src.m34 * src.m41) - (src.m14 * src.m31 * src.m42);
			buf.m32 /= det;
			buf.m33 = 
				(src.m11 * src.m22 * src.m44) + (src.m12 * src.m24 * src.m41) + (src.m14 * src.m21 * src.m42) - 
				(src.m11 * src.m24 * src.m42) - (src.m12 * src.m21 * src.m44) - (src.m14 * src.m22 * src.m41);
			buf.m33 /= det;
			buf.m34 = 
				(src.m11 * src.m24 * src.m32) + (src.m12 * src.m21 * src.m34) + (src.m14 * src.m22 * src.m31) - 
				(src.m11 * src.m22 * src.m34) - (src.m12 * src.m24 * src.m31) - (src.m14 * src.m21 * src.m32);
			buf.m34 /= det;

			buf.m41 = 
				(src.m21 * src.m33 * src.m42) + (src.m22 * src.m31 * src.m43) + (src.m23 * src.m32 * src.m41) - 
				(src.m21 * src.m32 * src.m43) - (src.m22 * src.m33 * src.m41) - (src.m23 * src.m31 * src.m42);
			buf.m41 /= det;
			buf.m42 = 
				(src.m11 * src.m32 * src.m43) + (src.m12 * src.m33 * src.m41) + (src.m13 * src.m31 * src.m42) - 
				(src.m11 * src.m33 * src.m42) - (src.m12 * src.m31 * src.m43) - (src.m13 * src.m32 * src.m41);
			buf.m42 /= det;
			buf.m43 = 
				(src.m11 * src.m23 * src.m42) + (src.m12 * src.m21 * src.m43) + (src.m13 * src.m22 * src.m41) - 
				(src.m11 * src.m22 * src.m43) - (src.m12 * src.m23 * src.m41) - (src.m13 * src.m21 * src.m42);
			buf.m43 /= det;
			buf.m44 = 
				(src.m11 * src.m22 * src.m33) + (src.m12 * src.m23 * src.m31) + (src.m13 * src.m21 * src.m32) - 
				(src.m11 * src.m23 * src.m32) - (src.m12 * src.m21 * src.m33) - (src.m13 * src.m22 * src.m31);
			buf.m44 /= det;

			dst = buf;
		}

		void Transpose(
			Matrix4x4& dst
			, const Matrix4x4& src
			)
		{
			Matrix4x4 buf;
			buf.m11 = src.m11;
			buf.m12 = src.m21;
			buf.m13 = src.m31;
			buf.m14 = src.m41;

			buf.m21 = src.m12;
			buf.m22 = src.m22;
			buf.m23 = src.m32;
			buf.m24 = src.m42;

			buf.m31 = src.m13;
			buf.m32 = src.m23;
			buf.m33 = src.m33;
			buf.m34 = src.m43;

			buf.m41 = src.m14;
			buf.m42 = src.m24;
			buf.m43 = src.m34;
			buf.m44 = src.m44;
			dst = buf;
		}

		void Scaling(
			Matrix4x4& dst
			, f32 sx
			, f32 sy
			, f32 sz
			)
		{
			dst.m11 = sx;	dst.m12 = 0.0f; dst.m13 = 0.0f; dst.m14 = 0.0f;
			dst.m21 = 0.0f; dst.m22 = sy;	dst.m23 = 0.0f; dst.m24 = 0.0f;
			dst.m31 = 0.0f; dst.m32 = 0.0f; dst.m33 = sz;	dst.m34 = 0.0f;
			dst.m41 = 0.0f; dst.m42 = 0.0f; dst.m43 = 0.0f; dst.m44 = 1.0f;
		}

		void RotationX(
			Matrix4x4& dst
			, f32 rad
			)
		{
			f32 s = Sin(rad);
			f32 c = Cos(rad);

			dst.m11 = 1.0f; dst.m12 = 0.0f; dst.m13 = 0.0f; dst.m14 = 0.0f;
			dst.m21 = 0.0f; dst.m22 = c;	dst.m23 = s;	dst.m24 = 0.0f;
			dst.m31 = 0.0f; dst.m32 = -s;	dst.m33 = c;	dst.m34 = 0.0f;
			dst.m41 = 0.0f; dst.m42 = 0.0f; dst.m43 = 0.0f; dst.m44 = 1.0f;
		}

		void RotationY(
			Matrix4x4& dst
			, f32 rad
			)
		{
			f32 s = Sin(rad);
			f32 c = Cos(rad);

			dst.m11 = c;	dst.m12 = 0.0f; dst.m13 = -s;	dst.m14 = 0.0f;
			dst.m21 = 0.0f; dst.m22 = 1.0f; dst.m23 = 0.0f; dst.m24 = 0.0f;
			dst.m31 = s;	dst.m32 = 0.0f; dst.m33 = c;	dst.m34 = 0.0f;
			dst.m41 = 0.0f; dst.m42 = 0.0f; dst.m43 = 0.0f; dst.m44 = 1.0f;
		}

		void RotationZ(
			Matrix4x4& dst
			, f32 rad
			)
		{
			f32 s = Sin(rad);
			f32 c = Cos(rad);

			dst.m11 = c;	dst.m12 = s;	dst.m13 = 0.0f; dst.m14 = 0.0f;
			dst.m21 = -s;	dst.m22 = c;	dst.m23 = 0.0f; dst.m24 = 0.0f;
			dst.m31 = 0.0f; dst.m32 = 0.0f; dst.m33 = 1.0f; dst.m34 = 0.0f;
			dst.m41 = 0.0f; dst.m42 = 0.0f; dst.m43 = 0.0f; dst.m44 = 1.0f;
		}

		void RotationYawPitchRoll(
			Matrix4x4& dst
			, f32 yaw
			, f32 pitch
			, f32 roll
			)
		{
			f32 ys = Sin(yaw);
			f32 yc = Cos(yaw);
			f32 ps = Sin(pitch);
			f32 pc = Cos(pitch);
			f32 rs = Sin(roll);
			f32 rc = Cos(roll);

			// Z*X*Y
			dst.m11 = yc * rc + ps * ys * rs;
			dst.m12 = pc * rs;
			dst.m13 = -ys * rc + ps * yc * rs;
			dst.m14 = 0.0f;
			
			dst.m21 = -yc * rs + ps * ys * rc;
			dst.m22 = pc * rc;
			dst.m23 = ys * rs + ps * yc * rc;
			dst.m24 = 0.0f;
			
			dst.m31 = pc * ys;
			dst.m32 = -ps;
			dst.m33 = pc * yc;
			dst.m34 = 0.0f;

			dst.m41 = 0.0f;
			dst.m42 = 0.0f;
			dst.m43 = 0.0f;
			dst.m44 = 1.0f;
		}

		void RotationAxis(
			Matrix4x4& dst
			, const Vector3& axis
			, f32 rad
			)
		{
			f32 s = Sin(rad);
			f32 c = Cos(rad);
			rad = 1.0f - c;

			dst.m11 = axis.x * axis.x * rad + c;
			dst.m12 = axis.x * axis.y * rad + axis.z * s;
			dst.m13 = axis.z * axis.x * rad - axis.y * s;
			dst.m14 = 0.0f;


			dst.m21 = axis.x * axis.y * rad - axis.z * s;
			dst.m22 = axis.y * axis.y * rad + c;
			dst.m23 = axis.y * axis.z * rad + axis.x * s;
			dst.m24 = 0.0f;

			dst.m31 = axis.z * axis.x * rad + axis.y * s;
			dst.m32 = axis.y * axis.z * rad - axis.x * s;
			dst.m33 = axis.z * axis.z * rad + c;
			dst.m34 = 0.0f;

			dst.m41 = dst.m42 = dst.m43 = 0.0f;
			dst.m44 = 1.0f;
		}

		void Translation(
			Matrix4x4& dst
			, f32 tx
			, f32 ty
			, f32 tz
			)
		{
			dst.m11 = 1.0f; dst.m12 = 0.0f; dst.m13 = 0.0f; dst.m14 = 0.0f;
			dst.m21 = 0.0f; dst.m22 = 1.0f; dst.m23 = 0.0f; dst.m24 = 0.0f;
			dst.m31 = 0.0f; dst.m32 = 0.0f; dst.m33 = 1.0f; dst.m34 = 0.0f;
			dst.m41 = tx;	dst.m42 = ty;	dst.m43 = tz;	dst.m44 = 1.0f;
		}

		void ViewLH(
			Matrix4x4& dst
			, const Vector3& eye
			, const Vector3& focus
			, const Vector3& up
			)
		{
			Vector3 x, y, z;
			VectorOp::Subtract(z, focus, eye);
			VectorOp::Cross(x, up, z);
			VectorOp::Cross(y, z, x);

			VectorOp::Normalize(x, x);
			VectorOp::Normalize(y, y);
			VectorOp::Normalize(z, z);

			dst.m11 = x.x;
			dst.m12 = x.y;
			dst.m13 = x.z;
			dst.m14 = 0.0f;

			dst.m21 = y.x;
			dst.m22 = y.y;
			dst.m23 = y.z;
			dst.m24 = 0.0f;

			dst.m31 = z.x;
			dst.m32 = z.y;
			dst.m33 = z.z;
			dst.m34 = 0.0f;

			dst.m41 = -VectorOp::Dot(x, eye);
			dst.m42 = -VectorOp::Dot(y, eye);
			dst.m43 = -VectorOp::Dot(z, eye);
			dst.m44 = 1.0f;
		}

		void ViewRH(
			Matrix4x4& dst
			, const Vector3& eye
			, const Vector3& focus
			, const Vector3& up
			)
		{
			Vector3 x, y, z;
			VectorOp::Subtract(z, eye, focus);
			VectorOp::Cross(x, up, z);
			VectorOp::Cross(y, z, x);

			VectorOp::Normalize(x, x);
			VectorOp::Normalize(y, y);
			VectorOp::Normalize(z, z);

			dst.m11 = x.x;
			dst.m12 = x.y;
			dst.m13 = x.z;
			dst.m14 = 0.0f;

			dst.m21 = y.x;
			dst.m22 = y.y;
			dst.m23 = y.z;
			dst.m24 = 0.0f;

			dst.m31 = z.x;
			dst.m32 = z.y;
			dst.m33 = z.z;
			dst.m34 = 0.0f;

			dst.m41 = -VectorOp::Dot(x, eye);
			dst.m42 = -VectorOp::Dot(y, eye);
			dst.m43 = -VectorOp::Dot(z, eye);
			dst.m44 = 1.0f;
		}

		void ViewLHTransposed(
			Matrix4x4& dst
			, const Vector3& eye
			, const Vector3& focus
			, const Vector3& up
			)
		{
			Vector3 x, y, z;
			VectorOp::Subtract(z, focus, eye);
			VectorOp::Cross(x, up, z);
			VectorOp::Cross(y, z, x);

			VectorOp::Normalize(x, x);
			VectorOp::Normalize(y, y);
			VectorOp::Normalize(z, z);

			// 転置済みになるように配置
			dst.m11 = x.x;
			dst.m21 = x.y;
			dst.m31 = x.z;
			dst.m41 = 0.0f;

			dst.m12 = y.x;
			dst.m22 = y.y;
			dst.m32 = y.z;
			dst.m42 = 0.0f;

			dst.m13 = z.x;
			dst.m23 = z.y;
			dst.m33 = z.z;
			dst.m43 = 0.0f;

			dst.m14 = -VectorOp::Dot(x, eye);
			dst.m24 = -VectorOp::Dot(y, eye);
			dst.m34 = -VectorOp::Dot(z, eye);
			dst.m44 = 1.0f;
		}

		void ViewRHTransposed(
			Matrix4x4& dst
			, const Vector3& eye
			, const Vector3& focus
			, const Vector3& up
			)
		{
			Vector3 x, y, z;
			VectorOp::Subtract(z, eye, focus);
			VectorOp::Cross(x, up, z);
			VectorOp::Cross(y, z, x);

			VectorOp::Normalize(x, x);
			VectorOp::Normalize(y, y);
			VectorOp::Normalize(z, z);

			// 転置済みになるように配置
			dst.m11 = x.x;
			dst.m21 = x.y;
			dst.m31 = x.z;
			dst.m41 = 0.0f;

			dst.m12 = y.x;
			dst.m22 = y.y;
			dst.m32 = y.z;
			dst.m42 = 0.0f;

			dst.m13 = z.x;
			dst.m23 = z.y;
			dst.m33 = z.z;
			dst.m43 = 0.0f;

			dst.m14 = -VectorOp::Dot(x, eye);
			dst.m24 = -VectorOp::Dot(y, eye);
			dst.m34 = -VectorOp::Dot(z, eye);
			dst.m44 = 1.0f;
		}

		void ProjOrthoLH(
			Matrix4x4& dst
			, f32 w
			, f32 h
			, f32 nearZ
			, f32 farZ
			)
		{
			dst.m11 = 2.0f / w;
			dst.m12 = 0.0f;
			dst.m13 = 0.0f;
			dst.m14 = 0.0f;

			dst.m21 = 0.0f;
			dst.m22 = 2.0f / h;
			dst.m23 = 0.0f;
			dst.m24 = 0.0f;

			dst.m31 = 0.0f;
			dst.m32 = 0.0f;
			dst.m33 = 1.0f / (farZ - nearZ);
			dst.m34 = 0.0f;

			dst.m41 = 0.0f;
			dst.m42 = 0.0f;
			dst.m43 = -nearZ / (farZ - nearZ);
			dst.m44 = 1.0f;
		}

		void ProjOrthoRH(
			Matrix4x4& dst
			, f32 w
			, f32 h
			, f32 nearZ
			, f32 farZ
			)
		{
			dst.m11 = 2.0f / w;
			dst.m12 = 0.0f;
			dst.m13 = 0.0f;
			dst.m14 = 0.0f;

			dst.m21 = 0.0f;
			dst.m22 = 2.0f / h;
			dst.m23 = 0.0f;
			dst.m24 = 0.0f;

			dst.m31 = 0.0f;
			dst.m32 = 0.0f;
			dst.m33 = 1.0f / (nearZ - farZ);
			dst.m34 = 0.0f;

			dst.m41 = 0.0f;
			dst.m42 = 0.0f;
			dst.m43 = -nearZ / (farZ - nearZ);
			dst.m44 = 1.0f;
		}

		void ProjPersLH(
			Matrix4x4& dst
			, f32 fov
			, f32 aspect
			, f32 nearZ
			, f32 farZ
			)
		{
			dst.m22 = Cot(fov * 0.5f);

			dst.m11 = dst.m22 / aspect;
			dst.m12 = 0.0f;
			dst.m13 = 0.0f;
			dst.m14 = 0.0f;

			dst.m21 = 0.0f;
			dst.m23 = 0.0f;
			dst.m24 = 0.0f;

			dst.m31 = 0.0f;
			dst.m32 = 0.0f;
			dst.m33 = farZ / (farZ - nearZ);
			dst.m34 = 1.0f;

			dst.m41 = 0.0f;
			dst.m42 = 0.0f;
			dst.m43 = -farZ * nearZ / (farZ - nearZ);
			dst.m44 = 0.0f;
		}

		void ProjPersRH(
			Matrix4x4& dst
			, f32 fov
			, f32 aspect
			, f32 nearZ
			, f32 farZ
			)
		{
			dst.m22 = Cot(fov * 0.5f);

			dst.m11 = dst.m22 / aspect;
			dst.m12 = 0.0f;
			dst.m13 = 0.0f;
			dst.m14 = 0.0f;

			dst.m21 = 0.0f;
			dst.m23 = 0.0f;
			dst.m24 = 0.0f;

			dst.m31 = 0.0f;
			dst.m32 = 0.0f;
			dst.m33 = farZ / (nearZ - farZ);
			dst.m34 = -1.0f;

			dst.m41 = 0.0f;
			dst.m42 = 0.0f;
			dst.m43 = -farZ * nearZ / (farZ - nearZ);
			dst.m44 = 0.0f;
		}

		void ViewportScaling(
			Matrix4x4& dst
			, f32 w
			, f32 h
			)
		{
			w *= 0.5f;
			h *= 0.5f;

			dst.m11 = w;
			dst.m12 = 0.0f;
			dst.m13 = 0.0f;
			dst.m14 = 0.0f;

			dst.m21 = 0.0f;
			dst.m22 = -h;
			dst.m23 = 0.0f;
			dst.m24 = 0.0f;

			dst.m31 = 0.0f;
			dst.m32 = 0.0f;
			dst.m33 = 0.0f;
			dst.m34 = 0.0f;

			dst.m41 = w;
			dst.m42 = h;
			dst.m43 = 0.0f;
			dst.m44 = 1.0f;
		}
		
	}	// namespace Matrix
}	// namespace ng

/*!
* @file		ngQuaternionOp.cpp
* @brief	クォータニオン演算
* @date		2015-10-20
* @author	s.fukami
*/

#include "ngQuaternionOp.h"
#include "ngQuaternion.h"
#include "ngLibCore/geometry/vector/ngVector3.h"
#include "ngLibCore/geometry/matrix/ngMatrix4x4.h"
#include "ngLibCore/geometry/vector/ngVectorOp.h"
#include "ngLibCore/math/ngMath.h"

namespace ng
{
	struct Vector3;
}

namespace ng
{
	namespace QuaternionOp
	{
		NG_DECL void Init(
			Quaternion& dst
			, float _x, float _y, float _z, float _w
			)
		{
			dst.x = _x;
			dst.y = _y;
			dst.z = _z;
			dst.w = _w;
		}

		NG_DECL void Identity(
			Quaternion& dst
			)
		{
			dst.x = dst.y = dst.z = 0.f;
			dst.w = 1.f;
		}

		NG_DECL void Vector(
			Vector3& dst
			, const Quaternion& src
			)
		{
			dst.x = src.x;
			dst.y = src.y;
			dst.z = src.z;
		}

		NG_DECL float Angle(
			const Quaternion& src
			)
		{
			return (2.0f*ACos(src.w));
		}

		NG_DECL void Axis(
			Vector3& dst
			, const Quaternion& src
			)
		{
			float length = Length(src);
			Vector(dst, src);

			if(length>0.0f) {
				VectorOp::Divide(dst, dst, length);
			}
		}

		NG_DECL void Add(
			Quaternion& dst
			, const Quaternion& lhs
			, const Quaternion& rhs
			)
		{
			dst.x = lhs.x + rhs.x;
			dst.y = lhs.y + rhs.y;
			dst.z = lhs.z + rhs.z;
			dst.w = lhs.w + rhs.w;
		}

		NG_DECL void Subtract(
			Quaternion& dst
			, const Quaternion& lhs
			, const Quaternion& rhs
			)
		{
			dst.x = lhs.x - rhs.x;
			dst.y = lhs.y - rhs.y;
			dst.z = lhs.z - rhs.z;
			dst.w = lhs.w - rhs.w;
		}

		NG_DECL void Multiply(
			Quaternion& dst
			, const Quaternion& lhs
			, float rhs
			)
		{
			dst.x = lhs.x * rhs;
			dst.y = lhs.y * rhs;
			dst.z = lhs.z * rhs;
			dst.w = lhs.w * rhs;
		}

		NG_DECL void Multiply(
			Quaternion& dst
			, const Quaternion& lhs
			, const Quaternion& rhs
			)
		{
			Quaternion buf;
			buf.x = lhs.w * rhs.x + rhs.w * lhs.x - (lhs.y * rhs.z - lhs.z * rhs.y);
			buf.y = lhs.w * rhs.y + rhs.w * lhs.y - (lhs.z * rhs.x - lhs.x * rhs.z);
			buf.z = lhs.w * rhs.z + rhs.w * lhs.z - (lhs.x * rhs.y - lhs.y * rhs.x);
			buf.w = lhs.w * rhs.w - (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z);
			dst = buf;
		}

		NG_DECL void Multiply(
			Quaternion& dst
			, const Quaternion& lhs
			, const Vector3& rhs
			)
		{
			// ベクトルをスカラー成分0のクォータニオンと見なす
			Quaternion buf;
			buf.x =   lhs.w * rhs.x + lhs.z * rhs.y - lhs.y * rhs.z;
			buf.y =   lhs.w * rhs.y + lhs.x * rhs.z - lhs.z * rhs.x;
			buf.z =   lhs.w * rhs.z + lhs.y * rhs.x - lhs.x * rhs.y;
			buf.w = -(lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z);
			dst = buf;
		}

		NG_DECL void Divide(
			Quaternion& dst
			, const Quaternion& lhs
			, float rhs
			)
		{
			dst.w = lhs.w / rhs;
			dst.x = lhs.x / rhs;
			dst.y = lhs.y / rhs;
			dst.z = lhs.z / rhs;
		}

		NG_DECL float Dot(
			const Quaternion& lhs
			, const Quaternion& rhs
			)
		{
			return (
				lhs.w * rhs.w + 
				lhs.x * rhs.x + 
				lhs.y * rhs.y + 
				lhs.z * rhs.z
				);
		}

		NG_DECL float LengthSq(
			const Quaternion& src
			)
		{
			return (
				src.w * src.w +
				src.x * src.x +
				src.y * src.y +
				src.z * src.z
				);
		}

		NG_DECL float Length(
			const Quaternion& src
			)
		{
			return Sqrt(
				LengthSq(src)
				);
		}

		NG_DECL void Normalize(
			Quaternion& dst
			, const Quaternion& src
			)
		{
			Divide(dst, src, Length(src));
		}

		NG_DECL void Inverse(
			Quaternion& dst
			, const Quaternion& src
			)
		{
			Divide(dst, src, Dot(src, src));
		}

		NG_DECL void Conjugate(
			Quaternion& dst
			, const Quaternion& src
			)
		{
			dst.w = src.w;
			dst.x = -src.x;
			dst.y = -src.y;
			dst.z = -src.z;
		}

		NG_DECL void RotationAxis(
			Quaternion& dst
			, const Vector3& axis
			, float rad
			)
		{
			float theta = rad * 0.5f;
			float sin = Sin(theta);

			dst.w = Cos(theta);
			dst.x = axis.x * sin;
			dst.y = axis.y * sin;
			dst.z = axis.z * sin;
		}

		NG_DECL void Rotate(
			Quaternion& dst
			, const Quaternion& q
			, const Quaternion& rot
			)
		{
			Quaternion buf;
			Conjugate(buf, rot);

			Multiply(dst, rot, q);
			Multiply(dst, dst, buf);
		}

		NG_DECL void Rotate(
			Vector3& dst
			, const Vector3& v
			, const Quaternion& rot
			)
		{
			Quaternion buf, q;
			Conjugate(q, rot);

			Multiply(buf, rot, v);
			Multiply(buf, buf, q);
			Vector(dst, buf);
		}

		NG_DECL void Slerp(
			Quaternion& dst
			, const Quaternion& q1
			, const Quaternion& q2
			, float t
			)
		{
			float qr = Dot(q1, q2);
			float ss = 1.0f - qr * qr;
			float sp;

			if(ss <= 0.0f || (sp = Sqrt(ss)) == 0.0f)
			{
				dst = q1;
			}
			else
			{
				float ph = ACos(qr);
				float pt = ph * t;
				float t1 = Sin(pt) / sp;
				float t0 = Sin(ph - pt) / sp;
				dst.m[0] = q1.m[0] * t0 + q2.m[0] * t1;
				dst.m[1] = q1.m[1] * t0 + q2.m[1] * t1;
				dst.m[2] = q1.m[2] * t0 + q2.m[2] * t1;
				dst.m[3] = q1.m[3] * t0 + q2.m[3] * t1;
			}
		}

		NG_DECL void ToEulerAngle(
			Vector3& dst
			, const Quaternion& src
			)
		{
			float q00 = src.x * src.x;
			float q11 = src.y * src.y;
			float q22 = src.z * src.z;
			float q33 = src.w * src.w;

			float r11 = -2.f * (src.x * src.y - src.w * src.z);
			float r12 = q33 - q00 + q11 - q22;
			float r21 = 2.f * (src.y * src.z + src.w * src.x);
			float r31 = 2.f * (src.x * src.z - src.w * src.y);
			float r32 = q33 - q00 - q11 + q33;

			// ZXY
			dst.x = ATan2(r31, r32);
			dst.y = ASin(r21);
			dst.z = ATan2(r11, r12);

			dst.x = RadianToDegree(dst.x);
			dst.y = RadianToDegree(dst.y);
			dst.z = RadianToDegree(dst.z);
		}

		NG_DECL void FromEulerAngle(
			Quaternion& dst
			, const Vector3& eulerAngle
			)
		{
			float x = DegreeToRadian(eulerAngle.x);
			float y = DegreeToRadian(eulerAngle.y);
			float z = DegreeToRadian(eulerAngle.z);

			float cx = Cos(x * 0.5f);
			float sx = Sin(x * 0.5f);
			float cy = Cos(y * 0.5f);
			float sy = Sin(y * 0.5f);
			float cz = Cos(z * 0.5f);
			float sz = Sin(z * 0.5f);

			// ZXY
			dst.x = sx * cy * cz - cx * sy * sz;
			dst.y = cx * sy * cz + sx * cy * sz;
			dst.z = cx * cy * sz + sx * sy * cz;
			dst.w = cx * cy * cz - sx * sy * sz;
		}

		NG_DECL void ToMatrix(
			Matrix4& dst
			, const Quaternion& src
			)
		{
			dst.m11 = 1.0f - 2.0f * src.y * src.y - 2.0f * src.z * src.z;
			dst.m12 = 2.0f * src.x * src.y + 2.0f * src.w * src.z;
			dst.m13 = 2.0f * src.x * src.z - 2.0f * src.w * src.y;
			dst.m14 = 0.0f;
			dst.m21 = 2.0f * src.x * src.y - 2.0f * src.w * src.z;
			dst.m22 = 1.0f - 2.0f * src.x * src.x - 2.0f * src.z * src.z;
			dst.m23 = 2.0f * src.y * src.z + 2.0f * src.w * src.x;
			dst.m24 = 0.0f;
			dst.m31 = 2.0f * src.x * src.z + 2.0f * src.w * src.y;
			dst.m32 = 2.0f * src.y * src.z - 2.0f * src.w * src.x;
			dst.m33 = 1.0f - 2.0f * src.x * src.x - 2.0f * src.y * src.y;
			dst.m34 = 0.0f;
			dst.m41 = dst.m42 = dst.m43 = 0.0f;
			dst.m44 = 1.0f;
		}

		NG_DECL void FromMatrix(
			Quaternion& dst
			, const Matrix4& src
			)
		{
			float elem[4];
			elem[0] = src.m11 + src.m22 + src.m33 + 1.0f;
			elem[1] = src.m11 - src.m22 - src.m33 + 1.0f;
			elem[2] = -src.m11 + src.m22 - src.m33 + 1.0f;
			elem[3] = -src.m11 - src.m22 + src.m33 + 1.0f;

			unsigned maxi = 0;
			for(int i=0; i<4; i++)
			{
				if(elem[i] > elem[ maxi ])
				{
					maxi = i;
				}
			}

			if(elem[ maxi ] < 0.0f)
			{
				// failed
				return;
			}

			dst.m[ maxi ] = Sqrt(elem[ maxi ]) * 0.5f;
			float Multiply = 0.25f / dst.m[ maxi ];

			switch(maxi)
			{
				// w
			case 0:
				dst.m[1] = (src.m23 - src.m32) * Multiply;
				dst.m[2] = (src.m31 - src.m13) * Multiply;
				dst.m[3] = (src.m12 - src.m21) * Multiply;
				break;
				// x
			case 1:
				dst.m[0] = (src.m23 - src.m32) * Multiply;
				dst.m[2] = (src.m12 + src.m21) * Multiply;
				dst.m[3] = (src.m31 + src.m13) * Multiply;
				break;
				// y
			case 2:
				dst.m[0] = (src.m31 - src.m13) * Multiply;
				dst.m[1] = (src.m12 + src.m21) * Multiply;
				dst.m[3] = (src.m23 + src.m32) * Multiply;
				break;
				// z
			case 3:
				dst.m[0] = (src.m12 - src.m21) * Multiply;
				dst.m[1] = (src.m31 + src.m13) * Multiply;
				dst.m[2] = (src.m23 + src.m32) * Multiply;
				break;
			}
		}

	}	// namespace QuaternionOp
}	// namespace ng

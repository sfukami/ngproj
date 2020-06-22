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
		/*!
		* クォータニオン 初期化
		*/
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

		/*!
		* クォータニオン ベクトル取得
		*/
		NG_DECL void Vector(
			Vector3& dst
			, const Quaternion& src
			)
		{
			dst.x = src.x;
			dst.y = src.y;
			dst.z = src.z;
		}

		/*!
		* クォータニオン 回転角取得
		*/
		NG_DECL float Angle(
			const Quaternion& src
			)
		{
			return (2.0f*ACos(src.w));
		}

		/*!
		* クォータニオン 回転軸取得
		*/
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

		/*!
		* クォータニオン クォータニオン加算
		*/
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

		/*!
		* クォータニオン クォータニオン減算
		*/
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

		/*!
		* クォータニオン スカラー乗算
		*/
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

		/*!
		* クォータニオン クォータニオン乗算
		*/
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

		/*!
		* クォータニオン ベクトル乗算
		*/
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

		/*!
		* クォータニオン スカラー除算
		*/
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

		/*!
		* クォータニオン 内積算出
		*/
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

		/*!
		* クォータニオン 長さ算出（平方前）
		*/
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

		/*!
		* クォータニオン 長さ算出
		*/
		NG_DECL float Length(
			const Quaternion& src
			)
		{
			return Sqrt(
				LengthSq(src)
				);
		}

		/*!
		* クォータニオン 正規化
		*/
		NG_DECL void Normalize(
			Quaternion& dst
			, const Quaternion& src
			)
		{
			Divide(dst, src, Length(src));
		}

		/*!
		* クォータニオン 逆クォータニオン算出
		*/
		NG_DECL void Inverse(
			Quaternion& dst
			, const Quaternion& src
			)
		{
			Divide(dst, src, Dot(src, src));
		}

		/*!
		* クォータニオン 共役クォータニオン算出
		*/
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

		/*!
		* クォータニオン 任意の回転軸及び、回転角よりクォータニオンを算出
		*/
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

		/*!
		* クォータニオン クォータニオン回転
		*/
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

		/*!
		* クォータニオン ベクトル回転
		*/
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

		/*!
		* クォータニオン 球面線形補間
		*
		* @attention		クォータニオンは正規化済みであること
		*/
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

		/*!
		* クォータニオン ヨー・ピッチ・ロールよりクォータニオンを算出
		*/
		NG_DECL void RotationYawPitchRoll(
			Quaternion& dst
			, float yaw
			, float pitch
			, float roll
			)
		{
			float cy = Cos(yaw * 0.5f);
			float sy = Sin(yaw * 0.5f);
			float cp = Cos(pitch * 0.5f);
			float sp = Sin(pitch * 0.5f);
			float cr = Cos(roll * 0.5f);
			float sr = Sin(roll * 0.5f);

			dst.w = cy * cp * cr + sy * sp * sr;
			dst.x = cy * sp * cr + sy * cp * sr;
			dst.y = sy * cp * cr - cy * sp * sr;
			dst.z = cy * cp * sr - sy * sp * cr;
		}

		/*!
		* クォータニオン オイラー角を取得
		*/
		NG_DECL void EulerAngle(
			Vector3& dst
			, const Quaternion& src
			)
		{
			float q00 = src.w * src.w;
			float q11 = src.x * src.x;
			float q22 = src.y * src.y;
			float q33 = src.z * src.z;

			float r11 = q00 + q11 - q22 - q33;
			float r21 = 2.0f * (src.x * src.y + src.w * src.z);
			float r31 = 2.0f * (src.x * src.z - src.w * src.y);
			float r32 = 2.0f * (src.y * src.z + src.w * src.x);
			float r33 = q00 - q11 - q22 + q33;

			float buf = Abs(r31);
			if(buf > 0.999999f)
			{
				float r12 = 2.0f * (src.x * src.y - src.w * src.z);
				float r13 = 2.0f * (src.x * src.z + src.w * src.y);

				dst.x = 0.0f;
				dst.y = (-(NG_PI * 0.5f)) * r31 / buf;
				dst.z = ATan2(-r12, -r31 * r13);
			}
			dst.x = ASin(-r31);			// pitch
			dst.y = ATan2(r21, r11);	// yaw
			dst.z = ATan2(r32, r33);	// roll
		}

		/*!
		* クォータニオン 4x4行列を算出
		*/
		NG_DECL void QuaternionToMat4(
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

		/*!
		* クォータニオン 4x4行列よりクォータニオンを算出
		*/
		NG_DECL void Mat4ToQuaternion(
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

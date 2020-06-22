/*!
* @file		ngVectorOp.cpp
* @brief	ベクトル演算
* @date		2013-10-18
* @author	s.fukami
*/

#include "ngVectorOp.h"
#include "ngVector2.h"
#include "ngVector3.h"
#include "ngVector4.h"
#include "../matrix/ngMatrix3x3.h"
#include "../matrix/ngMatrix4x4.h"
#include "ngLibCore/math/ngMath.h"

namespace ng
{
	namespace VectorOp
	{
		/*!
		* 2次元ベクトル 初期化
		*/
		void Init(
			Vector2& dst
			, f32 _x, f32 _y
			)
		{
			dst.x = _x;
			dst.y = _y;
		}

		/*!
		* 2次元ベクトル スカラー加算
		*/
		void Add(
			Vector2& dst
			, Vector2& lhs
			, f32 rhs
			)
		{
			dst.x = lhs.x + rhs;
			dst.y = lhs.y + rhs;
		}

		/*!
		* 2次元ベクトル ベクトル加算
		*/
		void Add(
			Vector2& dst
			, const Vector2& lhs
			, const Vector2& rhs
			)
		{
			dst.x = lhs.x + rhs.x;
			dst.y = lhs.y + rhs.y;
		}

		/*!
		* 2次元ベクトル スカラー減算
		*/
		void Subtract(
			Vector2& dst
			, const Vector2& lhs
			, f32 rhs
			)
		{
			dst.x = lhs.x - rhs;
			dst.y = lhs.y - rhs;
		}

		/*!
		* 2次元ベクトル ベクトル減算
		*/
		void Subtract(
			Vector2& dst
			, const Vector2& lhs
			, const Vector2& rhs
			)
		{
			dst.x = lhs.x - rhs.x;
			dst.y = lhs.y - rhs.y;
		}

		/*!
		* 2次元ベクトル スカラー乗算
		*/
		void Multiply(
			Vector2& dst
			, const Vector2& lhs
			, f32 rhs
			)
		{
			dst.x = lhs.x * rhs;
			dst.y = lhs.y * rhs;
		}

		/*!
		* 2次元ベクトル スカラー除算
		*/
		void Divide(
			Vector2& dst
			, const Vector2& lhs
			, f32 rhs
			)
		{
			dst.x = lhs.x / rhs;
			dst.y = lhs.y / rhs;
		}

		/*!
		* 2次元ベクトル 反転
		*/
		void Reverse(
			Vector2& dst
			, const Vector2& src
			)
		{
			dst.x = -src.x;
			dst.y = -src.y;
		}

		/*!
		* 2次元ベクトル 内積算出
		*/
		f32 Dot(
			const Vector2& lhs
			, const Vector2& rhs
			)
		{
			return (
				lhs.x * rhs.x + 
				lhs.y * rhs.y
				);
		}
		NG_DECL f32 Dot(
			const Vector2& self
			)
		{
			return Dot(self, self);
		}

		/*!
		* 2次元ベクトル 外積算出
		*/
		f32 Cross(
			const Vector2& lhs
			, const Vector2& rhs
			)
		{
			return (
				lhs.x * rhs.y - 
				lhs.y * rhs.x
				);
		}

		/*!
		* 2次元ベクトル 長さ算出（平方前）
		*/
		f32 LengthSq(
			const Vector2& src
			)
		{
			return (
				src.x * src.x + 
				src.y * src.y
				);
		}
		f32 LengthSq(
			const Vector2& pos1, const Vector2& pos2
			)
		{
			return LengthSq(
				pos2-pos1
				);
		}

		/*!
		* 2次元ベクトル 長さ算出
		*/
		f32 Length(
			const Vector2& src
			)
		{
			return Sqrt(
				LengthSq(src)
				);
		}
		f32 Length(
			const Vector2& pos1, const Vector2& pos2
			)
		{
			return Length(
				pos2-pos1
				);
		}

		/*!
		* 2次元ベクトル 正規化
		*/
		void Normalize(
			Vector2& dst
			, const Vector2& src
			)
		{
			f32 len = Length(src);
			dst.x /= len;
			dst.y /= len;
		}

		/*!
		* 2次元ベクトル ベクトル間の線形補間
		*/
		void Lerp(
			Vector2& dst
			, const Vector2& a
			, const Vector2& b
			, f32 s
			)
		{
			Vector2 buf;
			Subtract(buf, b, a);
			Multiply(buf, buf, s);
			Add(buf, a, buf);
			dst = buf;
		}

		/*!
		* 回転角（ラジアン）を指定し回転
		*/
		NG_DECL void Rotate(
			Vector2& dst
			, const Vector2& src
			, float rad
			)
		{
			float s = Sin(rad);
			float c = Cos(rad);

			dst.x = src.x*c - src.y*s;
			dst.y = src.x*s + src.y*c;
		}

		/*!
		* 2次元ベクトル 3x3行列による変換
		*/
		void Transform(
			Vector2& dst
			, const Vector2& src
			, const Matrix3& mat
			)
		{
			Vector2 buf;
			buf.x = src.x * mat.m11 + src.y * mat.m21;
			buf.y = src.x * mat.m12 + src.y * mat.m22;
			dst = buf;
		}

		/*!
		* 3次元ベクトル 初期化
		*/
		void Init(
			Vector3& dst
			, f32 _x, f32 _y, f32 _z
			)
		{
			dst.x = _x;
			dst.y = _y;
			dst.z = _z;
		}

		/*!
		* 3次元ベクトル スカラー加算
		*/
		void Add(
			Vector3& dst
			, const Vector3& lhs
			, f32 rhs
			)
		{
			dst.x = lhs.x + rhs;
			dst.y = lhs.y + rhs;
			dst.z = lhs.z + rhs;
		}

		/*!
		* 3次元ベクトル ベクトル加算
		*/
		void Add(
			Vector3& dst
			, const Vector3& lhs
			, const Vector3& rhs
			)
		{
			dst.x = lhs.x + rhs.x;
			dst.y = lhs.y + rhs.y;
			dst.z = lhs.z + rhs.z;
		}

		/*!
		* 3次元ベクトル スカラー減算
		*/
		void Subtract(
			Vector3& dst
			, const Vector3& lhs
			, f32 rhs
			)
		{
			dst.x = lhs.x - rhs;
			dst.y = lhs.y - rhs;
			dst.z = lhs.z - rhs;
		}

		/*!
		* 3次元ベクトル ベクトル減算
		*/
		void Subtract(
			Vector3& dst
			, const Vector3& lhs
			, const Vector3& rhs
			)
		{
			dst.x = lhs.x - rhs.x;
			dst.y = lhs.y - rhs.y;
			dst.z = lhs.z - rhs.z;
		}

		/*!
		* 3次元ベクトル スカラー乗算
		*/
		void Multiply(
			Vector3& dst
			, const Vector3& lhs
			, f32 rhs
			)
		{
			dst.x = lhs.x * rhs;
			dst.y = lhs.y * rhs;
			dst.z = lhs.z * rhs;
		}

		/*!
		* 3次元ベクトル スカラー除算
		*/
		void Divide(
			Vector3& dst
			, const Vector3& lhs
			, f32 rhs
			)
		{
			dst.x = lhs.x / rhs;
			dst.y = lhs.y / rhs;
			dst.z = lhs.z / rhs;
		}

		/*!
		* 3次元ベクトル 反転
		*/
		void Reverse(
			Vector3& dst
			, const Vector3& src
			)
		{
			dst.x = -src.x;
			dst.y = -src.y;
			dst.z = -src.z;
		}

		/*!
		* 3次元ベクトル 内積算出
		*/
		f32 Dot(
			const Vector3& lhs
			, const Vector3& rhs
			)
		{
			return (
				lhs.x * rhs.x + 
				lhs.y * rhs.y + 
				lhs.z * rhs.z
				);
		}
		NG_DECL f32 Dot(
			const Vector3& self
			)
		{
			return Dot(self, self);
		}

		/*!
		* 3次元ベクトル 外積算出
		*/
		void Cross(
			Vector3& dst
			, const Vector3& lhs
			, const Vector3& rhs
			)
		{
			Vector3 buf;
			buf.x = lhs.y * rhs.z - lhs.z * rhs.y;
			buf.y = lhs.z * rhs.x - lhs.x * rhs.z;
			buf.z = lhs.x * rhs.y - lhs.y * rhs.x;
			dst = buf;
		}

		/*!
		* 3次元ベクトル 長さ算出（平方前）
		*/
		f32 LengthSq(
			const Vector3& src
			)
		{
			return (
				src.x * src.x + 
				src.y * src.y +
				src.z * src.z
				);
		}
		f32 LengthSq(
			const Vector3& pos1, const Vector3& pos2
			)
		{
			return LengthSq(
				pos2-pos1
				);
		}

		/*!
		* 3次元ベクトル 長さ算出
		*/
		f32 Length(
			const Vector3& src
			)
		{
			return Sqrt(
				LengthSq(src)
				);
		}
		f32 Length(
			const Vector3& pos1, const Vector3& pos2
			)
		{
			return Length(
				pos2-pos1
				);
		}

		/*!
		* 3次元ベクトル 正規化
		*/
		void Normalize(
			Vector3& dst
			, const Vector3& src
			)
		{
			f32 len = Length(src);
			dst.x = src.x / len;
			dst.y = src.y / len;
			dst.z = src.z / len;
		}

		/*!
		* 3次元ベクトル ベクトル間の線形補間
		*/
		void Lerp(
			Vector3& dst
			, const Vector3& a
			, const Vector3& b
			, f32 s
			)
		{
			Vector3 buf;
			Subtract(buf, b, a);
			Multiply(buf, buf, s);
			Add(buf, a, buf);
			dst =  buf;
		}

		/*!
		* 3次元ベクトル 3x3行列による変換
		*/
		void Multiply(
			Vector3& dst
			, const Vector3& lhs
			, const Matrix3& rhs
			)
		{
			Vector3 buf;
			buf.x = lhs.x * rhs.m11 + lhs.y * rhs.m21 + lhs.z * rhs.m31;
			buf.y = lhs.x * rhs.m12 + lhs.y * rhs.m22 + lhs.z * rhs.m32;
			buf.z = lhs.x * rhs.m13 + lhs.y * rhs.m23 + lhs.z * rhs.m33;
			dst = buf;
		}

		/*!
		* 3次元ベクトル 3x3行列による変換
		*/
		void Multiply(
			Vector3& dst
			, const Matrix3& lhs
			, const Vector3& rhs
			)
		{
			Vector3 buf;
			buf.x = lhs.m11 * rhs.x + lhs.m12 * rhs.y + lhs.m13 * rhs.z;
			buf.y = lhs.m21 * rhs.x + lhs.m22 * rhs.y + lhs.m23 * rhs.z;
			buf.z = lhs.m31 * rhs.x + lhs.m32 * rhs.y + lhs.m33 * rhs.z;
			dst = buf;
		}

		/*!
		* 3次元ベクトル 4x4行列による変換
		*/
		void Multiply(
			Vector3& dst
			, const Vector3& lhs
			, const Matrix4& rhs
			)
		{
			Vector3 buf;
			buf.x = lhs.x * rhs.m11 + lhs.y * rhs.m21 + lhs.z * rhs.m31;
			buf.y = lhs.x * rhs.m12 + lhs.y * rhs.m22 + lhs.z * rhs.m32;
			buf.z = lhs.x * rhs.m13 + lhs.y * rhs.m23 + lhs.z * rhs.m33;
			dst = buf;
		}

		/*!
		* 3次元ベクトル 4x4行列による変換
		*/
		void Multiply(
			Vector3& dst
			, const Matrix4& lhs
			, const Vector3 rhs
			)
		{
			Vector3 buf;
			buf.x = lhs.m11 * rhs.x + lhs.m12 * rhs.y + lhs.m13 * rhs.z;
			buf.y = lhs.m21 * rhs.x + lhs.m22 * rhs.y + lhs.m23 * rhs.z;
			buf.z = lhs.m31 * rhs.x + lhs.m32 * rhs.y + lhs.m33 * rhs.z;
			dst = buf;
		}

		/*!
		* 3次元ベクトル 4x4行列による変換
		* z=1としてトランスフォーム変換を行う
		*/
		void Transform(
			Vector3& dst
			, const Vector3& lhs
			, const Matrix4& rhs
			)
		{
			Vector3 buf;
			buf.x = lhs.x * rhs.m11 + lhs.y * rhs.m21 + lhs.z * rhs.m31 + rhs.m41;
			buf.y = lhs.x * rhs.m12 + lhs.y * rhs.m22 + lhs.z * rhs.m32 + rhs.m42;
			buf.z = lhs.x * rhs.m13 + lhs.y * rhs.m23 + lhs.z * rhs.m33 + rhs.m43;
			dst = buf;
		}

		/*!
		* 4次元ベクトル 初期化
		*/
		void Init(
			Vector4& dst
			, f32 _x, f32 _y, f32 _z, f32 _w
			)
		{
			dst.x = _x;
			dst.y = _y;
			dst.z = _z;
			dst.w = _w;
		}

		/*!
		* 4次元ベクトル スカラー加算
		*/
		void Add(
			Vector4& dst
			, const Vector4& lhs
			, f32 rhs
			)
		{
			dst.x = lhs.x + rhs;
			dst.y = lhs.y + rhs;
			dst.z = lhs.z + rhs;
			dst.w = lhs.w + rhs;
		}

		/*!
		* 4次元ベクトル ベクトル加算
		*/
		void Add(
			Vector4& dst
			, const Vector4& lhs
			, const Vector4& rhs
			)
		{
			dst.x = lhs.x + rhs.x;
			dst.y = lhs.y + rhs.y;
			dst.z = lhs.z + rhs.z;
			dst.w = lhs.w + rhs.w;
		}

		/*!
		* 4次元ベクトル スカラー減算
		*/
		void Subtract(
			Vector4& dst
			, const Vector4& lhs
			, f32 rhs
			)
		{
			dst.x = lhs.x - rhs;
			dst.y = lhs.y - rhs;
			dst.z = lhs.z - rhs;
			dst.w = lhs.w - rhs;
		}

		/*!
		* 4次元ベクトル ベクトル減算
		*/
		void Subtract(
			Vector4& dst
			, const Vector4& lhs
			, const Vector4& rhs
			)
		{
			dst.x = lhs.x - rhs.x;
			dst.y = lhs.y - rhs.y;
			dst.z = lhs.z - rhs.z;
			dst.w = lhs.w - rhs.w;
		}

		/*!
		* 4次元ベクトル スカラー乗算
		*/
		void Multiply(
			Vector4& dst
			, const Vector4& lhs
			, f32 rhs
			)
		{
			dst.x = lhs.x * rhs;
			dst.y = lhs.y * rhs;
			dst.z = lhs.z * rhs;
			dst.w = lhs.w * rhs;
		}

		/*!
		* 4次元ベクトル スカラー除算
		*/
		void Divide(
			Vector4& dst
			, const Vector4& lhs
			, f32 rhs
			)
		{
			dst.x = lhs.x / rhs;
			dst.y = lhs.y / rhs;
			dst.z = lhs.z / rhs;
			dst.w = lhs.w / rhs;
		}

		/*!
		* 4次元ベクトル 反転
		*/
		void Reverse(
			Vector4& dst
			, const Vector4& src
			)
		{
			dst.x = -src.x;
			dst.y = -src.y;
			dst.z = -src.z;
			dst.w = -src.w;
		}

		/*!
		* 4次元ベクトル 4x4行列による変換
		*/
		void Multiply(
			Vector4& dst
			, const Vector4& lhs
			, const Matrix4& rhs
			)
		{
			Vector4 buf;
			buf.x = lhs.x * rhs.m11 + lhs.y * rhs.m21 + lhs.z * rhs.m31 + lhs.w * rhs.m41;
			buf.y = lhs.x * rhs.m12 + lhs.y * rhs.m22 + lhs.z * rhs.m32 + lhs.w * rhs.m42;
			buf.z = lhs.x * rhs.m13 + lhs.y * rhs.m23 + lhs.z * rhs.m33 + lhs.w * rhs.m43;
			buf.w = lhs.x * rhs.m14 + lhs.y * rhs.m24 + lhs.z * rhs.m34 + lhs.w * rhs.m44;
			dst = buf;
		}

		/*!
		* 4次元ベクトル 4x4行列による変換
		*/
		void Multiply(
			Vector4& dst
			, const Matrix4& lhs
			, const Vector4& rhs
			)
		{
			Vector4 buf;
			buf.x = lhs.m11 * rhs.x + lhs.m12 * rhs.y + lhs.m13 * rhs.z + lhs.m14 * rhs.w;
			buf.y = lhs.m21 * rhs.x + lhs.m22 * rhs.y + lhs.m23 * rhs.z + lhs.m24 * rhs.w;
			buf.z = lhs.m31 * rhs.x + lhs.m32 * rhs.y + lhs.m33 * rhs.z + lhs.m34 * rhs.w;
			buf.w = lhs.m41 * rhs.x + lhs.m42 * rhs.y + lhs.m43 * rhs.z + lhs.m44 * rhs.w;
			dst = buf;
		}

	}	// namespace VectorOp
}	// namespace ng
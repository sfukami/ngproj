/*!
* @file		ngMatrix4x4.h
* @brief	4x4行列
* @date		2015-10-18
* @author	s.fukami
*/

#ifndef __NG_CORE_MATRIX4X4_H__
#define __NG_CORE_MATRIX4X4_H__

#include "../vector/ngVector4.h"

namespace ng
{
	/*!
	* @brief					4x4行列
	*/
	struct NG_DECL Matrix4x4
	{
		static const s32 ROW;		//!< 行数
		static const s32 COL;		//!< 列数
		static const Matrix4x4 ZERO;		//!< ゼロ行列
		static const Matrix4x4 IDENTITY;	//!< 単位行列

		union
		{
			struct
			{
				Vector4 vx;
				Vector4 vy;
				Vector4 vz;
				Vector4 vw;
			};
			struct
			{
				Vector4 v[4];
			};
			struct
			{
				f32 m11, m12, m13, m14;
				f32 m21, m22, m23, m24;
				f32 m31, m32, m33, m34;
				f32 m41, m42, m43, m44;
			};
			f32 m[4][4];
		};
		
		Matrix4x4(
			f32 _m11 = .0f, f32 _m12 = .0f, f32 _m13 = .0f, f32 _m14 = .0f,
			f32 _m21 = .0f, f32 _m22 = .0f, f32 _m23 = .0f, f32 _m24 = .0f,
			f32 _m31 = .0f, f32 _m32 = .0f, f32 _m33 = .0f, f32 _m34 = .0f,
			f32 _m41 = .0f, f32 _m42 = .0f, f32 _m43 = .0f, f32 _m44 = .0f
			)
			: m11(_m11), m12(_m12), m13(_m13), m14(_m14)
			, m21(_m21), m22(_m22), m23(_m23), m24(_m24)
			, m31(_m31), m32(_m32), m33(_m33), m34(_m34)
			, m41(_m41), m42(_m42), m43(_m43), m44(_m44)
		{ }
		Matrix4x4(const Vector4& _vx, const Vector4& _vy, const Vector4& _vz, const Vector4& _vw)
			: vx(_vx), vy(_vy), vz(_vz), vw(_vw) { }
		explicit Matrix4x4(const f32 pElems[]);
		Vector4& operator[](s32 i) { return v[i]; }
		const Vector4& operator[](s32 i) const { return v[i]; }
		Matrix4x4& operator=(const Matrix4x4& rhs);
		Matrix4x4 operator+() const;
		Matrix4x4 operator-() const;
		Matrix4x4 operator+(const Matrix4x4& rhs) const;
		Matrix4x4 operator-(const Matrix4x4& rhs) const;
		Matrix4x4& operator+=(const Matrix4x4& rhs);
		Matrix4x4& operator-=(const Matrix4x4& rhs);
		bool operator==(const Matrix4x4& rhs) const;
		bool operator!=(const Matrix4x4& rhs) const;
	};

	// 列省略で正方行列として扱う
	typedef Matrix4x4 Matrix4;

	NG_INLINE Matrix4& Matrix4::operator=(const Matrix4& rhs)
	{
		m11 = rhs.m11; m12 = rhs.m12; m13 = rhs.m13; m14 = rhs.m14;
		m21 = rhs.m21; m22 = rhs.m22; m23 = rhs.m23; m24 = rhs.m24;
		m31 = rhs.m31; m32 = rhs.m32; m33 = rhs.m33; m34 = rhs.m34;
		m41 = rhs.m41; m42 = rhs.m42; m43 = rhs.m43; m44 = rhs.m44;
		return (*this);
	}

	NG_INLINE Matrix4 Matrix4::operator+() const
	{
		return (*this);
	}

	NG_INLINE Matrix4 Matrix4::operator-() const
	{
		Matrix4 buf(
			-m11, -m12, -m13, -m14,
			-m21, -m22, -m23, -m24,
			-m31, -m32, -m33, -m34,
			-m41, -m42, -m43, -m44
			);
		return buf;
	}

	NG_INLINE Matrix4 Matrix4::operator+(const Matrix4& rhs) const
	{
		Matrix4 buf(
			m11 + rhs.m11, m12 + rhs.m12, m13 + rhs.m13, m14 + rhs.m14,
			m21 + rhs.m21, m22 + rhs.m22, m23 + rhs.m23, m24 + rhs.m24,
			m31 + rhs.m31, m32 + rhs.m32, m33 + rhs.m33, m34 + rhs.m34,
			m41 + rhs.m41, m42 + rhs.m42, m43 + rhs.m43, m44 + rhs.m44
			);
		return buf;
	}

	NG_INLINE Matrix4 Matrix4::operator-(const Matrix4& rhs) const
	{
		Matrix4 buf(
			m11 - rhs.m11, m12 - rhs.m12, m13 - rhs.m13, m14 - rhs.m14,
			m21 - rhs.m21, m22 - rhs.m22, m23 - rhs.m23, m24 - rhs.m24,
			m31 - rhs.m31, m32 - rhs.m32, m33 - rhs.m33, m34 - rhs.m34,
			m41 - rhs.m41, m42 - rhs.m42, m43 - rhs.m43, m44 - rhs.m44
			);
		return buf;
	}

	NG_INLINE Matrix4& Matrix4::operator+=(const Matrix4& rhs)
	{
		m11 += rhs.m11; m12 += rhs.m12; m13 += rhs.m13; m14 += rhs.m14;
		m21 += rhs.m21; m22 += rhs.m22; m23 += rhs.m23; m24 += rhs.m24;
		m31 += rhs.m31; m32 += rhs.m32; m33 += rhs.m33; m34 += rhs.m34;
		m41 += rhs.m41; m42 += rhs.m42; m43 += rhs.m43; m44 += rhs.m44;
		return (*this);
	}

	NG_INLINE Matrix4& Matrix4::operator-=(const Matrix4& rhs)
	{
		m11 -= rhs.m11; m12 -= rhs.m12; m13 -= rhs.m13; m14 -= rhs.m14;
		m21 -= rhs.m21; m22 -= rhs.m22; m23 -= rhs.m23; m24 -= rhs.m24;
		m31 -= rhs.m31; m32 -= rhs.m32; m33 -= rhs.m33; m34 -= rhs.m34;
		m41 -= rhs.m41; m42 -= rhs.m42; m43 -= rhs.m43; m44 -= rhs.m44;
		return (*this);
	}

	NG_INLINE bool Matrix4::operator==(const Matrix4& rhs) const
	{
		return (
			m11 == rhs.m11 && m12 == rhs.m12 && m13 == rhs.m13 && m14 == rhs.m14 &&
			m21 == rhs.m21 && m22 == rhs.m22 && m23 == rhs.m23 && m24 == rhs.m24 &&
			m31 == rhs.m31 && m32 == rhs.m32 && m33 == rhs.m33 && m34 == rhs.m34 &&
			m41 == rhs.m41 && m42 == rhs.m42 && m43 == rhs.m43 && m44 == rhs.m44
			);
	}

	NG_INLINE bool Matrix4::operator!=(const Matrix4& rhs) const
	{
		return !(*this == rhs);
	}

}	// namespace ng

#endif	// __NG_CORE_Matrix4_H__

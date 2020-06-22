/*!
* @file		ngMatrix3x3.h
* @brief	3x3行列
* @date		2015-10-18
* @author	s.fukami
*/

#ifndef __NG_CORE_MATRIX3X3_H__
#define __NG_CORE_MATRIX3X3_H__

#include "../vector/ngVector3.h"

namespace ng
{
	/*!
	* @brief					3x3行列
	*/
	struct NG_DECL Matrix3x3
	{
		static const s32 ROW;		//!< 行数
		static const s32 COL;		//!< 列数
		static const Matrix3x3 ZERO;		//!< ゼロ行列
		static const Matrix3x3 IDENTITY;	//!< 単位行列

		union
		{
			struct
			{
				Vector3 vx;
				Vector3 vy;
				Vector3 vz;
			};
			struct
			{
				Vector3 v[3];
			};
			struct
			{
				f32 m11, m12, m13;
				f32 m21, m22, m23;
				f32 m31, m32, m33;
			};
			f32 m[3][3];
		};

		Matrix3x3(
			f32 _m11 = .0f, f32 _m12 = .0f, f32 _m13 = .0f,
			f32 _m21 = .0f, f32 _m22 = .0f, f32 _m23 = .0f,
			f32 _m31 = .0f, f32 _m32 = .0f, f32 _m33 = .0f
			)
			: m11(_m11), m12(_m12), m13(_m13)
			, m21(_m21), m22(_m22), m23(_m23)
			, m31(_m31), m32(_m32), m33(_m33)
		{ }
		Matrix3x3(const Vector3& _vx, const Vector3& _vy, const Vector3& _vz)
			: vx(_vx), vy(_vy), vz(_vz) { }
		explicit Matrix3x3(const f32 pElems[]);
		Vector3& operator[](s32 i) { return v[i]; }
		const Vector3& operator[](s32 i) const { return v[i]; }
		Matrix3x3& operator=(const Matrix3x3& rhs);
		Matrix3x3 operator+() const;
		Matrix3x3 operator-() const;
		Matrix3x3 operator+(const Matrix3x3& rhs) const;
		Matrix3x3 operator-(const Matrix3x3& rhs) const;
		Matrix3x3& operator+=(const Matrix3x3& rhs);
		Matrix3x3& operator-=(const Matrix3x3& rhs);
		bool operator==(const Matrix3x3& rhs) const;
		bool operator!=(const Matrix3x3& rhs) const;
	};

	// 列省略で正方行列として扱う
	typedef Matrix3x3 Matrix3;

	NG_INLINE Matrix3& Matrix3::operator=(const Matrix3& rhs)
	{
		m11 = rhs.m11; m12 = rhs.m12; m13 = rhs.m13;
		m21 = rhs.m21; m22 = rhs.m22; m23 = rhs.m23;
		m31 = rhs.m31; m32 = rhs.m32; m33 = rhs.m33;
		return (*this);
	}

	NG_INLINE Matrix3 Matrix3::operator+() const
	{
		return (*this);
	}

	NG_INLINE Matrix3 Matrix3::operator-() const
	{
		Matrix3 buf(
			-m11, -m12, -m13,
			-m21, -m22, -m23,
			-m31, -m32, -m33
			);
		return buf;
	}

	NG_INLINE Matrix3 Matrix3::operator+(const Matrix3& rhs) const
	{
		Matrix3 buf(
			m11 + rhs.m11, m12 + rhs.m12, m13 + rhs.m13,
			m21 + rhs.m21, m22 + rhs.m22, m23 + rhs.m23,
			m31 + rhs.m31, m32 + rhs.m32, m33 + rhs.m33
			);
		return buf;
	}

	NG_INLINE Matrix3 Matrix3::operator-(const Matrix3& rhs) const
	{
		Matrix3 buf(
			m11 - rhs.m11, m12 - rhs.m12, m13 - rhs.m13,
			m21 - rhs.m21, m22 - rhs.m22, m23 - rhs.m23,
			m31 - rhs.m31, m32 - rhs.m32, m33 - rhs.m33
			);
		return buf;
	}

	NG_INLINE Matrix3& Matrix3::operator+=(const Matrix3& rhs)
	{
		m11 += rhs.m11; m12 += rhs.m12; m13 += rhs.m13;
		m21 += rhs.m21; m22 += rhs.m22; m23 += rhs.m23;
		m31 += rhs.m31; m32 += rhs.m32; m33 += rhs.m33;
		return (*this);
	}

	NG_INLINE Matrix3& Matrix3::operator-=(const Matrix3& rhs)
	{
		m11 -= rhs.m11; m12 -= rhs.m12; m13 -= rhs.m13;
		m21 -= rhs.m21; m22 -= rhs.m22; m23 -= rhs.m23;
		m31 -= rhs.m31; m32 -= rhs.m32; m33 -= rhs.m33;
		return (*this);
	}

	NG_INLINE bool Matrix3::operator==(const Matrix3& rhs) const
	{
		return (
			m11 == rhs.m11 && m12 == rhs.m12 && m13 == rhs.m13 &&
			m21 == rhs.m21 && m22 == rhs.m22 && m23 == rhs.m23 &&
			m31 == rhs.m31 && m32 == rhs.m32 && m33 == rhs.m33
			);
	}

	NG_INLINE bool Matrix3::operator!=(const Matrix3& rhs) const
	{
		return !(*this == rhs);
	}

}	// namespace ng

#endif	// __NG_CORE_MATRIX3X3_H__

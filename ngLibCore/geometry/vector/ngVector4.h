/*!
* @file		ngVector4.h
* @brief	4次元ベクトル
* @date		2013-10-18
* @author	s.fukami
*/

#ifndef __NG_CORE_VECTOR4_H__
#define __NG_CORE_VECTOR4_H__

namespace ng
{
	/*!
	* @brief					4次元ベクトル
	*/
	struct NG_DECL Vector4
	{
		static const s32 ROW;			//!< 行数
		static const s32 COL;			//!< 列数
		static const Vector4 ZERO;		//!< ゼロベクトル
		static const Vector4 ONE;		//!< 全ての要素が1のベクトル
		static const Vector4 X_AXIS;	//!< X軸ベクトル
		static const Vector4 Y_AXIS;	//!< Y軸ベクトル
		static const Vector4 Z_AXIS;	//!< Z軸ベクトル
		static const Vector4 W_AXIS;	//!< W軸ベクトル

		union
		{
			struct
			{
				f32 x, y, z, w;
			};
			struct
			{
				f32 r, g, b, a;
			};
			f32 m[4];
		};

		Vector4(f32 _x = 0.0f, f32 _y = 0.0f, f32 _z = 0.0f, f32 _w = 0.0f)
			: x(_x), y(_y), z(_z), w(_w) { }
		explicit Vector4(const f32 pElems[]);
		f32 operator[](s32 i) const { return m[i]; }
		Vector4& operator=(const Vector4& rhs);
		Vector4 operator+() const;
		Vector4 operator-() const;
		Vector4 operator+(f32 rhs) const;
		Vector4 operator-(f32 rhs) const;
		Vector4 operator*(f32 rhs) const;
		Vector4 operator/(f32 rhs) const;
		Vector4 operator+(const Vector4& rhs) const;
		Vector4 operator-(const Vector4& rhs) const;
		Vector4& operator+=(f32 rhs);
		Vector4& operator-=(f32 rhs);
		Vector4& operator*=(f32 rhs);
		Vector4& operator/=(f32 rhs);
		Vector4& operator+=(const Vector4& rhs);
		Vector4& operator-=(const Vector4& rhs);
		bool operator==(const Vector4& rhs) const;
		bool operator!=(const Vector4& rhs) const;
	};

	NG_INLINE Vector4& Vector4::operator=(const Vector4& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;
		return (*this);
	}

	NG_INLINE Vector4 Vector4::operator+() const
	{
		return (*this);
	}

	NG_INLINE Vector4 Vector4::operator-() const
	{
		Vector4 buf(-x, -y, -z, -w);
		return buf;
	}

	NG_INLINE Vector4 Vector4::operator+(f32 rhs) const
	{
		Vector4 buf(
			x + rhs,
			y + rhs,
			z + rhs,
			w + rhs
			);
		return buf;
	}

	NG_INLINE Vector4 Vector4::operator-(f32 rhs) const
	{
		Vector4 buf(
			x - rhs,
			y - rhs,
			z - rhs,
			w - rhs
			);
		return buf;
	}

	NG_INLINE Vector4 Vector4::operator*(f32 rhs) const
	{
		Vector4 buf(
			x * rhs,
			y * rhs,
			z * rhs,
			w * rhs
			);
		return buf;
	}

	NG_INLINE Vector4 Vector4::operator/(f32 rhs) const
	{
		Vector4 buf(
			x / rhs,
			y / rhs,
			z / rhs,
			w / rhs
			);
		return buf;
	}

	NG_INLINE Vector4 Vector4::operator+(const Vector4& rhs) const
	{
		Vector4 buf(
			x + rhs.x,
			y + rhs.y,
			z + rhs.z,
			w + rhs.w
			);
		return buf;
	}

	NG_INLINE Vector4 Vector4::operator-(const Vector4& rhs) const
	{
		Vector4 buf(
			x - rhs.x,
			y - rhs.y,
			z - rhs.z,
			w - rhs.w
			);
		return buf;
	}

	NG_INLINE Vector4& Vector4::operator+=(f32 rhs)
	{
		x += rhs;
		y += rhs;
		z += rhs;
		w += rhs;
		return (*this);
	}

	NG_INLINE Vector4& Vector4::operator-=(f32 rhs)
	{
		x -= rhs;
		y -= rhs;
		z -= rhs;
		w -= rhs;
		return (*this);
	}

	NG_INLINE Vector4& Vector4::operator*=(f32 rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		w *= rhs;
		return (*this);
	}

	NG_INLINE Vector4& Vector4::operator/=(f32 rhs)
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;
		w /= rhs;
		return (*this);
	}

	NG_INLINE Vector4& Vector4::operator+=(const Vector4& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;
		return (*this);
	}

	NG_INLINE Vector4& Vector4::operator-=(const Vector4& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;
		return (*this);
	}

	NG_INLINE bool Vector4::operator==(const Vector4& rhs) const
	{
		return (x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w);
	}

	NG_INLINE bool Vector4::operator!=(const Vector4& rhs) const
	{
		return !(*this == rhs);
	}

}	// namespace ng

#endif	// __NG_CORE_VECTOR4_H__
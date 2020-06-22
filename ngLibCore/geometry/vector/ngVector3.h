/*!
* @file		ngVector3.h
* @brief	3次元ベクトル
* @date		2013-10-18
* @author	s.fukami
*/

#ifndef __NG_CORE_VECTOR3_H__
#define __NG_CORE_VECTOR3_H__

namespace ng
{
	/*!
	* @brief					3次元ベクトル
	*/
	struct NG_DECL Vector3
	{
		static const s32 ROW;			//!< 行数
		static const s32 COL;			//!< 列数
		static const Vector3 ZERO;		//!< ゼロベクトル
		static const Vector3 ONE;		//!< 全ての要素が1のベクトル
		static const Vector3 AXIS_X;	//!< X軸ベクトル
		static const Vector3 AXIS_Y;	//!< Y軸ベクトル
		static const Vector3 AXIS_Z;	//!< Z軸ベクトル

		union
		{
			struct
			{
				f32 x, y, z;
			};
			struct
			{
				f32 r, g, b;
			};
			f32 m[3];
		};

		Vector3(f32 _x = .0f, f32 _y = .0f, f32 _z = .0f)
			: x(_x), y(_y), z(_z) { }
		explicit Vector3(const f32 pElems[]);
		f32 operator[](s32 i) const { return m[i]; }
		Vector3& operator=(const Vector3& rhs);
		Vector3 operator+() const;
		Vector3 operator-() const;
		Vector3 operator+(f32 rhs) const;
		Vector3 operator-(f32 rhs) const;
		Vector3 operator*(f32 rhs) const;
		Vector3 operator/(f32 rhs) const;
		Vector3 operator+(const Vector3& rhs) const;
		Vector3 operator-(const Vector3& rhs) const;
		Vector3& operator+=(f32 rhs);
		Vector3& operator-=(f32 rhs);
		Vector3& operator*=(f32 rhs);
		Vector3& operator/=(f32 rhs);
		Vector3& operator+=(const Vector3& rhs);
		Vector3& operator-=(const Vector3& rhs);
		bool operator==(const Vector3& rhs) const;
		bool operator!=(const Vector3& rhs) const;
	};

	NG_INLINE Vector3& Vector3::operator=(const Vector3& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return (*this);
	}

	NG_INLINE Vector3 Vector3::operator+() const
	{
		return (*this);
	}

	NG_INLINE Vector3 Vector3::operator-() const
	{
		Vector3 buf(-x, -y, -z);
		return buf;
	}

	NG_INLINE Vector3 Vector3::operator+(f32 rhs) const
	{
		Vector3 buf(
			x + rhs,
			y + rhs,
			z + rhs
			);
		return buf;
	}

	NG_INLINE Vector3 Vector3::operator-(f32 rhs) const
	{
		Vector3 buf(
			x - rhs,
			y - rhs,
			z - rhs
			);
		return buf;
	}

	NG_INLINE Vector3 Vector3::operator*(f32 rhs) const
	{
		Vector3 buf(
			x * rhs,
			y * rhs,
			z * rhs
			);
		return buf;
	}

	NG_INLINE Vector3 Vector3::operator/(f32 rhs) const
	{
		Vector3 buf(
			x / rhs,
			y / rhs,
			z / rhs
			);
		return buf;
	}

	NG_INLINE Vector3 Vector3::operator+(const Vector3& rhs) const
	{
		Vector3 buf(
			x + rhs.x,
			y + rhs.y,
			z + rhs.z
			);
		return buf;
	}

	NG_INLINE Vector3 Vector3::operator-(const Vector3& rhs) const
	{
		Vector3 buf(
			x - rhs.x,
			y - rhs.y,
			z - rhs.z
			);
		return buf;
	}

	NG_INLINE Vector3& Vector3::operator+=(f32 rhs)
	{
		x += rhs;
		y += rhs;
		z += rhs;
		return (*this);
	}

	NG_INLINE Vector3& Vector3::operator-=(f32 rhs)
	{
		x -= rhs;
		y -= rhs;
		z -= rhs;
		return (*this);
	}

	NG_INLINE Vector3& Vector3::operator*=(f32 rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return (*this);
	}

	NG_INLINE Vector3& Vector3::operator/=(f32 rhs)
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;
		return (*this);
	}

	NG_INLINE Vector3& Vector3::operator+=(const Vector3& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return (*this);
	}

	NG_INLINE Vector3& Vector3::operator-=(const Vector3& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return (*this);
	}

	NG_INLINE bool Vector3::operator==(const Vector3& rhs) const
	{
		return (
			x == rhs.x &&
			y == rhs.y &&
			z == rhs.z
			);
	}

	NG_INLINE bool Vector3::operator!=(const Vector3& rhs) const
	{
		return !(*this == rhs);
	}

}	// namespace ng

#endif	// __NG_CORE_VECTOR3_H__
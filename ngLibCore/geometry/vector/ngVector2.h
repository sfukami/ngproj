/*!
* @file		ngVector2.h
* @brief	2次元ベクトル
* @date		2013-10-18
* @author	s.fukami
*/

#ifndef __NG_CORE_VECTOR2_H__
#define __NG_CORE_VECTOR2_H__

namespace ng
{
	/*!
	* @brief					2次元ベクトル
	*/
	struct NG_DECL Vector2
	{
		static const s32 ROW;			//!< 行数
		static const s32 COL;			//!< 列数
		static const Vector2 ZERO;		//!< ゼロベクトル
		static const Vector2 ONE;		//!< 全ての要素が1のベクトル
		static const Vector2 AXIS_X;	//!< X軸ベクトル
		static const Vector2 AXIS_Y;	//!< Y軸ベクトル

		union
		{
			struct
			{
				f32 x, y;
			};
			struct
			{
				f32 r, g;
			};
			f32 m[2];
		};

		Vector2(f32 _x=.0f, f32 _y=.0f)
			: x(_x), y(_y) { }
		explicit Vector2(const f32 pElems[]);
		f32 operator[](s32 i) const { return m[i]; }
		Vector2& operator=(const Vector2& rhs);
		Vector2 operator+() const;
		Vector2 operator-() const;
		Vector2 operator+(f32 rhs) const;
		Vector2 operator-(f32 rhs) const;
		Vector2 operator*(f32 rhs) const;
		Vector2 operator/(f32 rhs) const;
		Vector2 operator+(const Vector2& rhs) const;
		Vector2 operator-(const Vector2& rhs) const;
		Vector2& operator+=(f32 rhs);
		Vector2& operator-=(f32 rhs);
		Vector2& operator*=(f32 rhs);
		Vector2& operator/=(f32 rhs);
		Vector2& operator+=(const Vector2& rhs);
		Vector2& operator-=(const Vector2& rhs);
		bool operator==(const Vector2& rhs) const;
		bool operator!=(const Vector2& rhs) const;
	};

	NG_INLINE Vector2& Vector2::operator=(const Vector2& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		return (*this);
	}

	NG_INLINE Vector2 Vector2::operator+() const
	{
		return (*this);
	}

	NG_INLINE Vector2 Vector2::operator-() const
	{
		Vector2 buf(-x, -y);
		return buf;
	}

	NG_INLINE Vector2 Vector2::operator+(f32 rhs) const
	{
		Vector2 buf(
			x + rhs,
			y + rhs
			);
		return buf;
	}

	NG_INLINE Vector2 Vector2::operator-(f32 rhs) const
	{
		Vector2 buf(
			x - rhs,
			y - rhs
			);
		return buf;
	}

	NG_INLINE Vector2 Vector2::operator*(f32 rhs) const
	{
		Vector2 buf(
			x * rhs,
			y * rhs
			);
		return buf;
	}

	NG_INLINE Vector2 Vector2::operator/(f32 rhs) const
	{
		Vector2 buf(
			x / rhs,
			y / rhs
			);
		return buf;
	}

	NG_INLINE Vector2 Vector2::operator+(const Vector2& rhs) const
	{
		return (*this);
	}

	NG_INLINE Vector2 Vector2::operator-(const Vector2& rhs) const
	{
		Vector2 buf(
			x - rhs.x,
			y - rhs.y
			);
		return buf;
	}

	NG_INLINE Vector2& Vector2::operator+=(f32 rhs)
	{
		x += rhs;
		y += rhs;
		return (*this);
	}

	NG_INLINE Vector2& Vector2::operator-=(f32 rhs)
	{
		x -= rhs;
		y -= rhs;
		return (*this);
	}

	NG_INLINE Vector2& Vector2::operator*=(f32 rhs)
	{
		x *= rhs;
		y *= rhs;
		return (*this);
	}

	NG_INLINE Vector2& Vector2::operator/=(f32 rhs)
	{
		x /= rhs;
		y /= rhs;
		return (*this);
	}

	NG_INLINE Vector2& Vector2::operator+=(const Vector2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return (*this);
	}

	NG_INLINE Vector2& Vector2::operator-=(const Vector2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return (*this);
	}

	NG_INLINE bool Vector2::operator==(const Vector2& rhs) const
	{
		return ( x == rhs.x && y == rhs.y );
	}

	NG_INLINE bool Vector2::operator!=(const Vector2& rhs) const
	{
		return !(*this == rhs);
	}

}	// namespace ng

#endif	// __NG_CORE_VECTOR2_H__
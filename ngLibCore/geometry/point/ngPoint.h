/*!
* @file		ngPoint.h
* @brief	2次元座標
* @date		2019-08-10
* @author	s.fukami
*/

#ifndef __NG_CORE_POINT_H__
#define __NG_CORE_POINT_H__

namespace ng
{
	/*!
	* @brief					2次元座標
	*/
	struct NG_DECL Point
	{
		static const Point ZERO;	//!< ゼロ

		union
		{
			struct
			{
				s32 x, y;
			};
			s32 m[2];
		};

		Point(s32 _x = 0, s32 _y = 0)
			: x(_x), y(_y) { }
		s32 operator[](s32 i) const { return m[i]; }
		Point& operator=(const Point& rhs);
		Point operator+() const;
		Point operator-() const;
		Point operator+(const Point& rhs) const;
		Point operator-(const Point& rhs) const;
		Point& operator+=(const Point& rhs);
		Point& operator-=(const Point& rhs);
		bool operator==(const Point& rhs) const;
		bool operator!=(const Point& rhs) const;
	};

	NG_INLINE Point& Point::operator=(const Point& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		return (*this);
	}

	NG_INLINE Point Point::operator+() const
	{
		return (*this);
	}

	NG_INLINE Point Point::operator-() const
	{
		return Point(-x, -y);
	}

	NG_INLINE Point Point::operator+(const Point& rhs) const
	{
		return Point(
			x + rhs.x,
			y + rhs.y
			);
	}

	NG_INLINE Point Point::operator-(const Point& rhs) const
	{
		return Point(
			x - rhs.x,
			y - rhs.y
			);
	}

	NG_INLINE Point& Point::operator+=(const Point& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return (*this);
	}

	NG_INLINE Point& Point::operator-=(const Point& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return (*this);
	}

	NG_INLINE bool Point::operator==(const Point& rhs) const
	{
		return (x == rhs.x && y == rhs.y);
	}

	NG_INLINE bool Point::operator!=(const Point& rhs) const
	{
		return !(*this == rhs);
	}

}	// namespace ng

#endif	// __NG_CORE_POINT_H__
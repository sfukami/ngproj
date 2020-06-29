/*!
* @file		ngColor.h
* @brief	色情報
* @date		2019-08-15
* @author	s.fukami
*/

#ifndef __NG_CORE_COLOR_H__
#define __NG_CORE_COLOR_H__

namespace ng
{
	struct Vector4;
	struct Vector3;
	enum class eColorCode : u32;
}

namespace ng
{
	/*!
	* @brief					色情報 RGBA[0,1]
	*/
	struct NG_DECL Color
	{
		union
		{
			struct
			{
				f32 r, g, b, a;
			};
			f32 m[4];
		};

		Color()
			: r(0.f), g(0.f), b(0.f), a(1.f) { }
		Color(f32 _r, f32 _g, f32 _b, f32 _a = 1.f)
			: r(_r), g(_g), b(_b), a(_a) { }
		explicit Color(const Vector4& v);
		explicit Color(const Vector3& v);
		explicit Color(eColorCode code);
		f32 operator[](s32 index) const { return m[index]; }
		Color& operator=(const Color& rhs);
		Color operator+() const;
		Color operator-() const;
		Color operator+(f32 rhs) const;
		Color operator-(f32 rhs) const;
		Color operator*(f32 rhs) const;
		Color operator/(f32 rhs) const;
		Color operator+(const Color& rhs) const;
		Color operator-(const Color& rhs) const;
		Color& operator+=(f32 rhs);
		Color& operator-=(f32 rhs);
		Color& operator*=(f32 rhs);
		Color& operator/=(f32 rhs);
		Color& operator+=(const Color& rhs);
		Color& operator-=(const Color& rhs);
		bool operator==(const Color& rhs) const;
		bool operator!=(const Color& rhs) const;
	};

	NG_INLINE Color& Color::operator=(const Color& rhs)
	{
		r = rhs.r;
		g = rhs.g;
		b = rhs.b;
		a = rhs.a;
		return (*this);
	}

	NG_INLINE Color Color::operator+() const
	{
		return (*this);
	}

	NG_INLINE Color Color::operator-() const
	{
		return Color(-r, -g, -b, -a);
	}

	NG_INLINE Color Color::operator+(f32 rhs) const
	{
		return Color(
			r + rhs,
			g + rhs,
			b + rhs,
			a + rhs
			);
	}

	NG_INLINE Color Color::operator-(f32 rhs) const
	{
		return Color(
			r - rhs,
			g - rhs,
			b - rhs,
			a - rhs
			);
	}

	NG_INLINE Color Color::operator*(f32 rhs) const
	{
		return Color(
			r * rhs,
			g * rhs,
			b * rhs,
			a * rhs
			);
	}

	NG_INLINE Color Color::operator/(f32 rhs) const
	{
		return Color(
			r / rhs,
			g / rhs,
			b / rhs,
			a / rhs
			);
	}

	NG_INLINE Color Color::operator+(const Color& rhs) const
	{
		return Color(
			r + rhs.r,
			g + rhs.g,
			b + rhs.b,
			a + rhs.a
			);
	}
	
	NG_INLINE Color Color::operator-(const Color& rhs) const
	{
		return Color(
			r - rhs.r,
			g - rhs.g,
			b - rhs.b,
			a - rhs.a
			);
	}
	
	NG_INLINE Color& Color::operator+=(f32 rhs)
	{
		r += rhs;
		g += rhs;
		b += rhs;
		a += rhs;
		return (*this);
	}

	NG_INLINE Color& Color::operator-=(f32 rhs)
	{
		r -= rhs;
		g -= rhs;
		b -= rhs;
		a -= rhs;
		return (*this);
	}

	NG_INLINE Color& Color::operator*=(f32 rhs)
	{
		r *= rhs;
		g *= rhs;
		b *= rhs;
		a *= rhs;
		return (*this);
	}

	NG_INLINE Color& Color::operator/=(f32 rhs)
	{
		r /= rhs;
		g /= rhs;
		b /= rhs;
		a /= rhs;
		return (*this);
	}

	NG_INLINE Color& Color::operator+=(const Color& rhs)
	{
		r += rhs.r;
		g += rhs.g;
		b += rhs.b;
		a += rhs.a;
		return (*this);
	}

	NG_INLINE Color& Color::operator-=(const Color& rhs)
	{
		r -= rhs.r;
		g -= rhs.g;
		b -= rhs.b;
		a -= rhs.a;
		return (*this);
	}

	NG_INLINE bool Color::operator==(const Color& rhs) const
	{
		return (
			r == rhs.r &&
			g == rhs.g &&
			b == rhs.b &&
			a == rhs.a
			);
	}
	
	NG_INLINE bool Color::operator!=(const Color& rhs) const
	{
		return !(*this == rhs);
	}
	
}	// namespace ng

#endif	// __NG_CORE_COLOR_H__
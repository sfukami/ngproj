/*!
* @file		ngMath.cpp
* @brief	算術演算
* @date		2014-04-28
* @author	s.fukami
*/

#include <math.h>
#include <limits.h>
#include <cmath>
#include "ngMath.h"
#include "ngLibCore/common/debug/ngDbgMacro.h"

namespace ng
{
	template <typename T>
	NG_DECL T _wrapFloat(const T& n, const T& low, const T& high)
	{
		NG_ASSERT(low < high);
		const T buf = std::fmod(n - low, high - low);
		return (buf >= 0) ? (n + low) : (n + high);
	}
	template <>
	NG_DECL f32 Wrap<f32>(const f32& n, const f32& low, const f32& high)
	{
		return _wrapFloat(n, low, high);
	}
	template <>
	NG_DECL f64 Wrap<f64>(const f64& n, const f64& low, const f64& high)
	{
		return _wrapFloat(n, low, high);
	}

	template <typename T>
	NG_DECL T _absFloat(const T& x)
	{
		return x > 0.0f ? x : -x;
	}
	template <>
	NG_DECL f32 Abs(const f32& x)
	{
		return _absFloat(x);
	}
	template <>
	NG_DECL f64 Abs(const f64& x)
	{
		return _absFloat(x);
	}

	NG_DECL bool FloatEq(
		float x, float y,
		float tolerance
		)
	{
		if(tolerance == 0.0f)
		{
			return (x == y);
		}
		return (
			((y - tolerance) < x) && 
			(x < (y + tolerance))
			);
	}

	NG_DECL bool DoubleEq(
		double x, double y,
		double tolerance
		)
	{
		if(tolerance == 0.0)
		{
			return (x == y);
		}
		return (
			((y - tolerance) < x) && 
			(x < (y + tolerance))
			);
	}

	NG_DECL float Sqrt(
		float x,
		float tolerance
		)
	{
		return ::sqrt(x);
	}

	NG_DECL int Factorial(int n)
	{
		int res = 1;
		while(n>1)
		{
			res *= n;
			n--;
		}
		return res;
	}

	NG_DECL float DegreeToRadian(float deg)
	{
		return (deg * NG_PI / 180.0f);
	}

	NG_DECL float RadianToDegree(float rad)
	{
		return (rad * 180.0f / NG_PI);
	}

	NG_DECL float Sin(float rad)
	{
		return ::sin(rad);
	}

	NG_DECL float Cos(float rad)
	{
		return Sin(rad + NG_PI * 0.5f);
	}

	NG_DECL float Tan(float rad)
	{
		float c = Cos(rad);

		// 角度90度の場合、タンジェントは無限になる
		if(c == 0.0f)
		{
			return FLT_MAX;
		}
		return (Sin(rad) / c);
	}

	NG_DECL float Cot(float rad)
	{
		return (1.0f / Tan(rad));
	}

	NG_DECL float ASin(float x)
	{
		return ::asin(x);
	}

	NG_DECL float ACos(float x)
	{
		return ::acos(x);
	}

	NG_DECL float ATan2(float y, float x)
	{
		return ::atan2(y, x);
	}

}	// namespace ng
/*!
* @file		ngMath.h
* @brief	算術演算
* @date		2015-04-28
* @author	s.fukami
*/

#ifndef __NG_CORE_MATH_H__
#define __NG_CORE_MATH_H__

#include <float.h>
#include "ngMathDef.h"

namespace ng
{
	/*!
	* @brief					最大値を取得する
	*/
	template <typename T>
	NG_INLINE NG_DECL T Max(const T& lhs, const T& rhs)
	{
		return (lhs > rhs) ? lhs : rhs;
	}

	/*!
	* @brief					最小値を取得する
	*/
	template <typename T>
	NG_INLINE NG_DECL T Min(const T& lhs, const T& rhs)
	{
		return (lhs < rhs) ? lhs : rhs;
	}

	/*!
	* @brief					min以上、max以下の値にクランプ
	* @param n					クランプする値
	* @param min				クランプ最小値
	* @param min				クランプ最大値
	* @return					クランプ後の値
	*/
	template <class T>
	NG_INLINE NG_DECL T Clamp(const T& n, const T& min, const T& max)
	{
		if(n < min) return min;
		if(n > max) return max;
		return n;
	}
	template <class T>
	NG_INLINE NG_DECL T Clamp01(const T& n)
	{
		return Clamp(n, T(0), T(1));
	}

	/*!
	* @brief					ラップアラウンド
	* @attention				上限値は含まない
	*/
	template <typename T>
	NG_DECL T Wrap(const T& n, const T& low, const T& high)
	{
		NG_ASSERT(low < high);
		const T buf = (n - low) % (high - low);
		return (buf >= 0) ? (n + low) : (n + high);
	}
	template <>
	NG_DECL f32 Wrap<f32>(const f32& n, const f32& low, const f32& high);
	template <>
	NG_DECL f64 Wrap<f64>(const f64& n, const f64& low, const f64& high);
	
	/*!
	* @brief					正規化
	*/
	template <typename T>
	NG_DECL f32 Normalize(const T& x, const T& min, const T& max)
	{
		return Clamp01((x - min) / (f32)(max - min));
	}

	/*!
	* @brief					絶対値を算出する
	*/
	template <typename T>
	NG_DECL T Abs(const T& x)
	{
		#define T_BIT	(sizeof(T)*CHAR_BIT)
		return (x^(x>>(T_BIT-1)) - (x>>(T_BIT-1)));
	}
	template <>
	NG_DECL f32 Abs(const f32& x);
	template <>
	NG_DECL f64 Abs(const f64& x);

	/*!
	* @brief					乱数を生成する
	* @param beg 				乱数下限
	* @param end 				乱数上限
	*/
	template <typename T>
	NG_DECL T Random(const T& beg, const T& end)
	{
		return 
			(T)((rand() / (float)RAND_MAX) * (end - beg + 1)) + beg;
	}

	/*!
	* @brief					2乗計算
	*/
	template <typename T>
	NG_DECL T Square(const T& x)
	{
		return x*x;
	}

	/*!
	* @brief					3乗計算
	*/
	template <typename T>
	NG_DECL T Cube(const T& x)
	{
		return x*x*x;
	}

	/*!
	* @brief					累乗計算。xのy乗を算出する
	*/
	template <typename T>
	NG_DECL T Power(const T& x, unsigned y)
	{
		T ret = 1;
		for(unsigned i=0; i<y; i++)
		{
			ret *= x;
		}
		return ret;
	}

	/*!
	* @brief					float比較
	* @param tolerance			許容誤差
	*/
	NG_DECL bool FloatEq(
		float x, float y,
		float tolerance = NG_FLT_EPSILON
		);

	/*!
	* @brief					double比較
	* @param tolerance			許容誤差
	*/
	NG_DECL bool DoubleEq(
		double x, double y,
		double tolerance = NG_DBL_EPSILON
		);

	/*!
	* @brief					平方根を算出する
	* @param tolerance			許容誤差
	*/
	NG_DECL float Sqrt(
		float x,
		float tolerance = NG_SQRTTRL_DEF
		);

	/*!
	* @brief					階乗を算出する
	*/
	NG_DECL int Factorial(int n);

	/*!
	* @brief					角度をラジアンに変換
	*/
	NG_DECL float DegreeToRadian(float deg);

	/*!
	* @brief					ラジアンを角度に変換
	*/
	NG_DECL float RadianToDegree(float rad);

	/*!
	* @brief					テーブルを参照し、サイン（正弦）を算出する
	*/
	NG_DECL float Sin(float rad);

	/*!
	* @brief					テーブルを参照し、コサイン（余弦）を算出する
	*/
	NG_DECL float Cos(float rad);

	/*!
	* @brief					テーブルを参照し、タンジェント（正接）を算出する
	*/
	NG_DECL float Tan(float rad);

	/*!
	* @brief					テーブルを参照し、コタンジェント（余接）を算出する
	*/
	NG_DECL float Cot(float rad);

	/*!
	* @brief					アークサイン（逆正弦）を算出する
	*/
	NG_DECL float ASin(float x);

	/*!
	* @brief					アークコサイン（逆余弦）を算出する
	*/
	NG_DECL float ACos(float x);

	/*!
	* @brief					アークタンジェント（逆正接）を算出する
	*/
	NG_DECL float ATan2(float y, float x);

}	// namespace ng

/*!
* @brief					指定の型が符号付きかどうか判定
*/
#define NG_IS_SIGNED(type) \
	( std::numeric_limits<type>::is_signed )

/*!
* @brief					指定の型が整数型かどうか判定
*/
#define NG_IS_INTEGER(type) \
	( std::numeric_limits<type>::is_integer )

/*!
* @brief					指定の整数型が2の補数表現かどうか判定
*/
#define NG_IS_TWOS_COMPLEMENT(type) \
	( ng::IsTwosComplement<type>::result )

/*!
* @brief					指定の整数型が1の補数表現かどうか判定
*/
#define NG_IS_ONES_COMPLEMENT(type) \
	( ng::IsOnesComplement<type>::result )

/*!
* @brief					指定の整数型が「符号付き＋絶対値」かどうか判定
*/
#define NG_IS_SIGNED_MAGNITUDE(type) \
	( ng::IsSignedMagnitude<type>::result )

/*!
* @brief					指定の型における非符号ビット（基数の桁数）を取得
* @attention				小数点数型の場合、仮数部の桁数（基数）である
*							FLT_MANT_DIG, DBL_MANT_DIG, LDBL_MANT_DIGに相当
*/
#define NG_NON_SIGNE_BITS(type) \
	( std::numeric_limits<type>::digits )

/*!
* @brief					浮動小数点型の10を基数とした、表現可能な最小の指数を取得
* @note						FLT_MIN_10_EXP, DBL_MIN_10_EXP, LDBL_MIN_10_EXPに相当する
*/
#define NG_MIN_EXP10(type) \
	( std::numeric_limits<type>::min_exponent10 )

/*!
* @brief					浮動小数点型の10を基数とした、表現可能な最大の指数を取得
* @note						FLT_MAX_10_EXP, DBL_MAX_10_EXP, LDBL_MAX_10_EXPに相当する
*/
#define NG_MAX_EXP10(type) \
	( std::numeric_limits<type>::max_exponent10 )

/*!
* @brief					浮動小数点型の基数を用いた、表現可能な最小の指数を取得
* @note						FLT_MIN_EXP, DBL_MIN_EXP, LDBL_MIN_EXPに相当する
*							基数はFLT_RADIX, DBL_RADIX, LDBL_RADIXが相当する
*/
#define NG_MIN_EXP(type) \
	( std::numeric_limits<type>::min_exponent )

/*!
* @brief					浮動小数点型の基数を用いた、表現可能な最大の指数を取得
* @note						FLT_MAX_EXP, DBL_MAX_EXP, LDBL_MAX_EXPに相当する
*							基数はFLT_RADIX, DBL_RADIX, LDBL_RADIXが相当する
*/
#define NG_MAX_EXP(type) \
	( std::numeric_limits<type>::max_exponent )

/*!
* @brief					指定の型の基数を取得
* @note						整数型の場合は表現のベース
*							小数点数型の場合は指数部の底
*/
#define NG_RADIX(type) \
	( std::numeric_limits<type>::radix )

#if NG_CHECK_CPLUSPLUS_COMPILER_SUPPORT(11)
	// C++11以降
	/*!
	* @brief					指定の型の表現可能な最小値を求める
	* @attention				C++11からのみ有効
	*							小数点数型の場合、実装依存となる。一般的には最大値を負にしたものとなる
	*/
	#define NG_MIN_FINITE(type) \
		( std::numeric_limits<type>::lowest() )
#else
	// C++11以前
	/*!
	* @brief					指定の型の表現可能な最小値を求める
	* @attention				小数点数型に関しては最小の正の数を返却する
	*/
	#define NG_MIN_FINITE(type) \
		( std::numeric_limits<type>::min() )
#endif

/*!
* @brief					指定の型の表現可能な最大値を求める
*/
#define NG_MAX_FINITE(type) \
	( std::numeric_limits<type>::max() )

namespace ng
{
	/*!
	* @brief					2の補数表現判定用
	* @tparam T					判定する型
	* @note						resultメンバ変数参照
	*/
	template <typename T>
	struct IsTwosComplement
	{
		static const bool result = ((T(-1) & 3) == 3);
	};

	/*!
	* @brief					1の補数表現判定用
	* @tparam T					判定する型
	* @note						resultメンバ変数参照
	*/
	template <typename T>
	struct IsOnesComplement
	{
		static const bool result = ((T(-1) & 3) == 2);
	};

	/*!
	* @brief					「符号付き＋絶対値」判定用
	* @tparam T					判定する型
	* @note						resultメンバ変数参照
	*/
	template <typename T>
	struct IsSignedMagnitude
	{
		static const bool result = ((T(-1) & 3) == 1);
	};

}	// namespace ng

#endif	// __NG_CORE_MATH_H__
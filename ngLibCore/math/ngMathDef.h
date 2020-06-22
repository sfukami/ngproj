/*!
* @file		ngMathDef.h
* @brief	算術演算定義
* @date		2015-10-18
* @author	s.fukami
*/

#ifndef __NG_CORE_MATH_DEF_H__
#define __NG_CORE_MATH_DEF_H__

#include <limits.h>
#include <float.h>	// for FLT_MAX

#define NG_PI				( 3.1415927f )		//!< π
#define NG_SQRTTRL_DEF		( 0.0f )			//!< Sqrt関数 デフォルトの許容誤差
#define NG_FLT_EPSILON		( FLT_EPSILON )		//!< float用イプシロン
#define NG_DBL_EPSILON		( DBL_EPSILON )		//!< double用イプシロン

//! float最大値
#define NG_FLOAT_MAX		( FLT_MAX )

#endif	// #ifndef __NG_CORE_MATH_DEF_H__
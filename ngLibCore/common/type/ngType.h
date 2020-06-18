/*!
* @file		ngType.h
* @brief	ライブラリ定義型
* @date 	2015-11-04
* @author 	s.fukami
*/

#ifndef __NG_CORE_TYPE_H__
#define __NG_CORE_TYPE_H__

#include <stddef.h>

namespace ng
{

typedef signed char			s8;
typedef signed short		s16;
typedef signed int			s32;
typedef signed long long	s64;

typedef unsigned char		u8;
typedef unsigned short		u16;
typedef unsigned int		u32;
typedef unsigned long long	u64;

typedef volatile s8			vs8;
typedef volatile s16		vs16;
typedef volatile s32		vs32;
typedef volatile s64		vs64;

typedef volatile u8			vu8;
typedef volatile u16		vu16;
typedef volatile u32		vu32;
typedef volatile u64		vu64;

typedef float				f32;
typedef double				f64;

typedef volatile f32		vf32;
typedef volatile f64		vf64;

typedef char				char8;
typedef wchar_t				char16;

typedef u8					byte;

typedef size_t				size_type;

}	// namespace ng

#endif	// __NG_CORE_TYPE_H__

/*!
* @file		ngEnumMacro.h
* @brief	enum用マクロ定義
* @date		2019-08-10
* @author	s.fukami
*/

#ifndef __NG_CORE_ENUM_MACRO_H__
#define __NG_CORE_ENUM_MACRO_H__

#include <type_traits>

/*!
* @brief					enum型チェック
*/
#define NG_STATIC_ASSERT_ENUM_TYPE(_T) \
	NG_STATIC_ASSERT(std::is_enum<_T>::value, "Assertion requires enum argument.")

/*!
* @brief					enum型の規定型
*/
#define NG_UNDERLYING_TYPE(_T) \
	typename std::underlying_type<_T>::type

/*!
* @brief					enum型 グローバルな比較演算子を定義
*/
#define NG_ENUM_COMPARE_OP_GLOBAL(_T, _op) \
	constexpr bool operator _op(const _T& lhs, const NG_UNDERLYING_TYPE(_T)& rhs) \
	{ \
		using _U = NG_UNDERLYING_TYPE(_T); \
		return static_cast<_U>(lhs) _op rhs; \
	} \
	constexpr bool operator _op(const NG_UNDERLYING_TYPE(_T)& lhs, const _T& rhs) \
	{ \
		using _U = NG_UNDERLYING_TYPE(_T); \
		return lhs _op static_cast<_U>(rhs); \
	}

/*!
* @brief					enum型 グローバルなビット演算子（引数2）を定義
*/
#define NG_ENUM_BIT_OP2ARGS_GLOBAL(_T, _op) \
	constexpr _T operator _op(const _T lhs, const _T rhs) \
	{ \
		using _U = NG_UNDERLYING_TYPE(_T); \
		return static_cast<_T>(static_cast<_U>(lhs) _op static_cast<_U>(rhs)); \
	} \

/*!
* @brief					enum型 グローバルなビット演算代入演算子を定義
*/
#define NG_ENUM_BITASSIGN_OP_GLOBAL(_T, _bitAssignOp, _bitOp) \
	NG_INLINE _T& operator _bitAssignOp(_T& lhs, const _T& rhs) \
	{ \
		using _U = NG_UNDERLYING_TYPE(_T); \
		return lhs = static_cast<_T>(static_cast<_U>(lhs) _bitOp static_cast<_U>(rhs)); \
	}

/*!
* @brief					指定enum型の各ビット演算を定義
*/
#define NG_ENUM_BITFLAG_OP(_T) \
	NG_STATIC_ASSERT_ENUM_TYPE(_T); \
	NG_ENUM_BIT_OP2ARGS_GLOBAL(_T, |); \
	NG_ENUM_BIT_OP2ARGS_GLOBAL(_T, &); \
	NG_ENUM_BIT_OP2ARGS_GLOBAL(_T, ^); \
	constexpr _T operator~(const _T arg) \
	{ \
		using _U = NG_UNDERLYING_TYPE(_T); \
		return static_cast<_T>(~static_cast<_U>(arg)); \
	} \
	NG_ENUM_BITASSIGN_OP_GLOBAL(_T, |=, |); \
	NG_ENUM_BITASSIGN_OP_GLOBAL(_T, &=, &); \
	NG_ENUM_BITASSIGN_OP_GLOBAL(_T, ^=, ^); \
	NG_ENUM_COMPARE_OP_GLOBAL(_T, >); \
	NG_ENUM_COMPARE_OP_GLOBAL(_T, <); \
	NG_ENUM_COMPARE_OP_GLOBAL(_T, >=); \
	NG_ENUM_COMPARE_OP_GLOBAL(_T, <=); \
	NG_ENUM_COMPARE_OP_GLOBAL(_T, ==); \
	NG_ENUM_COMPARE_OP_GLOBAL(_T, !=);

#endif	// __NG_CORE_ENUM_MACRO_H__
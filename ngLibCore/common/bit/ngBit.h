/*!
* @file		ngBit.h
* @brief	ビット演算
* @date		2015-01-07
* @author	s.fukami
*/

#ifndef __NG_CORE_BIT_H__
#define __NG_CORE_BIT_H__

#include "ngBitMacro.h"

namespace ng
{

/*!
* @brief					有効ビット数カウント 8ビット
*/
NG_DECL s32 CountSBit8(u8 n);

/*!
* @brief					有効ビット数カウント 16ビット
*/
NG_DECL s32 CountSBit16(u16 n);

/*!
* @brief					有効ビット数カウント 32ビット
*/
NG_DECL s32 CountSBit32(u32 n);

/*!
* @brief					有効ビット数カウント 64ビット
*/
NG_DECL s32 CountSBit64(u64 n);

/*!
* @brief					最大有効ビット数（MSB）算出 8ビット
* @retval -1				入力された値が0
*/
NG_DECL s32 CalcMSB8(u8 n);

/*!
* @brief					最大有効ビット数（MSB）算出 16ビット
* @retval -1				入力された値が0
*/
NG_DECL s32 CalcMSB16(u16 n);

/*!
* @brief					最大有効ビット数（MSB）算出 32ビット
* @retval -1				入力された値が0
*/
NG_DECL s32 CalcMSB32(u32 n);

/*!
* @brief					最大有効ビット数（MSB）算出 64ビット
* @retval -1				入力された値が0
*/
NG_DECL s32 CalcMSB64(u64 n);

/*!
* @brief					最小有効ビット数（LSB）算出 8ビット
* @retval -1				入力された値が0
*/
NG_DECL s32 CalcLSB8(u8 n);

/*!
* @brief					最小有効ビット数（LSB）算出 16ビット
* @retval -1				入力された値が0
*/
NG_DECL s32 CalcLSB16(u16 n);

/*!
* @brief					最小有効ビット数（LSB）算出 32ビット
* @retval -1				入力された値が0
*/
NG_DECL s32 CalcLSB32(u32 n);

/*!
* @brief					最小有効ビット数（LSB）算出 64ビット
* @retval -1				入力された値が0
*/
NG_DECL s32 CalcLSB64(u64 n);

/*!
* @brief					2進数文字列化 8ビット
*/
NG_DECL const char* ToStrBit8(u8 n);

/*!
* @brief					2進数文字列化 16ビット
*/
NG_DECL const char* ToStrBit16(u16 n);

/*!
* @brief					2進数文字列化 32ビット
*/
NG_DECL const char* ToStrBit32(u32 n);

/*!
* @brief					2進数文字列化 64ビット
*/
NG_DECL const char* ToStrBit64(u64 n);

}	// namespace ng

#endif	// __NG_CORE_BIT_H__
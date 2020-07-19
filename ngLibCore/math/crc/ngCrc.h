/*!
* @file		ngCrc.h
* @brief	CRCハッシュ
* @date		2014-02-04
* @author	s.fukami
*/

#ifndef __NG_CORE_CRC_H__
#define __NG_CORE_CRC_H__

#include <limits.h>
#include "ngCrcTbl.h"

namespace ng
{
	/*!
	* @brief					CRC32を用いて、文字列よりハッシュ値を生成する
	* @attention				文字列リテラル用
	*							引数の配列の長さ == 文字列の長さ+1 を想定
	*/
	template <size_type N>
	NG_INLINE u32 CalcCRC32Hash(const char (&str)[N])
	{
		// '\0'を考慮してN-1
		return CalcCRC32Hash_Helper(N-1, reinterpret_cast<const char (&)[N-1]>(str));
	}

	/*!
	* @brief					CalcCRC32Hash関数のヘルパ関数
	*/
	template <size_type N>
	NG_INLINE u32 CalcCRC32Hash_Helper(u32 hash, const char (&str)[N])
	{
		return CalcCRC32Hash_Helper( 
			(hash >> CHAR_BIT) ^ GetHashTable(eHASH_TABLE_CRC32)[(unsigned char)((hash & 0xff) ^ str[N-1])]
			, reinterpret_cast<const char (&)[N-1]>(str)
			);
	}

	/*!
	* @brief					CalcCRC32Hash関数のヘルパ関数
	*/
	template <>
	NG_INLINE u32 CalcCRC32Hash_Helper<1>(u32 hash, const char (&str)[1])
	{
		return (hash >> CHAR_BIT) ^ GetHashTable(eHASH_TABLE_CRC32)[(unsigned char)((hash & 0xff) ^ str[0])];
	}

	/*!
	* @brief					CRC32を用いて、文字列よりハッシュ値を生成する
	*/
	u32 CalcCRC32Hash(const char* str, u32 length);

}	// namespace ng

#endif	// __NG_CORE_CRC_H__
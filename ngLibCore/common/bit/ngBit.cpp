/*!
* @file		ngBit.cpp
* @brief	ビット演算
* @date		2015-01-07
* @author	s.fukami
*/

#include "ngBit.h"
#include "ngLibCore/common/std/ngStdMacro.h"

namespace ng
{

NG_DECL s32 CountSBit8(u8 n)
{
	u8 c = (n & 0x55) + ((n >> 1) & 0x55);
	c = (c & 0x33) + ((c >> 2) & 0x33);
	return (c & 0x0f) + ((c >> 4) & 0x0f);
}

NG_DECL s32 CountSBit16(u16 n)
{
	u16 c = (n & 0x5555) + ((n >> 1) & 0x5555);
	c = (c & 0x3333) + ((c >> 2) & 0x3333);
	c = (c & 0x0f0f) + ((c >> 4) & 0x0f0f);
	return (c & 0x00ff) + ((c >> 8) & 0x00ff);
}

NG_DECL s32 CountSBit32(u32 n)
{
	u32 c = (n & 0x55555555) + ((n >> 1) & 0x55555555);
	c = (c & 0x33333333) + ((c >> 2) & 0x33333333);
	c = (c & 0x0f0f0f0f) + ((c >> 4) & 0x0f0f0f0f);
	c = (c & 0x00ff00ff) + ((c >> 8) & 0x00ff00ff);
	return (c & 0x0000ffff) + ((c >> 16) & 0x0000ffff);
}

NG_DECL s32 CountSBit64(u64 n)
{
	u64 c = (n & 0x5555555555555555) + ((n >> 1) & 0x5555555555555555);
	c = (c & 0x3333333333333333) + ((c >> 2) & 0x3333333333333333);
	c = (c & 0x0f0f0f0f0f0f0f0f) + ((c >> 4) & 0x0f0f0f0f0f0f0f0f);
	c = (c & 0x00ff00ff00ff00ff) + ((c >> 8) & 0x00ff00ff00ff00ff);
	c = (c & 0x0000ffff0000ffff) + ((c >> 16) & 0x0000ffff0000ffff);
	return (s32)((c & 0x00000000ffffffff) + ((c >> 32) & 0x00000000ffffffff));
}

NG_DECL s32 CalcMSB8(u8 n)
{
	if (n == 0)
	{
		return -1;
	}
	n |= (n >> 1);
	n |= (n >> 2);
	n |= (n >> 4);
	return (CountSBit8(n) - 1);
}

NG_DECL s32 CalcMSB16(u16 n)
{
	if (n == 0)
	{
		return -1;
	}
	n |= (n >> 1);
	n |= (n >> 2);
	n |= (n >> 4);
	n |= (n >> 8);
	return (CountSBit16(n) - 1);
}

NG_DECL s32 CalcMSB32(u32 n)
{
	if (n == 0)
	{
		return -1;
	}
	n |= (n >> 1);
	n |= (n >> 2);
	n |= (n >> 4);
	n |= (n >> 8);
	n |= (n >> 16);
	return (CountSBit32(n) - 1);
}

NG_DECL s32 CalcMSB64(u64 n)
{
	if (n == 0)
	{
		return -1;
	}
	n |= (n >> 1);
	n |= (n >> 2);
	n |= (n >> 4);
	n |= (n >> 8);
	n |= (n >> 16);
	n |= (n >> 32);
	return (CountSBit64(n) - 1);
}

NG_DECL s32 CalcLSB8(u8 n)
{
	if (n == 0)
	{
		return -1;
	}
	return CountSBit8((n & -(s8)n)-1);
}

NG_DECL s32 CalcLSB16(u16 n)
{
	if (n == 0)
	{
		return -1;
	}
	return CountSBit16((n & -(s16)n)-1);
}

NG_DECL s32 CalcLSB32(u32 n)
{
	if (n == 0)
	{
		return -1;
	}
	return CountSBit32((n & -(s32)n)-1);
}

NG_DECL s32 CalcLSB64(u64 n)
{
	if (n == 0)
	{
		return -1;
	}
	return CountSBit64((n & -(s64)n)-1);
}

template <typename T>
static inline const char* _toStrBitHelper(T& n)
{
	static const size_type SIZE = NG_SIZEOF(T)*8;
	static char str[ SIZE+1 ] = {'\0'};
	for(int i = 0; i < SIZE; i++)
	{
		str[(SIZE-1)-i] = (1 & (n >> i)) ? '1' : '0';
	}
	return str;
}

NG_DECL const char* ToStrBit8(u8 n)
{
	return _toStrBitHelper(n);
}

NG_DECL const char* ToStrBit16(u16 n)
{
	return _toStrBitHelper(n);
}

NG_DECL const char* ToStrBit32(u32 n)
{
	return _toStrBitHelper(n);
}

NG_DECL const char* ToStrBit64(u64 n)
{
	return _toStrBitHelper(n);
}

}	// namespace ng
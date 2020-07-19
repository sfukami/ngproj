/*!
* @file		ngCrc.cpp
* @brief	CRCハッシュ
* @date		2014-02-04
* @author	s.fukami
*/

#include "ngCrc.h"
#include "ngCrcTbl.h"

namespace ng
{
	u32 CalcCRC32Hash(const char* str, u32 length)
	{
		u32 hash = length;
		for(s32 i=length-1; i>=0; i--)
		{
			hash = (hash >> CHAR_BIT) ^ g_crc32tbl[(unsigned char)((hash & 0xff) ^ str[i])];
		}

		return hash;
	}

}	// namespace ng
/*!
* @file		ngMemDump.cpp
* @brief	メモリダンプ
* @date		2018-03-05
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "ngMemDump.h"

#define BUF_SIZE	(128U)		//!< BUF_SIZE > 行長さ
#define WIDTH		(16U)

/*
	0x00 - 0x1f		制御記号
	0x20			空白
	0x21 - 0x7e		図形文字
	0x7f			制御記号（DEL）
*/
#define ASCII_FLTR_L	(0x20)		//!< 無効文字ASCIIコード左端
#define ASCII_FLTR_H	(0x7e)		//!< 無効文字ASCIIコード右端

namespace ng
{
	NG_DECL void MemoryDump(const void* pMemory, size_type size)
	{
		const unsigned char* p = PointerCast<const unsigned char*>(pMemory);
		char buf[BUF_SIZE + 1] = "\0";
		char ascii[WIDTH + 1] = "\0";

		const char* pHeader	= "ADDRESS  | 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F | 0123456789ABCDEF\n";
		const char* pRuler	= "---------+-------------------------------------------------+-----------------\n";
		const size_type rowLen = NG_STRLEN(pHeader);

		Printf(pHeader);
		Printf(pRuler);

		char* pB = buf;
		for(unsigned int i = 0; i < size; i += WIDTH)
		{
			pB += NG_SPRINTF(pB, "%08p | ", p);

			size_type w = (size-i >= WIDTH) ? WIDTH : size-i;
			char* pA = ascii;
			size_type j = 0;
			for(; j < w; j++, pA++, p++)
			{
				pB += NG_SPRINTF(pB, "%02X ", *p);
				*pA = (*p < ASCII_FLTR_L || *p > ASCII_FLTR_H) ? '.' : *p;
			}
			for(; j < WIDTH; j++, pB+=3, pA++)
			{
				NG_STRCAT(pB, "   ");
				*pA = ' ';
			}

			*pA = '\0';
			pB += NG_SPRINTF(pB, "| %s\n", ascii);
			
			if(BUF_SIZE - (u32)(pB - buf) < rowLen) {
				Printf(buf);
				pB = buf;
			}
		}

		if(pB != buf) {
			Printf(buf);
		}
	}
}

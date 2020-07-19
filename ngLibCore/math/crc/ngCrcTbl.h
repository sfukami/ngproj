/*!
* @file		ngCrcTbl.h
* @brief	CRCテーブル
* @date		2014-02-04
* @author	s.fukami
*/

#ifndef __NG_CORE_CRC_TBL_H__
#define __NG_CORE_CRC_TBL_H__

namespace ng
{

	extern const unsigned int g_crc32tbl[256];
	extern const unsigned int g_crc16_CCITT_tbl[256];
	extern const unsigned int g_crc16_ANSI_tbl[256];
	extern const unsigned int g_crc7tbl[256];

	/*! ハッシュテーブル */
	enum eHashTable
	{
		eHASH_TABLE_CRC32,			//!< CRC-32 ハッシュテーブル
		eHASH_TABLE_CRC16_CCITT,	//!< CRC-16(CRC-CCITT) ハッシュテーブル
		eHASH_TABLE_CRC16_ANSI,		//!< CRC-16(CRC-ANSI) ハッシュテーブル
		eHASH_TABLE_CRC7,			//!< CRC-7 ハッシュテーブル
		////////////////////////////////
		eHASH_TABLE_NUM
	};

	/*!
	* @brief					ハッシュテーブル取得
	*/
	NG_DECL const unsigned int* GetHashTable(eHashTable table);

}	// namespace ng

#endif	// __NG_CORE_CRC_TBL_H__
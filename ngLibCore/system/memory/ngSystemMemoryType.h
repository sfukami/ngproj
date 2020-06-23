/*!
* @file		ngSystemMemoryType.h
* @brief	NGライブラリ システムメモリタイプ
* @date		2018-02-19
* @author	s.fukami
*/

#ifndef __NG_CORE_SYSTEM_MEMORY_TYPE_H__
#define __NG_CORE_SYSTEM_MEMORY_TYPE_H__

namespace ng
{
	/*!
	* @brief					NGライブラリ システムメモリタイプ
	*/
	enum class eSystemMemoryType : u32
	{
		MAINSYS,	//!< メインシステム
		GRAPHIC,	//!< グラフィック

		NUM,
	};

}	// namespace ng

#endif	// __NG_CORE_SYSTEM_MEMORY_TYPE_H__
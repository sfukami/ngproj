/*!
* @file		ngMemDump.h
* @brief	メモリダンプ
* @date		2018-03-05
* @author	s.fukami
*/

#ifndef __NG_CORE_MEM_DUMP_H__
#define __NG_CORE_MEM_DUMP_H__

namespace ng
{
	/*!
	* @brief					メモリダンプ
	* @param pMemory			対象のメモリ領域へのポインタ
	* @param size				対象のメモリ領域のサイズ
	*/
	NG_DECL void MemoryDump(const void* pMemory, size_type size);

}	// namespace ng

#endif	// __NG_CORE_MEM_DUMP_H__
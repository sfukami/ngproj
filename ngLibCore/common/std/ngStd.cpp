/*!
* @file		ngStd.cpp
* @brief	標準的な機能
* @date		2016-08-22
* @author	s.fukami
*/

#include "ngStd.h"

namespace ng
{

/*!
* @brief					ポインタの差（バイト数）を取得
* @param left				左項
* @param right				右項
* @return					ポインタの差（バイト数）
*/
NG_DECL void* PointerDiff(const void* left, const void* right)
{
	return reinterpret_cast<void*>(static_cast<char*>(const_cast<void*>(left)) - static_cast<char*>(const_cast<void*>(right)));
}

}	// namespace ng

/*!
* @file		ngStd.h
* @brief	標準的な機能
* @date		2016-08-22
* @author	s.fukami
*/

#ifndef __NG_CORE_STD_H__
#define __NG_CORE_STD_H__

#include <type_traits>
#include "ngStdMacro.h"

namespace ng
{

/*!
* @brief					ポインタのキャスト
* @note						static_cast<T>( static_cast<void*>(p) ) と同義
*/
template <typename T>
NG_INLINE T PointerCast(void* p)
{
	return static_cast<T>(p);
}
template <typename T>
NG_INLINE T PointerCast(const void* p)
{
	return static_cast<T>(p);
}

/*!
* @brief					ポインタのオフセット
* @tparam T					戻り値の型
* @tparam OFFSET			オフセットの型
* @param p					オフセットするポインタ
* @param offset				オフセットするバイト数
* @return					オフセット後のポインタ
*/
template <typename T, typename OFFSET>
NG_INLINE T PointerOffset(const void* p, OFFSET offset)
{
	return reinterpret_cast<T>(static_cast<char*>(const_cast<void*>(p)) + offset);
}

/*!
* @brief					ポインタの差（バイト数）を取得
* @param left				左項
* @param right				右項
* @return					ポインタの差（バイト数）
*/
NG_DECL intptr_t PointerDiff(const void* left, const void* right);

/*!
* @brief					指定の値でアライメントする
* @param value				対象の値
* @param alignment			アライメント
*/
template <typename T>
NG_INLINE T Align(T value, size_t alignment)
{
	return (T)(NG_ALIGN(value, alignment));
}

/*!
* @brief					Enum値をその基底型でキャストする
* @param enumVal			Enum値
*/
template <typename T>
NG_INLINE typename std::underlying_type<T>::type UnderlyingCast(T enumVal)
{
	static_assert(std::is_enum<T>::value, "Assertion requires enum argument.");
	return static_cast<typename std::underlying_type<T>::type>(enumVal);
}

}	// namespace ng

#endif	// __NG_CORE_STD_H__

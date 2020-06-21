/*!
* @file		ngFixedList.h
* @brief	固定長リスト 基底クラス
* @date		2017-12-02
* @author	s.fukami
*/

#ifndef __NG_CORE_FIXED_LIST_BASE_H__
#define __NG_CORE_FIXED_LIST_BASE_H__

#include "../ngListLinkedType.h"

namespace ng
{
	/*!
	* @brief					固定長リスト ベースクラス
	* @tparam T					格納する要素の型
	* @tparam LinkedType		リンクタイプ(BidirectionalLinked もしくは ForwardLinked)
	*/
	template <typename T, typename LinkedType = BidirectionalLinked>
	class NG_DECL CFixedListBase
	{
		// 使用禁止
		NG_STATIC_ASSERT(
			NG_SIZEOF(T)<0
			, "CFixedListBase template parameter \"LinkedType\" is invalid."
			);
	};

	/*!
	* @brief					固定長リスト
	* @tparam T					格納する要素の型
	* @tparam SIZE				格納する要素数。NG_UNSPECIFIED_SIZE で初期化時に要素数を指定する
	* @tparam LinkedType		リンクタイプ(BidirectionalLinked もしくは ForwardLinked)
	* @note						宣言時、もしくは初期化時にバッファを指定する固定長のコンテナ
	*/
	template <typename T, typename LinkedType = BidirectionalLinked, u32 SIZE = NG_UNSPECIFIED_SIZE>
	class NG_DECL CFixedList : public CFixedListBase<T, LinkedType>
	{
		// 使用不可
	};

}	// namespace ng

#endif	// __NG_CORE_FIXED_LIST_BASE_H__
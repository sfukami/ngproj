/*!
* @file		ngFixedList.h
* @brief	固定長リスト 基底クラス
* @date		2017-12-02
* @author	s.fukami
*/

#ifndef __NG_CORE_FIXED_LIST_BASE_H__
#define __NG_CORE_FIXED_LIST_BASE_H__

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

}	// namespace ng

#endif	// __NG_CORE_FIXED_LIST_BASE_H__
/*!
* @file		ngStdMacro.h
* @brief	汎用的なマクロ定義
* @date		2016-08-22
* @author	s.fukami
*/

#ifndef __NG_CORE_STD_MACRO_H__
#define __NG_CORE_STD_MACRO_H__

/*!
* @brief					変数のサイズ取得
*/
#define NG_SIZEOF(_v)		(sizeof(_v))

/*!
* @brief					文字列化マクロ
*/
#define NG_TO_STRING(_x)	NG_TO_STRING2(_x)
#define NG_TO_STRING2(_x)	#_x

/*!
* @brief					結合マクロ
*/
#define NG_JOIN(_x, _y)		NG_JOIN2(_x, _y)
#define NG_JOIN2(_x, _y)	_x##_y

/*!
* @brief					ソースファイル名 + 行数
*/
#define NG_FILE_LINE	(__FILE__"(" NG_TO_STRING(__LINE__) ")")

/*!
* @brief					関数名
*/
#define NG_FUNCTION		(__FUNCTION__)

/*!
* @brief					配列の要素数を取得
*/
#if NG_CHECK_CPLUSPLUS_COMPILER_SUPPORT(11)
	#define NG_ARRAY_SIZE(_a)		( ng::ArraySize(_a) )
#else
	#define NG_ARRAY_SIZE(_a)		( sizeof(_a) / sizeof(_a[0]) )
#endif

/*!
* ポインタサイズ
*/
#define NG_PTR_SIZE		(NG_SIZEOF(size_type))

/*!
* @brief					ポインタ比較
*/
#define NG_PTRCMP(_lhs, _op, _rhs)	(static_cast<const void*>(_lhs) _op static_cast<const void*>(_rhs))

/*!
* @brief					バイト変換
*/
#define NG_KB(_byte)	((_byte) * 1024)
#define NG_MB(_byte)	(NG_KB(_byte) * 1024)

/*!
* @brief					アドレスのアライメントを取得する
* @param _address			アドレス
*/
#define NG_ALIGNMENT_OF(_address) \
	( (~(ng::size_type)(_address) + 1U) & (ng::size_type)(_address) )

/*!
* @brief					指定の値でアライメントする
* @param _value				対象の値
* @param _alignment			アライメント
*/
#define NG_ALIGN(_value, _alignment) \
	( ((ng::size_type)(_value) + ((_alignment) - 1)) & ~(ng::size_type)((_alignment) - 1) )
	

namespace ng
{
#if NG_CHECK_CPLUSPLUS_COMPILER_SUPPORT(11)
	/*!
	* @brief					配列のサイズを取得
	* @note						C++11以降で有効
	*							constexprが使用できない場合は定義不可
	*/
	template <typename T, int N>
	NG_INLINE constexpr int ArraySize(T (&a)[N])
	{
		return N;
	}
#endif

}	// namespace ng

#endif	// __NG_CORE_STD_MACRO_H__

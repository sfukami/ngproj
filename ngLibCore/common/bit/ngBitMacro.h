/*!
* @file		ngBitMacro.h
* @brief	ビット演算マクロ定義
* @date		2015-06-13
* @author	s.fukami
*/

#ifndef __NG_CORE_BIT_MACRO_H__
#define __NG_CORE_BIT_MACRO_H__

/*!
* ビットフラグ
*/
#define NG_BIT_1		(NG_BIT(0))
#define NG_BIT_2		(NG_BIT(1))
#define NG_BIT_4		(NG_BIT(2))
#define NG_BIT_8		(NG_BIT(3))
#define NG_BIT_16		(NG_BIT(4))
#define NG_BIT_32		(NG_BIT(5))
#define NG_BIT_64		(NG_BIT(6))
#define NG_BIT_128		(NG_BIT(7))

/*!
* ビットマスク
*/
#define NG_BIT_MASK8	((u8)-1)
#define NG_BIT_MASK16	((u16)-1)
#define NG_BIT_MASK32	((u32)-1)
#define NG_BIT_MASK64	((u64)-1)

/*!
* @brief					指定のビットを1にする
*/
#define NG_BIT(_n)					(1<<(_n))

/*!
* @brief					指定のビットの値を取得
*/
#define NG_BIT_CHECK(_v, _pos)		(((_v)>>(_pos))&1)

/*!
* @brief					指定のビットの値を1に設定
*/
#define NG_BIT_SET(_v, _pos)		((_v)|=(1<<(_pos)))

/*!
* @brief					指定のビットの値を0に設定
*/
#define NG_BIT_UNSET(_v, _pos)		((_v)&=(~(1<<_pos)))

#endif	// __NG_CORE_BIT_MACRO_H__
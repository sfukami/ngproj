/*!
* @file		ngColorUtil.h
* @brief	色情報ユーティリティ
* @date		2019-08-15
* @author	s.fukami
*/

#ifndef __NG_CORE_COLOR_UTIL_H__
#define __NG_CORE_COLOR_UTIL_H__

namespace ng
{
	enum class eColorCode : u32;
	struct Color;
}

namespace ng
{
	namespace ColorUtil
	{
		/*!
		* @brief					色コード（16進数）を RGBに変換
		* @param pR					R成分の格納先
		* @param pG					G成分の格納先
		* @param pB					B成分の格納先
		*/
		NG_DECL void ToColor(eColorCode code, u8* pR, u8* pG, u8* pB);
		NG_DECL void ToColor(eColorCode code, u32* pR, u32* pG, u32* pB);
		NG_DECL void ToColor(eColorCode code, f32* pR, f32* pG, f32* pB);

		/*!
		* @brief					色コード（16進数）を Color構造体に変換
		*/
		NG_DECL void ToColor(eColorCode code, Color* pColor);
	}

}	// namespace ng

#endif	// __NG_CORE_COLOR_UTIL_H__
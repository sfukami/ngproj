/*!
* @file		ngColorUtil.cpp
* @brief	色情報ユーティリティ
* @date		2019-08-15
* @author	s.fukami
*/

#include "ngLibCore/common/std/ngStd.h"
#include "ngLibCore/math/ngMath.h"
#include "ngColorUtil.h"
#include "ngColorCode.h"
#include "ngColor.h"

namespace ng
{
	namespace ColorUtil
	{
		NG_DECL void ToColor(eColorCode code, u8* pR, u8* pG, u8* pB)
		{
			u32 val = UnderlyingCast(code);

			if(pR) *pR = (val >> 16) & 0xFF;
			if(pG) *pG = (val >> 8) & 0xFF;
			if(pB) *pB = val & 0xFF;
		}
		NG_DECL void ToColor(eColorCode code, u32* pR, u32* pG, u32* pB)
		{
			u8 r,g,b;
			ToColor(code, &r, &g, &b);

			if(pR) *pR = r;
			if(pG) *pG = g;
			if(pB) *pB = b;
		}
		NG_DECL void ToColor(eColorCode code, f32* pR, f32* pG, f32* pB)
		{
			u32 r,g,b;
			ToColor(code, &r, &g, &b);
			
			if(pR) *pR = Normalize(r, 0U, 255U);
			if(pG) *pG = Normalize(g, 0U, 255U);
			if(pB) *pB = Normalize(b, 0U, 255U);
		}
		
		NG_DECL void ToColor(eColorCode code, Color* pColor)
		{
			*pColor = Color(code);
		}

	}	// namespace ColorUtil
}	// namespace ng
/*!
* @file		ngColor.cpp
* @brief	色情報
* @date		2019-08-15
* @author	s.fukami
*/

#include "ngColor.h"
#include "ngColorUtil.h"
#include "../geometry/vector/ngVector3.h"
#include "../geometry/vector/ngVector4.h"

namespace ng
{
	Color::Color(eColorCode code)
		: a(1.f)
	{
		ColorUtil::ToColor(code, &r, &g, &b);
	}

	Color::Color(const Vector4& v)
	{
		r = v.r;
		g = v.g;
		b = v.b;
		a = v.a;
	}

	Color::Color(const Vector3& v)
	{
		r = v.r;
		g = v.g;
		b = v.b;
	}

}	// namespace ng
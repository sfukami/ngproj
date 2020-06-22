/*!
* @file		ngVector2.cpp
* @brief	2次元ベクトル
* @date		2013-10-18
* @author	s.fukami
*/

#include "ngVector2.h"
#include "ngLibCore/common/memory/ngMemMacro.h"

namespace ng
{
	const s32 Vector2::ROW = 1;
	const s32 Vector2::COL = 2;
	const Vector2 Vector2::ZERO = {0.0f, 0.0f};
	const Vector2 Vector2::ONE = {1.0f, 1.0f};
	const Vector2 Vector2::AXIS_X = {1.0f, 0.0f};
	const Vector2 Vector2::AXIS_Y = {0.0f, 1.0f};

	Vector2::Vector2(const f32 pElems[])
	{
		NG_MEMCPY(m, pElems, sizeof(m));
	}

}	// namespace ng
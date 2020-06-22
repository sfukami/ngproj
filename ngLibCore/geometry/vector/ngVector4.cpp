/*!
* @file		ngVector4.cpp
* @brief	4次元ベクトル
* @date		2013-10-18
* @author	s.fukami
*/

#include "ngVector4.h"
#include "ngLibCore/common/memory/ngMemMacro.h"

namespace ng
{
	const s32 Vector4::ROW = 1;
	const s32 Vector4::COL = 4;
	const Vector4 Vector4::ZERO = {0.0f, 0.0f, 0.0f, 0.0f};
	const Vector4 Vector4::ONE = {1.0f, 1.0f, 1.0f, 1.0f};
	const Vector4 Vector4::X_AXIS = {1.0f, 0.0f, 0.0f, 0.0f};
	const Vector4 Vector4::Y_AXIS = {0.0f, 1.0f, 0.0f, 0.0f};
	const Vector4 Vector4::Z_AXIS = {0.0f, 0.0f, 1.0f, 0.0f};
	const Vector4 Vector4::W_AXIS = {0.0f, 0.0f, 0.0f, 1.0f};

	Vector4::Vector4(const f32 pElems[])
	{
		NG_MEMCPY(m, pElems, sizeof(m));
	}

}	// namespace ng
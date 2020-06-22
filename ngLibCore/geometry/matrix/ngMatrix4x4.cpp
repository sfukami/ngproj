/*!
* @file		ngMatrix4x4.cpp
* @brief	4x4行列
* @date		2015-10-18
* @author	s.fukami
*/

#include "ngMatrix4x4.h"
#include "ngLibCore/common/memory/ngMemMacro.h"

namespace ng
{
	const s32 Matrix4x4::ROW = 4;
	const s32 Matrix4x4::COL = 4;
	const Matrix4 Matrix4::ZERO = Matrix4();
	const Matrix4 Matrix4::IDENTITY = Matrix4(
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f
		);

	Matrix4x4::Matrix4x4(const f32 pElems[])
	{
		NG_MEMCPY(m, pElems, sizeof(m));
	}

}	// namespace ng

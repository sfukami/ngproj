/*!
* @file		ngMatrix3x3.cpp
* @brief	3x3行列
* @date		2015-10-18
* @author	s.fukami
*/

#include "ngMatrix3x3.h"
#include "ngLibCore/common/memory/ngMemMacro.h"

namespace ng
{
	const s32 Matrix3::ROW = 3;
	const s32 Matrix3::COL = 3;
	const Matrix3 Matrix3::ZERO = Matrix3();
	const Matrix3 Matrix3::IDENTITY = Matrix3(
		1.f, 0.f, 0.f,
		0.f, 1.f, 0.f,
		0.f, 0.f, 1.f
		);

	Matrix3x3::Matrix3x3(const f32 pElems[])
	{
		NG_MEMCPY(m, pElems, sizeof(m));
	}

}	// namespace ng

/*!
* @file		ngVector3.cpp
* @brief	3次元ベクトル
* @date		2013-10-18
* @author	s.fukami
*/

#include "ngVector3.h"
#include "ngLibCore/common/memory/ngMemMacro.h"

namespace ng
{
	const s32 Vector3::ROW = 1;
	const s32 Vector3::COL = 3;
	const Vector3 Vector3::ZERO = {0.0f, 0.0f, 0.0f};
	const Vector3 Vector3::ONE = {1.0f, 1.0f, 1.0f};
	const Vector3 Vector3::AXIS_X = {1.0f, 0.0f, 0.0f};
	const Vector3 Vector3::AXIS_Y = {0.0f, 1.0f, 0.0f};
	const Vector3 Vector3::AXIS_Z = {0.0f, 0.0f, 1.0f};

	Vector3::Vector3(const f32 pElems[])
	{
		NG_MEMCPY(m, pElems, sizeof(m));
	}
	
}	// namespace ng
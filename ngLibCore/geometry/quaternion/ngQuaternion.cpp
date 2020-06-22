/*!
* @file		ngQuaternion.cpp
* @brief	クォータニオン
* @date		2015-10-18
* @author	s.fukami
*/

#include "ngQuaternion.h"
#include "ngLibCore/common/memory/ngMemMacro.h"

namespace ng
{
	const Quaternion Quaternion::IDENTITY = Quaternion(0,0,0,1);

	Quaternion::Quaternion(const f32 pElems[])
	{
		NG_MEMCPY(m, pElems, sizeof(m));
	}

}	// namespace ng

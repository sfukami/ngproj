/*!
* @file		appTransformObject.cpp
* @brief	トランスフォームオブジェクト
* @date		2020-08-28
* @author	s.fukami
*/

#include "appTransformObject.h"

namespace app
{
	CTransformObject::CTransformObject()
	{
	}
	CTransformObject::~CTransformObject()
	{
	}

	CTransform& CTransformObject::GetTransform()
	{
		return m_transform;
	}
	const CTransform& CTransformObject::GetTransform() const
	{
		return m_transform;
	}

}	// namespace app
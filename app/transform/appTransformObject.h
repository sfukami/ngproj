/*!
* @file		appTransformObject.h
* @brief	トランスフォームオブジェクト
* @date		2020-08-28
* @author	s.fukami
*/

#ifndef __APP_TRANSFORM_OBJECT_H__
#define __APP_TRANSFORM_OBJECT_H__

#include "appTransform.h"

namespace app
{
	/*!
	* @brief					トランスフォームオブジェクト
	*/
	class CTransformObject
	{
	public:
		CTransformObject();
		virtual ~CTransformObject();

		/*! トランスフォーム取得 */
		CTransform& GetTransform();
		const CTransform& GetTransform() const;
		
	private:
		CTransform m_transform;	//!< トランスフォーム
	};

}	// namespace app

#endif	// __APP_TRANSFORM_OBJECT_H__
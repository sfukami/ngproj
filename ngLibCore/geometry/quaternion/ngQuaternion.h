/*!
* @file		ngQuaternion.h
* @brief	クォータニオン
* @date		2015-10-18
* @author	s.fukami
*/

#ifndef __NG_CORE_QUATERNION_H__
#define __NG_CORE_QUATERNION_H__

namespace ng
{
	/*!
	* @brief					クォータニオン
	*/
	struct NG_DECL Quaternion
	{
		static const Quaternion IDENTITY;	//!< 単位クォータニオン
		
		union
		{
			struct
			{
				f32 w, x, y, z;
			};
			f32 m[4];
		};

		Quaternion(f32 _x = .0f, f32 _y = .0f, f32 _z = .0f, f32 _w = .0f) 
			: x(_x), y(_y), z(_z), w(_w) { }
		explicit Quaternion(const f32 pElems[]);
	};
	
}	// namespace ng

#endif	// __NG_CORE_QUATERNION_H__

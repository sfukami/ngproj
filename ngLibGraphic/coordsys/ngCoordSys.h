/*!
* @file		ngCoordSys.h
* @brief	座標系
* @date		2019-08-07
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_COORDSYS_H__
#define __NG_GRAPHIC_COORDSYS_H__

namespace ng
{
	/*!
	* @brief					座標系
	*/
	enum class eCoordSys : u32
	{
		LEFT_HAND,		//!< 左手座標系
		RIGHT_HAND,		//!< 右手座標系
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_COORDSYS_H__
/*!
* @file		ngDX12DeviceDriverType.h
* @brief	DX12デバイス ドライバータイプ
* @date		2017-09-12
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_DEVICE_DRIVER_TYPE_H__
#define __NG_GRAPHIC_DX12_DEVICE_DRIVER_TYPE_H__

namespace ng
{
	/*!
	* DX12 ドライバーの種類
	*/
	enum class eDX12DriverType : u32
	{
		UNKNOWN = 0,		//!< 不明
		HARDWARE = 1,		//!< ソフトウェアドライバー
		SOFTWARE = 2,		//!< ハードウェアドライバー
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_DEVICE_DRIVER_TYPE_H__
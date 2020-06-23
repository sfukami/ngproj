/*!
* @file		ngDXError.cpp
* @brief	DirectX 関数戻り値 エラーコード
* @date		2017-09-11
* @author	s.fukami
*/

#include <Winerror.h>
#include "ngLibCore/common/ngCommon.h"
#include "ngDXError.h"

/*
	DXGI_ERROR
	https://msdn.microsoft.com/en-us/library/windows/desktop/bb509553(v=vs.85).aspx
*/

namespace ng
{
	// DX エラーコード 詳細
	struct Detail
	{
		HRESULT code;
		const char* str;
		const char* desc;
	};

	// DX エラーコード 詳細定義
	#define MAKE_DETAIL(_code, _desc) \
		_code, #_code, _desc

	// DX エラーコード -> 詳細変換テーブル
	static const Detail g_errCodeDetailTable[] = {
		MAKE_DETAIL(DXGI_ERROR_DEVICE_HUNG, "The application's device failed due to badly formed commands sent by the application. This is an design-time issue that should be investigated and fixed."),
		MAKE_DETAIL(DXGI_ERROR_DEVICE_RESET, "The device failed due to a badly formed command. This is a run-time issue; The application should destroy and recreate the device."),
		MAKE_DETAIL(DXGI_ERROR_DRIVER_INTERNAL_ERROR, "The driver encountered a problem and was put into the device removed state."),
		MAKE_DETAIL(DXGI_ERROR_FRAME_STATISTICS_DISJOINT, "An event (for example, a power cycle) interrupted the gathering of presentation statistics."),
		MAKE_DETAIL(DXGI_ERROR_GRAPHICS_VIDPN_SOURCE_IN_USE, "The application attempted to acquire exclusive ownership of an output, but failed because some other application (or device within the application) already acquired ownership."),
		MAKE_DETAIL(DXGI_ERROR_INVALID_CALL, "The application provided invalid parameter data; this must be debugged and fixed before the application is released."),
		MAKE_DETAIL(DXGI_ERROR_MORE_DATA, "The buffer supplied by the application is not big enough to hold the requested data."),
		MAKE_DETAIL(DXGI_ERROR_NONEXCLUSIVE, "A global counter resource is in use, and the Direct3D device can't currently use the counter resource."),
		MAKE_DETAIL(DXGI_ERROR_NOT_CURRENTLY_AVAILABLE, "The resource or request is not currently available, but it might become available later."),
		MAKE_DETAIL(DXGI_ERROR_NOT_FOUND, "When calling IDXGIObject::GetPrivateData, the GUID passed in is not recognized as one previously passed to IDXGIObject::SetPrivateData or IDXGIObject::SetPrivateDataInterface. When calling IDXGIFactory::EnumAdapters or IDXGIAdapter::EnumOutputs, the enumerated ordinal is out of range."),
		MAKE_DETAIL(DXGI_ERROR_REMOTE_CLIENT_DISCONNECTED, "Reserved"),
		MAKE_DETAIL(DXGI_ERROR_REMOTE_OUTOFMEMORY, "Reserved"),
		MAKE_DETAIL(DXGI_ERROR_WAS_STILL_DRAWING, "The GPU was busy at the moment when a call was made to perform an operation, and did not execute or schedule the operation."),
		MAKE_DETAIL(DXGI_ERROR_UNSUPPORTED, "The requested functionality is not supported by the device or the driver."),
		MAKE_DETAIL(DXGI_ERROR_ACCESS_LOST, "The desktop duplication interface is invalid. The desktop duplication interface typically becomes invalid when a different type of image is displayed on the desktop."),
		MAKE_DETAIL(DXGI_ERROR_WAIT_TIMEOUT, "The time-out interval elapsed before the next desktop frame was available."),
		MAKE_DETAIL(DXGI_ERROR_SESSION_DISCONNECTED, "The Remote Desktop Services session is currently disconnected."),
		MAKE_DETAIL(DXGI_ERROR_RESTRICT_TO_OUTPUT_STALE, "The DXGI output (monitor) to which the swap chain content was restricted is now disconnected or changed."),
		MAKE_DETAIL(DXGI_ERROR_CANNOT_PROTECT_CONTENT, "DXGI can't provide content protection on the swap chain. This error is typically caused by an older driver, or when you use a swap chain that is incompatible with content protection."),
		MAKE_DETAIL(DXGI_ERROR_ACCESS_DENIED, "You tried to use a resource to which you did not have the required access privileges. This error is most typically caused when you write to a shared resource with read-only access."),
		MAKE_DETAIL(DXGI_ERROR_NAME_ALREADY_EXISTS, "The supplied name of a resource in a call to IDXGIResource1::CreateSharedHandle is already associated with some other resource."),
		MAKE_DETAIL(DXGI_ERROR_SDK_COMPONENT_MISSING, "The operation depends on an SDK component that is missing or mismatched."),
	};

	static const Detail* GetDetail(HRESULT code);

	NG_DECL const char* DXErrorCodeToString(HRESULT hr)
	{
		const char* str = nullptr;

		str = ErrorCodeToString(hr);

		if(str == nullptr) {
			const Detail* pDetail = GetDetail(hr);
			if(pDetail != nullptr) {
				str = pDetail->str;
			}
		}

		return str;
	}

	NG_DECL const char* DXErrorCodeToDescription(HRESULT hr)
	{
		const char* str = nullptr;

		str = ErrorCodeToDescription(hr);

		if(str == nullptr) {
			const Detail* pDetail = GetDetail(hr);
			if(pDetail != nullptr) {
				str = pDetail->desc;
			}
		}

		return str;
	}

	/*!
	* @brief					DX エラーコード 詳細取得
	* @param code				エラーコード
	*/
	const Detail* GetDetail(NG_ERRCODE code)
	{
		for(int i = 0; i < NG_ARRAY_SIZE(g_errCodeDetailTable); i++)
		{
			const Detail& pair = g_errCodeDetailTable[i];
			if(pair.code == code) {
				return &pair;
			}
		}

		return nullptr;
	}

}	// namespace ng
/*!
* @file		ngDX12Std.cpp
* @brief	DX12 標準機能
* @date		2017-09-12
* @author	s.fukami
*/

#include <D3DCommon.h>
#include "ngDX12Common.h"
#include "ngDX12Std.h"

namespace ng
{
	// サポート可能なDX12機能レベル
	static const D3D_FEATURE_LEVEL s_supportedDX12FeatureLevels[] = {
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_NONE,
	};

	NG_DECL const D3D_FEATURE_LEVEL* GetSupportedDX12FeatureLevels()
	{
		return s_supportedDX12FeatureLevels;
	}

}	// namespace ng
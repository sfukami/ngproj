/*!
* @file		ngDXDebug.cpp
* @brief	DirectXデバッグ
* @date		2017-08-23
* @author	s.fukami
*/

#include "ngDXDebug.h"

#include <d3d12.h>
#include "ngLibCore/common/ngCommon.h"
#include "ngDXMacro.h"

namespace ng
{
	NG_DECL void EnableDX12DebugLayer()
	{
		ID3D12Debug* pIDebug = nullptr;

		if(NG_SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&pIDebug)))) {
			pIDebug->EnableDebugLayer();
			NG_SAFE_RELEASE(pIDebug);
		}
	}

}	// namespace ng
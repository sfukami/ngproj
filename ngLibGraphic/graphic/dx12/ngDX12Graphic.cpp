/*!
* @file		ngDX12Graphic.cpp
* @brief	DX12グラフィックス
* @date		2017-08-23
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "ngLibGraphic/graphic/dx12/common/ngDX12Common.h"
#include "ngDX12Graphic.h"

namespace ng
{
	CDX12Graphic::CreateParam::CreateParam()
		: hWnd(nullptr)
		, clientWidth(0)
		, clientHeight(0)
		, isFullscreen(false)
	{
	}

	CDX12Graphic::CDX12Graphic()
	{
	}

	CDX12Graphic::~CDX12Graphic()
	{
		Destroy();
	}

	NG_ERRCODE CDX12Graphic::Create(const CreateParam& param)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// DX12デバッグレイヤー有効化
		NG_DX12_ENABLE_DEBUG_LAYER();

		// DX12デバイス生成
		{
			NG_LOG("DX12Graphic", "DX12デバイス生成");
			if(NG_FAILED(ret = m_device.Create(param.deviceParam))) {
				NG_ERRLOG_C("DX12Graphic", ret, "DX12デバイスの生成に失敗");
				return ret;
			}
		}

		return ret;
	}

	void CDX12Graphic::Render()
	{

	}

	void CDX12Graphic::Destroy()
	{
		m_device.Destroy();
	}

	CDX12Device& CDX12Graphic::GetDevice()
	{
		return m_device;
	}
	const CDX12Device& CDX12Graphic::GetDevice() const
	{
		return m_device;
	}

}	//namespace ng
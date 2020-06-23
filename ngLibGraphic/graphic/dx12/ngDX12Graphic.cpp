/*!
* @file		ngDX12Graphic.cpp
* @brief	DX12グラフィックス
* @date		2017-08-23
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
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
	}

	NG_ERRCODE CDX12Graphic::Create(const CreateParam& param)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		

		return ret;
	}

	void CDX12Graphic::Render()
	{

	}

	void CDX12Graphic::Destroy()
	{

	}

}	//namespace ng
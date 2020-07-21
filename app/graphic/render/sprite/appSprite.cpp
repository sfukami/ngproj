﻿/*!
* @file		appSprite.cpp
* @brief	スプライト
* @date		2020-07-19
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "ngLibGraphic/graphic/dx12/ngDX12.h"
#include "appSprite.h"
#include "../appRenderParam.h"
#include "../../appGraphicUtil.h"

namespace app
{
	CSprite::CSprite()
	{
	}
	CSprite::~CSprite()
	{
	}

	bool CSprite::Create(
		unsigned int width
		, unsigned int height
		)
	{
		ng::CDX12Device* pDX12Device = ng::DX12Util::GetDevice();
		NG_ASSERT_NOT_NULL(pDX12Device);

		// DX12ポリゴン 矩形生成
		NG_ERRCODE err = m_square.Create(*pDX12Device, (float)width, (float)height, true);
		if(NG_FAILED(err)) {
			NG_ERRLOG_C("Sprite", err, "DX12ポリゴン 矩形の生成に失敗しました.");
			return false;
		}

		return true;
	}

	void CSprite::Destroy()
	{
		m_square.Destroy();
	}

	bool CSprite::IsEnable() const
	{
		if(!_isCreate()) return false;

		return true;
	}

	void CSprite::_render(const RenderParam* pParam)
	{
		if(!_isCreate()) return;

		ng::CDX12CommandList* pCmdList = GraphicUtil::GetDX12CommandList(pParam->cmdListId);
		NG_ASSERT_NOT_NULL(pCmdList);

		m_square.Render(*pCmdList);
	}

	bool CSprite::_isCreate() const
	{
		return m_square.IsValid();
	}

}	// namespace app
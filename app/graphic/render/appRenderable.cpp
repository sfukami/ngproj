/*!
* @file		appRenderable.cpp
* @brief	描画可能オブジェクト インターフェース
* @date		2020-07-19
* @author	s.fukami
*/

#include "ngLibGraphic/graphic/ngGraphicManager.h"
#include "appRenderable.h"
#include "appRenderParam.h"

namespace app
{
	IRenderable::IRenderable()
	{
	}
	IRenderable::~IRenderable()
	{
	}

	void IRenderable::RegisterRender()
	{
		if(!IsVisible()) return;
		
		ng::CGraphicManager::GetInstance().AddRenderable(*this);
	}

	void IRenderable::Render(const ng::RenderParam* pParam)
	{
		NG_ASSERT_NOT_NULL(pParam);

		if(!IsVisible()) return;

		RenderParam* pAppParam = const_cast<RenderParam*>(ng::PointerCast<const RenderParam*>(pParam));

		GetWorldMatrix(pAppParam->worldMat);
		pAppParam->CalcWorldViewProjMatrix();

		_render(*pAppParam);
	}

}	// namespace app
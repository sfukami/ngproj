/*!
* @file		appRenderable.cpp
* @brief	描画可能オブジェクト
* @date		2020-07-19
* @author	s.fukami
*/

#include "ngLibGraphic/graphic/ngGraphicManager.h"
#include "appRenderable.h"

namespace app
{
	CRenderable::CRenderable()
	{
	}
	CRenderable::~CRenderable()
	{
	}

	void CRenderable::RegisterRender()
	{
		if(!IsEnable()) return;
		
		ng::CGraphicManager::GetInstance().AddRenderable(*this);
	}

	void CRenderable::Render(const ng::RenderParam* pParam)
	{
		_render(ng::PointerCast<const RenderParam*>(pParam));
	}

	bool CRenderable::IsEnable() const
	{
		return false;
	}

	void CRenderable::_render(const RenderParam* pParam)
	{
	}

}	// namespace app
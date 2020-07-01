/*!
* @file		appGraphicModule.cpp
* @brief	グラフィック機能
* @date		2020-07-01
* @author	s.fukami
*/

#include "appGraphicModule.h"
#include "appGraphic.h"

namespace app
{
	CGraphic* CGraphicModule::s_pGraphic = nullptr;

	void CGraphicModule::SetGraphicPipeline(CGraphicPipeline* pPipeline)
	{
		if(s_pGraphic != nullptr) {
			s_pGraphic->SetPipeline(pPipeline);
		}
	}

	void CGraphicModule::SetGraphic(CGraphic* pGraphic)
	{
		s_pGraphic = pGraphic;
	}

}	// namespace app
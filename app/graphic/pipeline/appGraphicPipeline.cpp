/*!
* @file		appGraphicPipeline.cpp
* @brief	グラフィックパイプライン 基底クラス
* @date		2020-06-24
* @author	s.fukami
*/

#include "ngLibGraphic/graphic/dx12/ngDX12.h"
#include "appGraphicPipeline.h"

namespace app
{
	CGraphicPipeline::CGraphicPipeline()
		: m_isInit(false)
	{
	}
	CGraphicPipeline::~CGraphicPipeline()
	{
	}

	bool CGraphicPipeline::Initialize()
	{
		m_isInit = _initialize();

		return m_isInit;
	}

	void CGraphicPipeline::Finalize()
	{
		_finalize();

		m_isInit = false;
	}

	void CGraphicPipeline::Execute()
	{
		if(!IsInit()) return;

		_preprocessPipeline();
		_execute();
		_postprocessPipeline();
	}

	bool CGraphicPipeline::IsInit() const
	{
		return m_isInit;
	}

	bool CGraphicPipeline::_initialize()
	{
		return true;
	}

	void CGraphicPipeline::_finalize()
	{
	}
	
	void CGraphicPipeline::_execute()
	{
	}

	void CGraphicPipeline::_preprocessPipeline()
	{
	}

	void CGraphicPipeline::_postprocessPipeline()
	{
	}

}	// namespace app
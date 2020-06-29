/*!
* @file		appGraphicPipeline.cpp
* @brief	グラフィックパイプライン 基底クラス
* @date		2020-08-24
* @author	s.fukami
*/

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
		if(IsInit()) {
			_execute();
		}
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

}	// namespace app
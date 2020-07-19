/*!
* @file		ngGraphicManager.cpp
* @brief	グラフィック管理
* @date		2020-06-23
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "ngGraphicManager.h"
#include "ngGraphic.h"

namespace ng
{
	CGraphicManager CGraphicManager::m_instance;

	CGraphicManager::CGraphicManager()
		: m_pGraphic(nullptr)
	{
	}

	CGraphicManager::~CGraphicManager()
	{
		Finalize();
	}

	NG_ERRCODE CGraphicManager::Initialize(u32 commandMax)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// 描画システムを初期化
		if(NG_FAILED(ret = m_renderSys.Initialize(commandMax))) {
			NG_ERRLOG_C("GraphicManager", ret, "描画システムの初期化に失敗しました.");
			return ret;
		}

		return ret;
	}

	void CGraphicManager::Finalize()
	{
		m_renderSys.Finalize();
	}

	void CGraphicManager::AssignGraphic(IGraphic* pGraphic)
	{
		if(pGraphic == nullptr) return;

		m_pGraphic = pGraphic;
	}

	void CGraphicManager::Render(const RenderParam* pParam)
	{
		if(!IsAssigned()) return;

		m_renderSys.ExecuteCommand(pParam);
	}

	void CGraphicManager::CleanupRender()
	{
		if(!IsAssigned()) return;

		m_renderSys.ClearCommand();
	}

	void CGraphicManager::UnassignGraphic()
	{
		m_pGraphic = nullptr;
	}

	bool CGraphicManager::IsAssigned() const
	{
		return (m_pGraphic != nullptr);
	}

	IGraphic* CGraphicManager::GetGraphic()
	{
		return m_pGraphic;
	}
	const IGraphic* CGraphicManager::GetGraphic() const
	{
		return m_pGraphic;
	}

	CGraphicManager* CGraphicManager::_createInstance()
	{
		return &m_instance;
	}

	void CGraphicManager::_destroyInstance(CGraphicManager* pInst)
	{
		// 空定義
	}

}	// namespace ng
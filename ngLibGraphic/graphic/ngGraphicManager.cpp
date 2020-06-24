/*!
* @file		ngGraphicManager.cpp
* @brief	グラフィック管理
* @date		2020-06-23
* @author	s.fukami
*/

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
	}

	void CGraphicManager::AssignGraphic(IGraphic* pGraphic)
	{
		if(pGraphic == nullptr) return;

		m_pGraphic = pGraphic;
	}

	void CGraphicManager::Render()
	{
		if(!IsAssigned()) return;

		m_pGraphic->Render();
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
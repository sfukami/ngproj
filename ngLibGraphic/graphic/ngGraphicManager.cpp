/*!
* @file		ngGraphicManager.cpp
* @brief	グラフィック管理
* @date		2020-06-23
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "ngLibGraphic/render/ngRenderCommand.h"
#include "ngGraphicManager.h"
#include "ngGraphic.h"

namespace ng
{
	CGraphicManager CGraphicManager::m_instance;

	CGraphicManager::CGraphicManager()
		: m_pGraphic(nullptr)
		, m_isInit(false)
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

		m_isInit = true;

		return ret;
	}

	void CGraphicManager::Finalize()
	{
		m_renderSys.Finalize();

		m_isInit = false;
	}

	void CGraphicManager::AssignGraphic(IGraphic* pGraphic)
	{
		NG_ASSERT(_isInit());
		if(pGraphic == nullptr) return;

		m_pGraphic = pGraphic;
	}

	void CGraphicManager::AddRenderable(IRenderable& renderable)
	{
		NG_ASSERT(_isInit());
		if(!IsAssigned()) return;

		// TODO: 仮
		m_renderSys.AddCommand(RenderCommand(0, &renderable));
	}

	void CGraphicManager::Render(const RenderParam* pParam)
	{
		NG_ASSERT(_isInit());
		if(!IsAssigned()) return;

		m_renderSys.ExecuteCommand(pParam);
	}

	void CGraphicManager::CleanupRender()
	{
		NG_ASSERT(_isInit());
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

	bool CGraphicManager::_isInit() const
	{
		return m_isInit;
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
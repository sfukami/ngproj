/*!
* @file		appModelObject.cpp
* @brief	モデルオブジェクト
* @date		2021-06-21
* @author	s.fukami
*/

#include "appModelObject.h"

namespace app
{
	CModelObject::CModelObject()
		: m_isVisible(true)
	{
	}
	CModelObject::~CModelObject()
	{
		Destroy();
	}

	bool CModelObject::Create(const char* modelFilePath, eResourceMemoryType resMemType)
	{
		return m_model.Create(modelFilePath, resMemType);
	}

	void CModelObject::Destroy()
	{
		m_model.Destroy();
	}

	void CModelObject::GetWorldMatrix(ng::Matrix4x4& dst)
	{
		CTransform& transform = GetTransform();
		transform.GetWorldMatrix(dst);
	}

	void CModelObject::SetVisible(bool visible)
	{
		m_isVisible = visible;
	}
	bool CModelObject::IsVisible() const
	{
		return m_isVisible && m_model.IsEnable();
	}

	CModelRender& CModelObject::GetRender()
	{
		return m_model;
	}
	const CModelRender& CModelObject::GetRender() const
	{
		return m_model;
	}

	void CModelObject::_render(const RenderParam& param)
	{
		m_model.Render(param);
	}

}	// namespace app
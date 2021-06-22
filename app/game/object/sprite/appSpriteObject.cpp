/*!
* @file		appSpriteObject.cpp
* @brief	スプライトオブジェクト
* @date		2021-06-21
* @author	s.fukami
*/

#include "appSpriteObject.h"

namespace app
{
	CSpriteObject::CSpriteObject()
		: m_isVisible(true)
	{
	}
	CSpriteObject::~CSpriteObject()
	{
		Destroy();
	}

	bool CSpriteObject::Create(
		ng::u32 width
		, ng::u32 height
		, const char* imageFilePath
		, eResourceMemoryType resMemType
		)
	{
		return m_sprite.Create(width, height, imageFilePath, resMemType);
	}

	void CSpriteObject::Destroy()
	{
		m_sprite.Destroy();
	}

	void CSpriteObject::GetWorldMatrix(ng::Matrix4x4& dst)
	{
		CTransform& transform = GetTransform();
		transform.GetWorldMatrix(dst);
	}

	void CSpriteObject::SetVisible(bool visible)
	{
		m_isVisible = visible;
	}
	bool CSpriteObject::IsVisible() const
	{
		return m_isVisible && m_sprite.IsEnable();
	}

	void CSpriteObject::_render(const RenderParam& param)
	{
		m_sprite.Render(param);
	}

}	// namespace app
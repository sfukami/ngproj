/*!
* @file		ngRenderCommand.cpp
* @brief	描画コマンド
* @date		2020-07-07
* @author	s.fukami
*/

#include "ngRenderCommand.h"
#include "ngRenderable.h"

namespace ng
{
	CRenderCommand::CRenderCommand(IRenderable* pRenderable)
		: m_pRenderable(pRenderable)
	{
	}

	CRenderCommand::~CRenderCommand()
	{
	}

	void CRenderCommand::Execute()
	{
		if(m_pRenderable != nullptr) {
			m_pRenderable->Render();
		}
	}

}	// namespace ng
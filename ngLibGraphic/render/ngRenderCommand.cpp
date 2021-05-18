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
	RenderCommand::RenderCommand()
		: order(0), pRenderable(nullptr)
	{
	}

	RenderCommand::RenderCommand(u32 _order, IRenderable* _pRenderable)
		: order(_order), pRenderable(_pRenderable)
	{
	}

	void RenderCommand::Execute(const RenderParam* pParam)
	{
		pRenderable->Render(pParam);
	}

}	// namespace ng
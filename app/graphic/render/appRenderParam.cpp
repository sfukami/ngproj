/*!
* @file		appRenderParam.cpp
* @brief	描画パラメータ
* @date		2020-07-19
* @author	s.fukami
*/

#include "appRenderParam.h"

namespace app
{
	RenderParam::RenderParam()
		: cmdListId(eGraphicCommandListId::MAIN)
	{
		ng::MatrixOp::Identity(viewMat);
		ng::MatrixOp::Identity(projMat);
		ng::MatrixOp::Identity(vpMat);
	}

	void RenderParam::CalcViewProjMatrix()
	{
		ng::MatrixOp::Multiply(vpMat, viewMat, projMat);
	}

}	// namespace app
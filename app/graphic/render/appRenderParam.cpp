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
		ng::MatrixOp::Identity(worldMat);
		ng::MatrixOp::Identity(viewMat);
		ng::MatrixOp::Identity(projMat);
		ng::MatrixOp::Identity(vpMat);
		ng::MatrixOp::Identity(wvpMat);
	}

	void RenderParam::CalcViewProjMatrix()
	{
		ng::MatrixOp::Multiply(vpMat, viewMat, projMat);
	}

	void RenderParam::CalcWorldViewProjMatrix()
	{
		ng::MatrixOp::Multiply(wvpMat, worldMat, vpMat);
	}

}	// namespace app
/*!
* @file		appShaderParam.cpp
* @brief	シェーダーエフェクト パラメータ
* @date		2021-06-16
* @author	s.fukami
*/

#include "ngLibCore/geometry/matrix/ngMatrixOp.h"
#include "appShaderParam.h"

namespace app
{
	ShaderParam::ShaderParam()
	{
		ng::MatrixOp::Identity(wvpMat);
	}

}	// namespace app
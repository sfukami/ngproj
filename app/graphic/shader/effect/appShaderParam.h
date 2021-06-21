/*!
* @file		appShaderParam.h
* @brief	シェーダーエフェクト パラメータ
* @date		2021-06-16
* @author	s.fukami
*/

#ifndef __APP_SHADER_PARAM_H__
#define __APP_SHADER_PARAM_H__

#include "ngLibCore/geometry/matrix/ngMatrix4x4.h"

namespace app
{
	/*!
	* @brief					シェーダーエフェクト パラメータ
	*/
	struct ShaderParam
	{
		ShaderParam();

		ng::Matrix4 wvpMat;		//!< ワールドビュープロジェクション行列
	};

}	// namespace app

#endif	// __APP_SHADER_PARAM_H__
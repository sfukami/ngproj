/*!
* @file		appShaderEffect.h
* @brief	シェーダーエフェクト 基底クラス
* @date		2020-07-28
* @author	s.fukami
*/

#ifndef __APP_SHADER_EFFECT_H__
#define __APP_SHADER_EFFECT_H__

namespace app
{
	/*!
	* @brief					シェーダーエフェクト 基底クラス
	*/
	class CShaderEffect
	{
	public:
		CShaderEffect();
		virtual ~CShaderEffect();
	};

}	// namespace app

#endif	// __APP_SHADER_EFFECT_H__
/*!
* @file		appMaterial.cpp
* @brief	シェーダーエフェクト テーブル
* @date		2020-08-14
* @author	s.fukami
*/

// シェーダーエフェクト
#include "../appShaderEffectTexture.h"

namespace ng
{
	class IMemoryAllocator;
}
namespace app
{
	class CShaderEffect;
	class CShaderEffectFactory;
}

namespace app
{
	//! シェーダーエフェクトテーブル宣言
	#define _SHADER_EFFECT_TABLE() \
		static const ShaderEffectInfo s_shaderEffectTable[] = { \
			_SHADER_EFFECT_INFO("texture", CShaderEffectTexture), \
		};

}	// namespace app

namespace app
{
	//! シェーダーエフェクト情報設定
	#define _SHADER_EFFECT_INFO(_name, _type) \
		{ _name, &CShaderEffectFactory::_createShaderEffect<_type> }

	//! シェーダーエフェクト情報
	struct ShaderEffectInfo
	{
		using FuncType = CShaderEffect*(CShaderEffectFactory::*)(ng::IMemoryAllocator&)const;	//!< シェーダーエフェクト生成関数

		const char* name;	//!< 名前
		FuncType func;	//!< シェーダーエフェクト生成関数
	};

}	// namespace app
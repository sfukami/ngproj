/*!
* @file		appMaterial.cpp
* @brief	シェーダーエフェクト テーブル
* @date		2020-08-14
* @author	s.fukami
*/

// シェーダーエフェクト
#include "../appShaderEffectSprite.h"

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
	//! シェーダーエフェクトテーブル
	#define _SHADER_EFFECT_TABLE	(s_shaderEffectTable)

	//! シェーダーエフェクトテーブル宣言
	#define _DECLARE_SHADER_EFFECT_TABLE() \
		static const ShaderEffectInfo _SHADER_EFFECT_TABLE[] = { \
			_SHADER_EFFECT_INFO("sprite", CShaderEffectSprite), \
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
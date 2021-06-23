/*!
* @file		appShaderEffectTable.cpp
* @brief	シェーダーエフェクト テーブル
* @date		2020-08-14
* @author	s.fukami
*/

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
	//! シェーダーエフェクト情報設定
	#define _SHADER_EFFECT_INFO(_type) \
		{ _type::GetName(), &CShaderEffectFactory::_createShaderEffect<_type> }

	//! シェーダーエフェクト情報
	struct ShaderEffectInfo
	{
		using FuncType = CShaderEffect*(CShaderEffectFactory::*)(ng::IMemoryAllocator&)const;	//!< シェーダーエフェクト生成関数

		const char* name;	//!< 名前
		FuncType func;	//!< シェーダーエフェクト生成関数
	};

}	// namespace app
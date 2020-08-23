/*!
* @file		appShaderEffectFactory.cpp
* @brief	シェーダーエフェクト ファクトリ
* @date		2020-07-28
* @author	s.fukami
*/

#include "appShaderEffectFactory.h"

// シェーダーエフェクト テーブル
#include "appShaderEffectTable.cpp"

namespace app
{
	CShaderEffectFactory::CShaderEffectFactory()
	{
	}
	CShaderEffectFactory::~CShaderEffectFactory()
	{
		Finalize();
	}

	bool CShaderEffectFactory::Initialize()
	{
		bool result = true;

		// シェーダーエフェクトテーブル宣言
		_SHADER_EFFECT_TABLE();

		for(int i = 0; i < NG_ARRAY_SIZE(s_shaderEffectTable); i++)
		{
			const ShaderEffectInfo& info = s_shaderEffectTable[i];

			if(!m_funcMap.Add(info.name, info.func)) {
				NG_ERRLOG("ShaderEffectFactory", "シェーダーエフェクト生成関数の追加に失敗しました. name:%s", info.name);
				result = false;
			}
		}

		return result;
	}

	void CShaderEffectFactory::Finalize()
	{
		m_funcMap.Clear();
	}

	bool CShaderEffectFactory::Create(
		ng::IMemoryAllocator& alloc, const char* name, ng::CSharedPtr<CShaderEffect>& dstPtr
		) const
	{
		FuncType func = nullptr;
		if(!m_funcMap.Get(name, func)) {
			NG_ERRLOG("ShaderEffectFactory", "シェーダーエフェクト生成関数の取得に失敗しました. name:%s", name);
			return false;
		}

		CShaderEffect* pShEff = (this->*func)(alloc);
		if(pShEff == nullptr) {
			NG_ERRLOG("ShaderEffectFactory", "シェーダーエフェクトオブジェクトの生成に失敗しました. name:%s", name);
			return false;
		}

		dstPtr.reset(pShEff);

		return true;
	}

}	// namespace app
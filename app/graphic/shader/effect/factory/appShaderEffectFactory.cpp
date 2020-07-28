/*!
* @file		appShaderEffectFactory.cpp
* @brief	シェーダーエフェクト ファクトリ
* @date		2020-07-28
* @author	s.fukami
*/

#include "appShaderEffectFactory.h"
// シェーダーエフェクト
#include "../appShaderEffectTexture.h"

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

		// シェーダーエフェクト生成関数追加
		{
			// シェーダーエフェクト生成関数追加マクロ
			#define _ADD_CREATE_FUNC(_name, _type) \
				m_funcMap.Add(_name, &CShaderEffectFactory::_createShaderEffect<_type>)

			result &= _ADD_CREATE_FUNC("texture", CShaderEffectTexture);
			
			#undef _ADD_CREATE_FUNC
		}

		return result;
	}

	void CShaderEffectFactory::Finalize()
	{
		m_funcMap.Clear();
	}

	bool CShaderEffectFactory::Create(
		ng::IMemoryAllocator& alloc, const char* name, ng::CSharedPtr<CShaderEffect>& dstPtr
		)
	{
		FuncType func = nullptr;
		if(!m_funcMap.Get(name, func)) {
			NG_ERRLOG("ShaderEffectFactory", "シェーダーエフェクト生成関数の取得に失敗しました. name:%s", name);
			return false;
		}

		CShaderEffect* pShEff = (this->*func)(alloc);
		if(pShEff == nullptr) {
			NG_ERRLOG("ShaderEffectFactory", "シェーダーエフェクトの生成に失敗しました. name:%s", name);
			return false;
		}

		dstPtr.reset(pShEff);

		return true;
	}

}	// namespace app
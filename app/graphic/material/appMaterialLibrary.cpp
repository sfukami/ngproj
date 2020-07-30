/*!
* @file		appMaterialLibrary.cpp
* @brief	マテリアルライブラリ
* @date		2020-07-30
* @author	s.fukami
*/

#include "appMaterialLibrary.h"

namespace app
{
	CMaterialLibrary::CMaterialLibrary()
	{
	}
	CMaterialLibrary::~CMaterialLibrary()
	{
		Clear();
	}

	bool CMaterialLibrary::Add(const char* name, const CMaterial& material)
	{
		if(!m_matMap.Add(name, material)) {
			NG_ERRLOG("MaterialLibrary", "マテリアルの追加に失敗しました. name:%s", name);
			return false;
		}

		return true;
	}
	
	bool CMaterialLibrary::Copy(const char* name, CMaterial& dst)
	{
		return m_matMap.Get(name, dst);
	}

	void CMaterialLibrary::Clear()
	{
		m_matMap.Clear();
	}

}	// namespace app
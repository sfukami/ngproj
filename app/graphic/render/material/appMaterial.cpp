/*!
* @file		appMaterial.cpp
* @brief	マテリアル
* @date		2020-07-22
* @author	s.fukami
*/

#include "appMaterial.h"
#include "appMaterialFormat.h"
#include "app/resource/appResourceModule.h"

namespace app
{
	CMaterial::CMaterial()
	{
	}
	CMaterial::~CMaterial()
	{
		Destroy();
	}
	
	bool CMaterial::Build(const MaterialData& data)
	{
		// ディフューズマップ読み込み
		if(!CResourceModule::LoadResource(
			data.diffuseMap.filePath,
			eResourceMemoryType::FIXED,
			m_diffuseMap
			)) {
			NG_ERRLOG("Material", "ディフューズマップの読み込みに失敗しました. filePath:%s", data.diffuseMap.filePath);
			return false;
		}

		return true;
	}

	void CMaterial::Destroy()
	{
		m_diffuseMap.Release();
	}

}	// namespace app
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
		bool result = true;

		// ディフューズマップ読み込み
		result &= _loadResource(data.diffuseMap.filePath, nullptr, m_diffuseMap);

		// 頂点シェーダー読み込み
		result &= _loadShaderResource(data.vertexShader, m_vertexShader);
		// ピクセルシェーダー読み込み
		result &= _loadShaderResource(data.pixelShader, m_pixelShader);

		return result;
	}

	void CMaterial::Destroy()
	{
		m_diffuseMap.Release();
		m_vertexShader.Release();
		m_pixelShader.Release();
	}

	bool CMaterial::_loadResource(const char* filePath, const void* pBuildParam, ng::IResourceHandle& handle)
	{
		if(!CResourceModule::LoadResource(
			filePath,
			eResourceMemoryType::FIXED,
			pBuildParam,
			handle
			)) {
			NG_ERRLOG("Material", "リソースの読み込みに失敗しました. filePath:%s", filePath);
			return false;
		}
	}

	bool CMaterial::_loadShaderResource(const ShaderData& shaderData, ng::IResourceHandle& handle)
	{
		CShader::BuildParam buildParam(shaderData.entryPoint, shaderData.target);
		return _loadResource(shaderData.filePath, &buildParam, handle);
	}

}	// namespace app
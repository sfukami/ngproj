/*!
* @file		appMaterialData.cpp
* @brief	マテリアルデータ
* @date		2021-05-11
* @author	s.fukami
*/

#include "appMaterialData.h"

namespace app
{
	CMaterialData::CMaterialData()
	{
	}
	CMaterialData::~CMaterialData()
	{
	}

	bool CMaterialData::Build(const void* pBinary, ng::size_type size, const void* pBuildParam)
	{
		if(pBinary != nullptr) {
			SetFormat(*ng::PointerCast<const MaterialFormat*>(pBinary));
			return true;
		}

		return false;
	}

	void CMaterialData::SetFormat(const MaterialFormat& matFormat)
	{
		NG_MEMCPY(&m_matFormat, &matFormat, sizeof(matFormat));
	}

	void CMaterialData::SetMaterialName(const char* name)
	{
		m_matFormat.SetMaterialName(name);
	}
	void CMaterialData::SetRootSignatureName(const char* name)
	{
		m_matFormat.SetRootSignatureName(name);
	}
	void CMaterialData::SetPipelineStateName(const char* name)
	{
		m_matFormat.SetPipelineStateName(name);
	}
	void CMaterialData::SetShaderEffectName(const char* name)
	{
		m_matFormat.SetShaderEffectName(name);
	}

	void CMaterialData::SetVertexLayout(ng::eVertexLayout vertexLayout)
	{
		m_matFormat.vertexLayout = vertexLayout;
	}

	void CMaterialData::SetVSFilePath(const char* filePath)
	{
		_setShaderFilePath(&m_matFormat.vertexShader, filePath);
	}
	void CMaterialData::SetVSEntryPoint(const char* entryPoint)
	{
		_setShaderEntryPoint(&m_matFormat.vertexShader, entryPoint);
	}
	void CMaterialData::SetVSTarget(const char* target)
	{
		_setShaderTarget(&m_matFormat.vertexShader, target);
	}

	void CMaterialData::SetPSFilePath(const char* filePath)
	{
		_setShaderFilePath(&m_matFormat.pixelShader, filePath);
	}
	void CMaterialData::SetPSEntryPoint(const char* entryPoint)
	{
		_setShaderEntryPoint(&m_matFormat.pixelShader, entryPoint);
	}
	void CMaterialData::SetPSTarget(const char* target)
	{
		_setShaderTarget(&m_matFormat.pixelShader, target);
	}

	void CMaterialData::SetDiffuseMapFilePath(const char* filePath)
	{
		_setTextureFilePath(&m_matFormat.diffuseMap, filePath);
	}

	const MaterialFormat& CMaterialData::GetFormat() const
	{
		return m_matFormat;
	}

	void CMaterialData::_setShaderFilePath(ShaderFormat* pShaderFormat, const char* filePath)
	{
		pShaderFormat->SetFilePath(filePath);
	}
	void CMaterialData::_setShaderEntryPoint(ShaderFormat* pShaderFormat, const char* entryPoint)
	{
		pShaderFormat->SetEntryPoint(entryPoint);
	}
	void CMaterialData::_setShaderTarget(ShaderFormat* pShaderFormat, const char* target)
	{
		pShaderFormat->SetTarget(target);
	}

	void CMaterialData::_setTextureFilePath(TextureFormat* pTextureFormat, const char* filePath)
	{
		pTextureFormat->SetFilePath(filePath);
	}

}	// namespace app
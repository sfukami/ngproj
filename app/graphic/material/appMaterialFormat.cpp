/*!
* @file		appMaterialFormat.cpp
* @brief	マテリアルフォーマット
* @date		2020-07-22
* @author	s.fukami
*/

#include "appMaterialFormat.h"

namespace app
{
	TextureData::TextureData()
		: pBinary(nullptr)
	{
		ng::ClearString(filePath);
	}
	void TextureData::SetFilePath(const char* _filePath)
	{
		NG_STRCPY(filePath, _filePath);
	}

	ShaderData::ShaderData()
		: pBinary(nullptr)
	{
		ng::ClearString(filePath);
	}
	void ShaderData::SetFilePath(const char* _filePath)
	{
		NG_STRCPY(filePath, _filePath);
	}
	void ShaderData::SetEntryPoint(const char* _entryPoint)
	{
		NG_STRCPY(entryPoint, _entryPoint);
	}
	void ShaderData::SetTarget(const char* _target)
	{
		NG_STRCPY(target, _target);
	}

	MaterialData::MaterialData()
	{
		ng::ClearString(name);
		ng::ClearString(rootSignatureName);
		ng::ClearString(pipelineStateName);
		ng::ClearString(shaderEffectName);

		vertexLayout = ng::eVertexLayout::STATIC;
	}
	void MaterialData::SetMaterialName(const char* _name)
	{
		NG_STRCPY(name, _name);
	}
	void MaterialData::SetRootSignatureName(const char* _name)
	{
		NG_STRCPY(rootSignatureName, _name);
	}
	void MaterialData::SetPipelineStateName(const char* _name)
	{
		NG_STRCPY(pipelineStateName, _name);
	}
	void MaterialData::SetShaderEffectName(const char* _name)
	{
		NG_STRCPY(shaderEffectName, _name);
	}

}	// namespace app
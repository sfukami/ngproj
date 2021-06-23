/*!
* @file		appMaterialFormat.cpp
* @brief	マテリアルフォーマット
* @date		2020-07-22
* @author	s.fukami
*/

#include "appMaterialFormat.h"

namespace app
{
	TextureFormat::TextureFormat()
		: pBinary(nullptr), size(0), resMemType(eResourceMemoryType::FIXED)
	{
		ng::ClearString(filePath);
	}
	void TextureFormat::SetFilePath(const char* _filePath)
	{
		NG_STRCPY(filePath, _filePath);
	}
	void TextureFormat::SetName(const char* _name)
	{
		NG_STRCPY(name, _name);
	}
	bool TextureFormat::IsValidFilePath() const
	{
		return NG_STRLEN(filePath) > 0;
	}
	bool TextureFormat::IsValidBinary() const
	{
		return (pBinary != nullptr) && (size > 0);
	}

	ShaderFormat::ShaderFormat()
		: pBinary(nullptr), size(0), resMemType(eResourceMemoryType::FIXED)
	{
		NG_STRCLR(filePath);
		NG_STRCLR(entryPoint);
		NG_STRCLR(target);
	}
	void ShaderFormat::SetFilePath(const char* _filePath)
	{
		NG_STRCPY(filePath, _filePath);
	}
	void ShaderFormat::SetEntryPoint(const char* _entryPoint)
	{
		NG_STRCPY(entryPoint, _entryPoint);
	}
	void ShaderFormat::SetTarget(const char* _target)
	{
		NG_STRCPY(target, _target);
	}
	bool ShaderFormat::IsValidFilePath() const
	{
		return NG_STRLEN(filePath) > 0;
	}
	bool ShaderFormat::IsValidBinary() const
	{
		return (pBinary != nullptr) && (size > 0);
	}

	MaterialFormat::MaterialFormat()
	{
		NG_STRCLR(name);
		NG_STRCLR(rootSignatureName);
		NG_STRCLR(pipelineStateName);
		NG_STRCLR(shaderEffectName);

		vertexLayout = ng::eVertexLayout::STATIC;
	}
	void MaterialFormat::SetMaterialName(const char* _name)
	{
		NG_STRCPY(name, _name);
	}
	void MaterialFormat::SetRootSignatureName(const char* _name)
	{
		NG_STRCPY(rootSignatureName, _name);
	}
	void MaterialFormat::SetPipelineStateName(const char* _name)
	{
		NG_STRCPY(pipelineStateName, _name);
	}
	void MaterialFormat::SetShaderEffectName(const char* _name)
	{
		NG_STRCPY(shaderEffectName, _name);
	}

}	// namespace app
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
	}

}	// namespace app
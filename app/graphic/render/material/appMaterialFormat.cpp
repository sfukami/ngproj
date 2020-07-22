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

	MaterialData::MaterialData()
	{
	}

}	// namespace app
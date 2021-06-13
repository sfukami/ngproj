/*!
* @file		GLTFModelConverter.cpp
* @brief	glTFモデル変換
* @date		2021-06-07
* @author	s.fukami
*/

#include "GLTFModelConverter.h"
#include "GLTFStreamReader.h"
#include "ModelBinaryWriter.h"
#include "../model/ModelFormat.h"

namespace glTFConv
{
	CGLTFModelConverter::CGLTFModelConverter()
	{
	}
	CGLTFModelConverter::~CGLTFModelConverter()
	{
	}

	bool CGLTFModelConverter::Convert(const char* pSrcFilePath, const char* pDstFilePath)
	{
		CGLTFStreamReader streamReader;
		CModelBinaryWriter binaryWriter;
		ModelFormat modelFormat;

		// 中間モデル形式を生成
		if(!streamReader.Read(pSrcFilePath, &modelFormat)) {
			return false;
		}

		// 中間モデル形式をバイナリ出力
		if(!binaryWriter.Write(pDstFilePath, modelFormat)) {
			return false;
		}

		return true;
	}

}	// namespace glTFConv
/*!
* @file		GLTFModelConverter.cpp
* @brief	glTFモデル変換
* @date		2021-06-07
* @author	s.fukami
*/

//#include "ngLibCore/io/file/ngFile.h"
#include "GLTFModelConverter.h"
#include "GLTFStreamReader.h"

namespace glTFConv
{
	CGLTFModelConverter::CGLTFModelConverter()
	{
	}
	CGLTFModelConverter::~CGLTFModelConverter()
	{
	}

	bool CGLTFModelConverter::Convert(const char* pFilePath)
	{
		CGLTFStreamReader streamReader;

		if(!streamReader.Read(pFilePath)) {
			return false;
		}
		
		/*
		ng::CFile inputFile;

		NG_ERRCODE err = inputFile.Open(pFilePath, "r");
		if(NG_FAILED(err)) {
			NG_ERRLOG_C("GLTFModelConverter", err, "変換元ファイルの読み込みに失敗しました.");
			return false;
		}
		*/

		return true;
	}

}	// namespace glTFConv
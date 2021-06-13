/*!
* @file		BinaryFormat.cpp
* @brief	モデルバイナリ形式
* @date		2021-06-11
* @author	s.fukami
*/

#include "BinaryFormat.h"

namespace glTFConv
{
	BinaryFormat::ModelHeader::ModelHeader()
		: signature(GLTFCONV_BINARY_FORMAT_MODEL_SIGNATURE)
	{
	}

}	// namespace glTFConv
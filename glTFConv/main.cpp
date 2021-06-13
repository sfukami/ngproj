/*!
* @file		main.cpp
* @brief	エントリ
* @date		2021-06-07
* @author	s.fukami
*/

#include <locale.h>
#include "ngLibCore/locale/ngLocale.h"
#include "glTFConv/converter/GLTFModelConverter.h"

int main()
{
	ng::SetLocaleDefault(LC_CTYPE);

	glTFConv::CGLTFModelConverter conv;

	// test
	const char srcFilePath[256] = "C:/local/project/ngproj/glTFConv/resources/alicia-solid.vrm";
	const char dstFilePath[256] = "C:/local/project/ngproj/glTFConv/resources/test.mdl";

	if(!conv.Convert(srcFilePath, dstFilePath)) {
		return 1;
	}

	return 0;
}
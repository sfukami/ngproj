/*!
* @file		main.cpp
* @brief	エントリ
* @date		2021-06-07
* @author	s.fukami
*/

#include <locale.h>
#include <filesystem>
#include "ngLibCore/locale/ngLocale.h"
#include "glTFConv/converter/GLTFModelConverter.h"

int main(int argc, char* argv[])
{
	ng::SetLocaleDefault(LC_CTYPE);

	if(argc != 3) {
		ng::Printf("変換元ファイルのパスと出力先フォルダのパスを指定してください.");
		return 1;
	}

	const char* pSrcFilePath = argv[1];
	const char* pDstPath = argv[2];

	if(!std::filesystem::is_regular_file(pSrcFilePath)) {
		ng::Printf("変換元ファイルのパスにファイルが含まれていません.");
		return 1;
	}
	if(!std::filesystem::exists(pSrcFilePath)) {
		ng::Printf("変換元ファイルのパスのファイルが存在しません.");
		return 1;
	}
	if(!std::filesystem::is_directory(pDstPath)) {
		ng::Printf("出力先フォルダのパスにフォルダが含まれていません.");
		return 1;
	}
	if(!std::filesystem::exists(pDstPath)) {
		ng::Printf("出力先フォルダのパスのフォルダが存在しません.");
		return 1;
	}

	const char* outputFileExt = ".mdl";
	std::filesystem::path srcFilePath(pSrcFilePath);
	std::filesystem::path dstFilePath = std::filesystem::path(pDstPath) / srcFilePath.filename().replace_extension(outputFileExt);

	ng::Printf("SrcFile:%s\n", srcFilePath.string().c_str());
	ng::Printf("DstFile:%s\n", dstFilePath.string().c_str());

	glTFConv::CGLTFModelConverter conv;
	if(!conv.Convert(srcFilePath.string().c_str(), dstFilePath.string().c_str())) {
		ng::Printf("モデルの変換に失敗しました.");
		return 1;
	}

	return 0;
}
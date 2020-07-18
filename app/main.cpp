/*!
* @file		main.cpp
* @brief	エントリ
* @date		2016-08-22
* @author	s.fukami
*/

#include <Windows.h>
#include "application/appApplication.h"

/*! エントリ */
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
{
	INT retCode = 0;

	app::CApplication application;

	// 初期化
	if (!application.Initialize(hInst)) {
		return retCode;
	}

	// メインループ
	retCode = application.MainLoop();

	// 終了処理
	application.Finalize();

	return retCode;
}
/*!
* @file		main.cpp
* @brief	エントリ
* @date		2016-08-22
* @author	s.fukami
*/

#include <Windows.h>
#include "game/appGame.h"

// エントリ
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
{
	INT retCode = 0;

	app::CGame game;

	// 初期化
	if (!game.Initialize(hInst)) {
		return retCode;
	}

	// メインループ
	retCode = game.MainLoop();

	// 終了処理
	game.Finalize();

	return retCode;
}

/*!
* @file		main.cpp
* @brief	�G���g��
* @date		2016-08-22
* @author	s.fukami
*/

#include <Windows.h>
#include "game/appGame.h"

// �G���g��
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
{
	INT retCode = 0;

	app::CGame game;

	// ������
	if (!game.Initialize(hInst)) {
		return retCode;
	}

	// ���C�����[�v
	retCode = game.MainLoop();

	// �I������
	game.Finalize();

	return retCode;
}

/*!
* @file		appGameActorPlayer.cpp
* @brief	ゲームアクター プレイヤー
* @date		2020-07-12
* @author	s.fukami
*/

#include "appGameActorPlayer.h"

namespace app
{
	CGameActorPlayer::CGameActorPlayer()
		: CGameActor(eGameActorType::PLAYER)
	{
	}

	CGameActorPlayer::~CGameActorPlayer()
	{
	}

	void CGameActorPlayer::Update(float deltaTime)
	{
		_update(deltaTime);
	}

	void CGameActorPlayer::Render()
	{
		_render();
	}

	void CGameActorPlayer::_update(float deltaTime)
	{
	}

	void CGameActorPlayer::_render()
	{
	}

}	// namespace app
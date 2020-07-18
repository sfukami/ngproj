/*!
* @file		appGameActorPlayer.cpp
* @brief	ゲームアクター プレイヤー
* @date		2020-07-12
* @author	s.fukami
*/

#include "appGameActorPlayer.h"
#include "app/game/job/appGameJobUtil.h"

namespace app
{
	CGameActorPlayer::CGameActorPlayer()
		: CGameActor(eGameActorType::PLAYER)
	{
	}

	CGameActorPlayer::~CGameActorPlayer()
	{
	}

	void CGameActorPlayer::Schedule(float deltaTime)
	{
		GameJobUtil::CreateGameJob(eGameJobType::UPDATE_PLAYER, this, &CGameActorPlayer::Update, deltaTime);
		GameJobUtil::CreateGameJob(eGameJobType::RENDER_PLAYER, this, &CGameActorPlayer::Render);
	}

	void CGameActorPlayer::Update(float deltaTime)
	{
		//test
		NG_DPRINTF("[CGameActorPlayer::Update]\n");

		_update(deltaTime);
	}

	void CGameActorPlayer::Render()
	{
		//test
		NG_DPRINTF("[CGameActorPlayer::Render]\n");

		_render();
	}

	void CGameActorPlayer::_update(float deltaTime)
	{
	}

	void CGameActorPlayer::_render()
	{
	}

}	// namespace app
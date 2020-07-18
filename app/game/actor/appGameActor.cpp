/*!
* @file		appGameActor.cpp
* @brief	ゲームアクター
* @date		2020-07-12
* @author	s.fukami
*/

#include "appGameActor.h"

namespace app
{
	CGameActor::CGameActor(eGameActorType actorType)
		: m_actorType(actorType)
	{
	}

	CGameActor::~CGameActor()
	{
	}

	void CGameActor::Schedule(float deltaTime)
	{
	}

	void CGameActor::Update(float deltaTime)
	{
	}

	void CGameActor::Render()
	{
	}

	eGameActorType CGameActor::GetActorType() const
	{
		return m_actorType;
	}
	
}	// namespace app
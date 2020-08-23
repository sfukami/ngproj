﻿/*!
* @file		appGameWorld.cpp
* @brief	ゲームワールド
* @date		2020-07-15
* @author	s.fukami
*/

#include "appGameWorld.h"
#include "app/game/actor/appGameActorMacro.h"

namespace app
{
	CGameWorld::CGameWorld()
	{
	}

	CGameWorld::~CGameWorld()
	{
	}

	bool CGameWorld::Initialize()
	{
		return true;
	}

	void CGameWorld::Update(float deltaTime)
	{
		// 各アクターのスケジュール実行
		for(auto actorType : eGameActorType())
		{
			ActorList& actorList = _getActorList(actorType);

			typename ActorList::NodeType* pNode = actorList.Begin();
			for(; pNode != actorList.End(); pNode = pNode->GetNext())
			{
				pNode->GetElem().Schedule(deltaTime);
			}
		}
	}

	void CGameWorld::Render()
	{
	}

	void CGameWorld::Finalize()
	{
		for(auto actorType : eGameActorType())
		{
			_clearActor(actorType);
		}
	}

	void CGameWorld::AddActor(CGameActor& actor)
	{
		ActorList& actorList = _getActorList(actor.GetActorType());

		actorList.PushBack(actor);
	}

	void CGameWorld::_clearActor(eGameActorType actorType)
	{
		ActorList& actorList = _getActorList(actorType);

		while(!actorList.Empty())
		{
			CGameActor& actor = actorList.Front();
			actorList.PopFront();

			actor.Destroy();
			NG_DELETE(app::GameActorMacro::_GetGameActorMemAlloc(), &actor);
		}
	}

	CGameWorld::ActorList& CGameWorld::_getActorList(eGameActorType actorType)
	{
		NG_ASSERT(actorType != eGameActorType::UNKNOWN);
		NG_ASSERT(actorType < eGameActorType::NUM);

		return m_actorListArr[ ng::UnderlyingCast(actorType) ];
	}
	const CGameWorld::ActorList& CGameWorld::_getActorList(eGameActorType actorType) const
	{
		return const_cast<CGameWorld*>(this)->_getActorList(actorType);
	}

}	// namespace app
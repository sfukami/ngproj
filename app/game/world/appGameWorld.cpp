/*!
* @file		appGameWorld.cpp
* @brief	ゲームワールド
* @date		2020-07-15
* @author	s.fukami
*/

#include "appGameWorld.h"

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
		for(auto type : eGameActorType())
		{
			ActorList& actorList = _getActorList(type);

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
		for(auto type : eGameActorType())
		{
			ActorList& actorList = _getActorList(type);
			actorList.Clear();
		}
	}

	void CGameWorld::AddActor(CGameActor& actor)
	{
		ActorList& actorList = _getActorList(actor.GetActorType());

		actorList.PushBack(actor);
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
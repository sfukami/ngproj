/*!
* @file		appGameWorld.cpp
* @brief	ゲームワールド
* @date		2020-07-15
* @author	s.fukami
*/

#include "appGameWorld.h"
#include "app/game/actor/appGameActorMacro.h"
#include "app/game/job/appGameJobUtil.h"

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
		_checkDeleteAllActors();
		_scheduleAllActors(deltaTime);
	}

	void CGameWorld::Render()
	{
	}

	void CGameWorld::Finalize()
	{
		for(auto actorType : eGameActorType())
		{
			_clearActors(actorType);
		}
	}

	void CGameWorld::AddActor(CGameActor& actor)
	{
		ActorList& actorList = _getActorList(actor.GetActorType());

		actorList.PushBack(actor);
	}

	void CGameWorld::_checkDeleteAllActors()
	{
		// 削除可能なアクターを削除
		for(auto actorType : eGameActorType())
		{
			ActorList& actorList = _getActorList(actorType);

			typename ActorList::NodeType* pNode = actorList.Begin();
			for(; pNode != actorList.End(); )
			{
				CGameActor* pActor = &pNode->GetElem();
				if(pActor->CheckDelete()) {
					pNode = actorList.Erase(pNode);

					pActor->Destroy();
					APP_DELETE_GAME_ACTOR(pActor);
					continue;
				}

				pNode = pNode->GetNext();
			}
		}
	}

	void CGameWorld::_scheduleAllActors(float deltaTime)
	{
		//! ジョブ生成マクロ
		#define _CREATE_GAME_JOB(_jobType, _func, _actorType) \
			GameJobUtil::CreateGameJob(eGameJobType::_jobType, this, &CGameWorld::_func, eGameActorType::_actorType)
		#define _CREATE_GAME_JOB_P1(_jobType, _func, _actorType, _p1) \
			GameJobUtil::CreateGameJob(eGameJobType::_jobType, this, &CGameWorld::_func, eGameActorType::_actorType, _p1)

		// アクター更新
		_CREATE_GAME_JOB_P1(UPDATE_PLAYER,			_updateActors,	PLAYER,			deltaTime);
		_CREATE_GAME_JOB_P1(UPDATE_ENEMY,			_updateActors,	ENEMY,			deltaTime);
		_CREATE_GAME_JOB_P1(UPDATE_PLAYER_BULLET,	_updateActors,	PLAYER_BULLET,	deltaTime);

		// アクター描画
		_CREATE_GAME_JOB(RENDER_PLAYER,			_renderActors,	PLAYER);
		_CREATE_GAME_JOB(RENDER_ENEMY,			_renderActors,	ENEMY);
		_CREATE_GAME_JOB(RENDER_PLAYER_BULLET,	_renderActors,	PLAYER_BULLET);
	}

	void CGameWorld::_clearActors(eGameActorType actorType)
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

	void CGameWorld::_updateActors(eGameActorType actorType, float deltaTime)
	{
		ActorList& actorList = _getActorList(actorType);

		for(auto& actor : actorList)
		{
			actor.Update(deltaTime);
		}
	}

	void CGameWorld::_renderActors(eGameActorType actorType)
	{
		ActorList& actorList = _getActorList(actorType);

		for(auto& actor : actorList)
		{
			actor.Render();
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
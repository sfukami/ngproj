/*!
* @file		appGameActorMacro.cpp
* @brief	ゲームアクター マクロ
* @date		2020-07-17
* @author	s.fukami
*/

#include "appGameActorMacro.h"
#include "app/memory/appMemoryUtil.h"
#include "../appGameModule.h"

namespace app
{
namespace GameActorMacro
{
	ng::IMemoryAllocator& _GetGameActorMemAlloc()
	{
		return APP_GET_MEMALLOC(APPLICATION);
	}

	CGameActor* _AddGameActor(CGameActor* pActor)
	{
		CGameModule::AddActor(pActor);

		return pActor;
	}
	
}	// namespace GameActorMacro
}	// namespace app
/*!
* @file		appGameJobUtil.h
* @brief	ゲームジョブ ユーティリティ
* @date		2020-07-18
* @author	s.fukami
*/

#include "appGameJobUtil.h"
#include "app/memory/appMemoryUtil.h"
#include "../appGameModule.h"

namespace app
{
namespace GameJobUtil
{
	ng::IMemoryAllocator& _GetGameJobMemAlloc()
	{
		return APP_MEMALLOC_GAME_JOB;
	}

	bool _AddGameJob(eGameJobType jobType, CGameJob* pJob)
	{
		if(!CGameModule::AddGameJob(jobType, pJob)) {
			NG_DELETE(_GetGameJobMemAlloc(), pJob);
			return false;
		}

		return true;
	}

}	// namespace GameJobUtil
}	// namespace app
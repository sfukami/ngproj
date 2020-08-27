/*!
* @file		appGameJobQueueSize.cpp
* @brief	ゲーム ジョブキューのサイズ
* @date		2020-07-16
* @author	s.fukami
*/

#include "appGameJobQueueSize.h"
#include "appGameJobType.h"

namespace app
{
	//! 各ジョブキューのサイズ
	static const unsigned int s_gameJobQueueSizeTbl[] =
	{
		1,		// UPDATE_PLAYER
		10,		// UPDATE_ENEMY
		10,		// UPDATE_PLAYER_BULLET
		10,		// UPDATE_ENEMY_BULLET
		10,		// CHKCOL_PLAYER_TO_ENEMY
		1,		// RENDER_PLAYER
		10,		// RENDER_ENEMY
		10,		// RENDER_PLAYER_BULLET
		10,		// RENDER_ENEMY_BULLET
	};

	unsigned int GetGameJobQueueSize(eGameJobType jobType)
	{
		NG_ASSERT(jobType < eGameJobType::NUM);

		return s_gameJobQueueSizeTbl[ ng::UnderlyingCast(jobType) ];
	}

	const unsigned int* GetGameJobQueueSizeTable()
	{
		return s_gameJobQueueSizeTbl;
	}

}	// namespace app
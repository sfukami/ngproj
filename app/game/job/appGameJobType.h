/*!
* @file		appGameJobType.h
* @brief	ゲーム ジョブ種類
* @date		2020-07-16
* @author	s.fukami
*/

#ifndef __APP_GAME_JOB_TYPE_H__
#define __APP_GAME_JOB_TYPE_H__

namespace app
{
	/*!
	* @brief					ゲーム ジョブ種類
	* 							値がそのまま実行順序となる
	*/
	enum class eGameJobType : unsigned int
	{
		BEGIN_UPDATE,
		// --------
			// 更新
			UPDATE_PLAYER	= BEGIN_UPDATE,
			UPDATE_ENEMY,
			UPDATE_PLAYER_BULLET,
			UPDATE_ENEMY_BULLET,
			CHKCOL_PLAYER_TO_ENEMY,
		// --------
		END_UPDATE_DUMMY,
		END_UPDATE		= END_UPDATE_DUMMY - 1,

		BEGIN_RENDER,
		// --------
			// 描画
			RENDER_PLAYER	= BEGIN_RENDER,
			RENDER_ENEMY,
			RENDER_PLAYER_BULLET,
			RENDER_ENEMY_BULLET,
		// --------
		END_RENDER_DUMMY,
		END_RENDER		= END_RENDER_DUMMY - 1,

		NUM,
		BEGIN	= 0,
		END		= NUM - 1,
	};
	NG_ENUM_RANGE_BASED_FOR_FUNC(eGameJobType, BEGIN, END);

}	// namespace app

#endif	// __APP_GAME_JOB_TYPE_H__
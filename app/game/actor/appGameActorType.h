/*!
* @file		appGameActorType.h
* @brief	ゲームアクタータイプ
* @date		2020-07-15
* @author	s.fukami
*/

#ifndef __APP_GAME_ACTOR_TYPE_H__
#define __APP_GAME_ACTOR_TYPE_H__

namespace app
{
	/*!
	* @brief					ゲームアクタータイプ
	*/
	enum class eGameActorType : int
	{
		UNKNOWN = -1,	//!< 不明
		PLAYER,			//!< プレイヤー
		ENEMY,			//!< 敵
		BULLET_PLAYER,	//!< プレイヤーの弾
		BULLET_ENEMY,	//!< 敵の弾
		ITEM,			//!< アイテム
		BLOCK,			//!< ブロック

		NUM,
		BEGIN	= 0,
		END		= NUM - 1,
	};
	NG_ENUM_RANGE_BASED_FOR_FUNC(eGameActorType, BEGIN, END);

}	// namespace app

#endif	// __APP_GAME_ACTOR_TYPE_H__
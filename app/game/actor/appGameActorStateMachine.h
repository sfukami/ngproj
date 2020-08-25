/*!
* @file		appGameActorStateMachine.h
* @brief	ゲームアクター用ステートマシン
* @date		2020-08-26
* @author	s.fukami
*/

#ifndef __APP_GAME_ACTOR_STATE_MACHINE_H__
#define __APP_GAME_ACTOR_STATE_MACHINE_H__

#include "ngLibApp/state/ngStateMachine.h"

namespace app
{
	/*!
	* @brief					ゲームアクター用ステートマシン
	*/
	template <class T, typename State, State Num>
	class CGameActorStateMachine : public ng::CClassStateMachine<T, State, Num, ng::CClassAction<T, void, float>>
	{
	public:
		using BaseType = ng::CClassStateMachine<T, State, Num, ng::CClassAction<T, void, float>>;	//!< 基底クラス
		using BaseType::BaseType;	//!< 基底クラスのコンストラクタを使用
	};

}	// namespace app

#endif	// __APP_GAME_ACTOR_STATE_MACHINE_H__
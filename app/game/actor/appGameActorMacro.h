/*!
* @file		appGameActorMacro.h
* @brief	ゲームアクター マクロ
* @date		2020-07-17
* @author	s.fukami
*/

#ifndef __APP_GAME_ACTOR_MACRO_H__
#define __APP_GAME_ACTOR_MACRO_H__

//! ゲームアクター生成
#define APP_CREATE_GAME_ACTOR(_ctor) \
	app::GameActorMacro::_AddGameActor( NG_NEW(app::GameActorMacro::_GetGameActorMemAlloc()) _ctor )->Create()

namespace ng
{
	class IMemoryAllocator;
}
namespace app
{
	class CGameActor;
}

namespace app
{
namespace GameActorMacro
{
	/*! ゲームアクター生成用メモリアロケータ取得 */
	ng::IMemoryAllocator& _GetGameActorMemAlloc();
	/*! ゲームアクター追加 */
	CGameActor* _AddGameActor(CGameActor* pActor);

}	// namespace GameActorMacro
}	// namespace app

#endif	// __APP_GAME_ACTOR_MACRO_H__
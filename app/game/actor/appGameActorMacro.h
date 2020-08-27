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
	app::GameActorMacro::_CreateActor<decltype(_ctor)>( NG_NEW(app::GameActorMacro::_GetGameActorMemAlloc()) _ctor )

//! ゲームアクター削除
#define APP_DELETE_GAME_ACTOR(_actor) \
	NG_DELETE(app::GameActorMacro::_GetGameActorMemAlloc(), _actor)

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

	template <class T>
	T* _CreateActor(T* pActor)
	{
		_AddGameActor(pActor);

		return (pActor->Create() ? pActor : nullptr);
	}

}	// namespace GameActorMacro
}	// namespace app

#endif	// __APP_GAME_ACTOR_MACRO_H__
/*!
* @file		appGameJobUtil.cpp
* @brief	ゲームジョブ ユーティリティ
* @date		2020-07-18
* @author	s.fukami
*/

#ifndef __APP_GAME_JOB_UTIL_H__
#define __APP_GAME_JOB_UTIL_H__

#include "ngLibCore/action/ngAction.h"
#include "appGameJobAction.h"
#include "appGameJobType.h"

namespace ng
{
	class IMemoryAllocator;
}

namespace app
{
namespace GameJobUtil
{
	/*! ゲームジョブ生成用のメモリアロケータ取得 */
	ng::IMemoryAllocator& _GetGameJobMemAlloc();
	/*! ゲームジョブ追加 */
	bool _AddGameJob(eGameJobType jobType, CGameJob* pJob);

	/*!
	* @brief					ゲームジョブ生成
	* @return					生成したジョブ。失敗した場合は nullptr を返す
	* @note						生成されたジョブはジョブ管理へ登録される
	*/
	template <typename Func, typename... Args>
	CGameJobAction<ng::CAction<void, Args...>>* CreateGameJob(eGameJobType jobType, Func pFunc, Args... args)
	{
		using ActionType = ng::CAction<void, Args...>;
		auto pJob = NG_NEW(GameJobUtil::_GetGameJobMemAlloc()) CGameJobAction<ActionType>(ActionType(pFunc), args...);

		if(_AddGameJob(jobType, pJob)) {
			return pJob;
		}

		return nullptr;
	}

	/*!
	* @brief					ゲームジョブ生成（クラス用）
	* @return					生成したジョブ。失敗した場合は nullptr を返す
	* @note						生成されたジョブはジョブ管理へ登録される
	*/
	template <class T, typename Func, typename... Args>
	CGameJobAction<ng::CClassAction<T, void, Args...>>* CreateGameJob(eGameJobType jobType, T* pObj, Func pFunc, Args... args)
	{
		using ActionType = ng::CClassAction<T, void, Args...>;
		auto pJob = NG_NEW(GameJobUtil::_GetGameJobMemAlloc()) CGameJobAction<ActionType>(ActionType(pObj, pFunc), args...);

		if(_AddGameJob(jobType, pJob)) {
			return pJob;
		}

		return nullptr;
	}

}	// namespace GameJobUtil
}	// namespace app

#endif	// __APP_GAME_JOB_UTIL_H__
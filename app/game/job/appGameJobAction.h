/*!
* @file		appGameJobAction.h
* @brief	ゲームジョブ アクション実行
* @date		2020-07-18
* @author	s.fukami
*/

#ifndef __APP_GAME_JOB_ACTION_H__
#define __APP_GAME_JOB_ACTION_H__

#include "appGameJob.h"
#include "ngLibCore/action/ngAction.h"

namespace app
{
	/*!
	* @brief					ゲームジョブ アクション実行
	*/
	template <class Action>
	class CGameJobAction : public CGameJob
	{
	public:
		using FuncType = typename Action::FuncType;	//!< 関数の型
		using ArgsType = typename Action::ArgsType;	//!< 引数の型

	public:
		/*!
		* @brief					コンストラクタ
		* @param action				アクション
		*/
		CGameJobAction(Action&& action);

		/*!
		* @brief					コンストラクタ
		* @param action				アクション
		* @param args				引数
		*/
		CGameJobAction(Action&& action, ArgsType&& args);

		/*!
		* @brief					デストラクタ
		*/
		~CGameJobAction();

		/*!
		* @brief					ジョブ実行
		*/
		void Execute();

	private:
		Action m_action;	//!< アクション
		ArgsType m_args;	//!< 引数
	};

	template <class Action>
	CGameJobAction<Action>::CGameJobAction(Action&& action)
		: m_action(action)
	{
	}

	template <class Action>
	CGameJobAction<Action>::CGameJobAction(Action&& action, ArgsType&& args)
		: m_action(action)
		, m_args(args)
	{
	}

	template <class Action>
	CGameJobAction<Action>::~CGameJobAction()
	{
	}

	template <class Action>
	void CGameJobAction<Action>::Execute()
	{
		m_action(std::move(m_args));
	}

}	// namespace app

#endif	// __APP_GAME_JOB_ACTION_H__
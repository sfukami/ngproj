/*!
* @file		ngStateMachine.h
* @brief	ステートマシン
* @date		2020-07-18
* @author	s.fukami
*/

#ifndef __NG_APP_STATE_MACHINE_H__
#define __NG_APP_STATE_MACHINE_H__

#include "ngLibCore/container/array/ngFixedArray.h"
#include "ngLibCore/action/ngAction.h"

namespace ng
{
	/*!
	* @brief					ステートマシン
	*/
	template <typename State, State Num, typename Process>
	class NG_DECL CStateMachine
	{
	public:
		/*!
		* @brief					コンストラクタ
		*/
		CStateMachine();

		/*!
		* @brief					コンストラクタ
		* @param defaultState		デフォルトステート
		*/
		explicit CStateMachine(State defaultState);

		/*!
		* @brief					デストラクタ
		*/
		~CStateMachine();

		/*!
		* @brief					ステート設定
		* @param process			ステート処理
		*/
		void SetState(State state, const Process&& process);

		/*!
		* @brief					ステート切り替え
		*/
		void ChangeState(State state);

		/*!
		* @brief					ステート処理実行
		*/
		void Execute();

	private:
		State m_curState;	//!< 現在のステート
		CFixedArray<Process, static_cast<u32>(Num)> m_procArr;	//!< ステート処理の配列
	};

	template <typename State, State Num, typename Process>
	CStateMachine<State, Num, Process>::CStateMachine()
		: m_curState(State())
	{
	}

	template <typename State, State Num, typename Process>
	CStateMachine<State, Num, Process>::CStateMachine(State defaultState)
		: m_curState(defaultState)
	{
	}

	template <typename State, State Num, typename Process>
	CStateMachine<State, Num, Process>::~CStateMachine()
	{
	}

	template <typename State, State Num, typename Process>
	void CStateMachine<State, Num, Process>::SetState(State state, const Process&& process)
	{
		m_procArr[static_cast<u32>(state)] = std::move(process);
	}

	template <typename State, State Num, typename Process>
	void CStateMachine<State, Num, Process>::ChangeState(State state)
	{
		m_curState = state;
	}

	template <typename State, State Num, typename Process>
	void CStateMachine<State, Num, Process>::Execute()
	{
		m_procArr[static_cast<u32>(m_curState)]();
	}

	/*!
	* @brief					ステートマシン クラス用
	*/
	template <class T, typename State, State Num, typename Process = CClassAction<T>>
	class NG_DECL CClassStateMachine : public CStateMachine<State, Num, Process>
	{
	public:
		using BaseType = CStateMachine<State, Num, Process>;	//!< 基底クラス
		using BaseType::SetState;
		
	public:
		/*!
		* @brief					コンストラクタ
		* @param pObj				呼び出し元のオブジェクト
		*/
		explicit CClassStateMachine(T* pObj);

		/*!
		* @brief					コンストラクタ
		* @param pObj				呼び出し元のオブジェクト
		* @param defaultState		デフォルトステート
		*/
		CClassStateMachine(T* pObj, State defaultState);

		/*!
		* @brief					デストラクタ
		*/
		~CClassStateMachine();

		/*!
		* @brief					ステート設定
		* @param pFunc				メンバ関数ポインタ
		*/
		void SetState(State state, typename Process::FuncType pFunc);

	private:
		T* m_pObj;	//!< 呼び出し元のオブジェクト
	};

	template <class T, typename State, State Num, typename Process>
	CClassStateMachine<T, State, Num, Process>::CClassStateMachine(T* pObj)
		: m_pObj(pObj)
	{
	}

	template <class T, typename State, State Num, typename Process>
	CClassStateMachine<T, State, Num, Process>::CClassStateMachine(T* pObj, State defaultState)
		: BaseType(defaultState)
		, m_pObj(pObj)
	{
	}

	template <class T, typename State, State Num, typename Process>
	CClassStateMachine<T, State, Num, Process>::~CClassStateMachine()
	{
	}

	template <class T, typename State, State Num, typename Process>
	void CClassStateMachine<T, State, Num, Process>::SetState(State state, typename Process::FuncType pFunc)
	{
		SetState(state, Process(m_pObj, pFunc));
	}

}	// namespace ng

#endif	//__NG_APP_STATE_MACHINE_H__
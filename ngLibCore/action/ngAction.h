/*!
* @file		ngAction.h
* @brief	アクション
* @date		2020-07-18
* @author	s.fukami
*/

#ifndef __NG_CORE_ACTION_H__
#define __NG_CORE_ACTION_H__

#include <tuple>
#include "../tuple/ngTupleArgs.h"

namespace ng
{
	/*!
	* @brief					アクション
	* @tparam Ret				戻り値
	* @tparam Args...			引数
	*/
	template <typename Ret = void, typename... Args>
	class NG_DECL CAction
	{
	public:
		using FuncType = Ret(*)(Args...);	//!< 関数の型
		using ArgsType = typename std::tuple<Args...>;	//!< 引数のタプル型

	public:
		/*!
		* @brief					コンストラクタ
		*/
		CAction()
			: m_pFunc(nullptr)
		{ }

		/*!
		* @brief					コンストラクタ
		* @param pFunc				関数ポインタ
		*/
		CAction(FuncType pFunc)
			: m_pFunc(pFunc)
		{ }

		/*!
		* @brief					実行
		* @param args				引数
		*/
		Ret operator()(Args... args)
		{
			NG_ASSERT_NOT_NULL(m_pFunc);

			return (*m_pFunc)(args...);
		}

		/*!
		* @brief					実行
		* @param args				引数
		*/
		Ret operator()(std::tuple<Args...>&& args)
		{
			return CallFunc(*this, args);
		}

	private:
		FuncType m_pFunc;	//!< 関数ポインタ
	};

	/*!
	* @brief					アクション（クラス版）
	* @tparam T					呼び出し元のクラス
	* @tparam Ret				戻り値
	* @tparam Args...			引数
	*/
	template <class T, typename Ret = void, typename... Args>
	class NG_DECL CClassAction
	{
	public:
		using ObjType = T;	//!< オブジェクトの型
		using FuncType = Ret(ObjType::*)(Args...);	//!< 関数の型
		using ArgsType = typename std::tuple<Args...>;	//!< 引数のタプル型

	public:
		/*!
		* @brief					コンストラクタ
		*/
		CClassAction()
			: m_pObj(nullptr), m_pFunc(nullptr)
		{ }

		/*!
		* @brief					コンストラクタ
		* @param pObj				呼び出し元のオブジェクト
		* @param pFunc				メンバ関数ポインタ
		*/
		CClassAction(ObjType* pObj, FuncType pFunc)
			: m_pObj(pObj), m_pFunc(pFunc)
		{ }

		/*!
		* @brief					実行
		* @param args				引数
		*/
		Ret operator()(Args... args)
		{
			NG_ASSERT_NOT_NULL(m_pObj);
			NG_ASSERT_NOT_NULL(m_pFunc);

			return (m_pObj->*m_pFunc)(args...);
		}

		/*!
		* @brief					実行
		* @param args				引数
		*/
		Ret operator()(std::tuple<Args...>&& args)
		{
			return CallFunc(*this, args);
		}

	private:
		ObjType* m_pObj;	//!< 呼び出し元のオブジェクト
		FuncType m_pFunc;	//!< メンバ関数ポインタ
	};

}	// namespace ng

#endif	//__NG_CORE_ACTION_H__
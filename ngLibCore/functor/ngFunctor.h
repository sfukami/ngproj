/*!
* @file		ngFunctor.h
* @brief	ファンクタ
* @date		2016-12-08
* @author	s.fukami
*/

#ifndef __NG_CORE_FUNCTOR_H__
#define __NG_CORE_FUNCTOR_H__

#include "ngLibCore/common/type/ngTypeList.h"

namespace ng
{
	/*!
	* @brief					ファンクタ インターフェース
	*/
	template <typename Ret, typename Params, typename TypeNum = typename Params::TypeNum>
	class IFunctor
	{ };

	/*!
	* @brief					ファンクタ インターフェース
	* 							パラメータ0
	*/
	template <typename Ret, typename Params>
	class IFunctor<Ret, Params, TypeNum0>
	{
	public:
		typedef Ret RetType;
		typedef Params ParamsType;

	public:
		IFunctor() { }
		virtual ~IFunctor() { }

		/*! 登録関数実行 パラメータ0 */
		virtual RetType operator()() = 0;
	};

	/*!
	* @brief					ファンクタ インターフェース
	* 							パラメータ1
	*/
	template <typename Ret, typename Params>
	class IFunctor<Ret, Params, TypeNum1>
	{
	public:
		typedef Ret RetType;
		typedef Params ParamsType;
		typedef typename Params::T1 P1;

	public:
		IFunctor() { }
		virtual ~IFunctor() { }

		/*! 登録関数実行 パラメータ1 */
		virtual RetType operator()(P1) = 0;
	};

	/*!
	* @brief					ファンクタ インターフェース
	* 							パラメータ2
	*/
	template <typename Ret, typename Params>
	class IFunctor<Ret, Params, TypeNum2>
	{
	public:
		typedef Ret RetType;
		typedef Params ParamsType;
		typedef typename Params::T1 P1;
		typedef typename Params::T2 P2;

	public:
		IFunctor() { }
		virtual ~IFunctor() { }

		/*! 登録関数実行 パラメータ2 */
		virtual RetType operator()(P1, P2) = 0;
	};

	/*!
	* @brief					ファンクタ インターフェース
	* 							パラメータ3
	*/
	template <typename Ret, typename Params>
	class IFunctor<Ret, Params, TypeNum3>
	{
	public:
		typedef Ret RetType;
		typedef Params ParamsType;
		typedef typename Params::T1 P1;
		typedef typename Params::T2 P2;
		typedef typename Params::T3 P3;

	public:
		IFunctor() { }
		virtual ~IFunctor() { }

		/*! 登録関数実行 パラメータ3 */
		virtual RetType operator()(P1, P2, P3) = 0;
	};

	/*!
	* @brief					ファンクタ インターフェース
	* 							パラメータ4
	*/
	template <typename Ret, typename Params>
	class IFunctor<Ret, Params, TypeNum4>
	{
	public:
		typedef Ret RetType;
		typedef Params ParamsType;
		typedef typename Params::T1 P1;
		typedef typename Params::T2 P2;
		typedef typename Params::T3 P3;
		typedef typename Params::T4 P4;

	public:
		IFunctor() { }
		virtual ~IFunctor() { }

		/*! 登録関数実行 パラメータ4 */
		virtual RetType operator()(P1, P2, P3, P4) = 0;
	};

	/*!
	* @brief					ファンクタ インターフェース
	* 							パラメータ5
	*/
	template <typename Ret, typename Params>
	class IFunctor<Ret, Params, TypeNum5>
	{
	public:
		typedef Ret RetType;
		typedef Params ParamsType;
		typedef typename Params::T1 P1;
		typedef typename Params::T2 P2;
		typedef typename Params::T3 P3;
		typedef typename Params::T4 P4;
		typedef typename Params::T5 P5;

	public:
		IFunctor() { }
		virtual ~IFunctor() { }

		/*! 登録関数実行 パラメータ5 */
		virtual RetType operator()(P1, P2, P3, P4, P5) = 0;
	};

	/*!
	* @brief					ファンクタ インターフェース
	* 							パラメータ6
	*/
	template <typename Ret, typename Params>
	class IFunctor<Ret, Params, TypeNum6>
	{
	public:
		typedef Ret RetType;
		typedef Params ParamsType;
		typedef typename Params::T1 P1;
		typedef typename Params::T2 P2;
		typedef typename Params::T3 P3;
		typedef typename Params::T4 P4;
		typedef typename Params::T5 P5;
		typedef typename Params::T6 P6;

	public:
		IFunctor() { }
		virtual ~IFunctor() { }

		/*! 登録関数実行 パラメータ6 */
		virtual RetType operator()(P1, P2, P3, P4, P5, P6) = 0;
	};

	/*!
	* @brief					ファンクタ インターフェース
	* 							パラメータ7
	*/
	template <typename Ret, typename Params>
	class IFunctor<Ret, Params, TypeNum7>
	{
	public:
		typedef Ret RetType;
		typedef Params ParamsType;
		typedef typename Params::T1 P1;
		typedef typename Params::T2 P2;
		typedef typename Params::T3 P3;
		typedef typename Params::T4 P4;
		typedef typename Params::T5 P5;
		typedef typename Params::T6 P6;
		typedef typename Params::T7 P7;

	public:
		IFunctor() { }
		virtual ~IFunctor() { }

		/*! 登録関数実行 パラメータ7 */
		virtual RetType operator()(P1, P2, P3, P4, P5, P6, P7) = 0;
	};

	/*!
	* @brief					ファンクタ インターフェース
	* 							パラメータ8
	*/
	template <typename Ret, typename Params>
	class IFunctor<Ret, Params, TypeNum8>
	{
	public:
		typedef Ret RetType;
		typedef Params ParamsType;
		typedef typename Params::T1 P1;
		typedef typename Params::T2 P2;
		typedef typename Params::T3 P3;
		typedef typename Params::T4 P4;
		typedef typename Params::T5 P5;
		typedef typename Params::T6 P6;
		typedef typename Params::T7 P7;
		typedef typename Params::T8 P8;

	public:
		IFunctor() { }
		virtual ~IFunctor() { }

		/*! 登録関数実行 パラメータ8 */
		virtual RetType operator()(P1, P2, P3, P4, P5, P6, P7, P8) = 0;
	};

	/*!
	* @brief					ファンクタ（クラスメソッド用）
	* @tparam Obj				呼び出し元のオブジェクト
	* @tparam Ret				戻り値
	* @tparam Param				引数リスト
	*/
	template <class Obj, typename Ret, typename Params>
	class NG_DECL CClassFunctor : public IFunctor<Ret, Params>
	{
	public:
		typedef Obj ObjType;
		typedef Ret RetType;
		typedef typename Params::T1 P1;
		typedef typename Params::T2 P2;
		typedef typename Params::T3 P3;
		typedef typename Params::T4 P4;
		typedef typename Params::T5 P5;
		typedef typename Params::T6 P6;
		typedef typename Params::T7 P7;
		typedef typename Params::T8 P8;

		/*! メンバ関数型解決 */
		template <typename TypeNum = typename Params::TypeNum>
		struct FuncSolver
		{ };
		/*! メンバ関数型解決 パラメータ0 */
		template <>
		struct FuncSolver<TypeNum0>
		{
			typedef RetType(ObjType::*FuncType)();
		};
		/*! メンバ関数型解決 パラメータ1 */
		template <>
		struct FuncSolver<TypeNum1>
		{
			typedef RetType(ObjType::*FuncType)(P1);
		};
		/*! メンバ関数型解決 パラメータ2 */
		template <>
		struct FuncSolver<TypeNum2>
		{
			typedef RetType(ObjType::*FuncType)(P1, P2);
		};
		/*! メンバ関数型解決 パラメータ3 */
		template <>
		struct FuncSolver<TypeNum3>
		{
			typedef RetType(ObjType::*FuncType)(P1, P2, P3);
		};
		/*! メンバ関数型解決 パラメータ4 */
		template <>
		struct FuncSolver<TypeNum4>
		{
			typedef RetType(ObjType::*FuncType)(P1, P2, P3, P4);
		};
		/*! メンバ関数型解決 パラメータ5 */
		template <>
		struct FuncSolver<TypeNum5>
		{
			typedef RetType(ObjType::*FuncType)(P1, P2, P3, P4, P5);
		};
		/*! メンバ関数型解決 パラメータ6 */
		template <>
		struct FuncSolver<TypeNum6>
		{
			typedef RetType(ObjType::*FuncType)(P1, P2, P3, P4, P5, P6);
		};
		/*! メンバ関数型解決 パラメータ7 */
		template <>
		struct FuncSolver<TypeNum7>
		{
			typedef RetType(ObjType::*FuncType)(P1, P2, P3, P4, P5, P6, P7);
		};
		/*! メンバ関数型解決 パラメータ8 */
		template <>
		struct FuncSolver<TypeNum8>
		{
			typedef RetType(ObjType::*FuncType)(P1, P2, P3, P4, P5, P6, P7, P8);
		};
		typedef typename FuncSolver<typename Params::TypeNum>::FuncType FuncType;

	public:
		/*!
		* @brief					コンストラクタ
		* @param pObj				呼び出し元のオブジェクト
		* @param pFunc				呼び出すメンバ関数
		*/
		CClassFunctor(ObjType* pObj, FuncType pFunc)
			: m_pObj(pObj), m_pFunc(pFunc)
		{ }

		/*!
		* @brief					コンストラクタ
		* @param pFunc				呼び出すメンバ関数
		* @attention				関数実行前に、SetObj()関数で呼び出し元のオブジェクトを設定する必要がある
		*/
		explicit CClassFunctor(FuncType pFunc)
			: m_pObj(nullptr), m_pFunc(pFunc)
		{ }

		#define _CLASSFUNCTOR_POINTER_ASSERT() \
			{ \
				NG_ASSERT_NOT_NULL(m_pObj); \
				NG_ASSERT_NOT_NULL(m_pFunc); \
			}

		/*! 登録関数実行 パラメータ0 */
		RetType operator()()
		{
			_CLASSFUNCTOR_POINTER_ASSERT();
			(m_pObj->*m_pFunc)();
		}
		/*! 登録関数実行 パラメータ1 */
		RetType operator()(P1 p1)
		{
			_CLASSFUNCTOR_POINTER_ASSERT();
			(m_pObj->*m_pFunc)(p1);
		}
		/*! 登録関数実行 パラメータ2 */
		RetType operator()(P1 p1, P2 p2)
		{
			_CLASSFUNCTOR_POINTER_ASSERT();
			(m_pObj->*m_pFunc)(p1, p2);
		}
		/*! 登録関数実行 パラメータ3 */
		RetType operator()(P1 p1, P2 p2, P3 p3)
		{
			_CLASSFUNCTOR_POINTER_ASSERT();
			(m_pObj->*m_pFunc)(p1, p2, p3);
		}
		/*! 登録関数実行 パラメータ4 */
		RetType operator()(P1 p1, P2 p2, P3 p3, P4 p4)
		{
			_CLASSFUNCTOR_POINTER_ASSERT();
			(m_pObj->*m_pFunc)(p1, p2, p3, p4);
		}
		/*! 登録関数実行 パラメータ5 */
		RetType operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
		{
			_CLASSFUNCTOR_POINTER_ASSERT();
			(m_pObj->*m_pFunc)(p1, p2, p3, p4, p5);
		}
		/*! 登録関数実行 パラメータ6 */
		RetType operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6)
		{
			_CLASSFUNCTOR_POINTER_ASSERT();
			(m_pObj->*m_pFunc)(p1, p2, p3, p4, p5, p6);
		}
		/*! 登録関数実行 パラメータ7 */
		RetType operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7)
		{
			_CLASSFUNCTOR_POINTER_ASSERT();
			(m_pObj->*m_pFunc)(p1, p2, p3, p4, p5, p6, p7);
		}
		/*! 登録関数実行 パラメータ8 */
		RetType operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8)
		{
			_CLASSFUNCTOR_POINTER_ASSERT();
			(m_pObj->*m_pFunc)(p1, p2, p3, p4, p5, p6, p7, p8);
		}

		#undef _CLASSFUNCTOR_POINTER_ASSERT

		/*! 呼び出し元のオブジェクトを設定 */
		void SetObj(ObjType* pObj) { m_pObj = pObj; }

		/*! 呼び出すメンバ関数を設定 */
		void SetFunc(FuncType pFunc) { m_pFunc = pFunc; }

	private:
		ObjType* m_pObj;	//!< 呼び出し元のオブジェクト
		FuncType m_pFunc;	//!< 呼び出すメンバ関数
	};

	/*!
	* @brief					ファンクタ
	* @tparam Ret				戻り値
	* @tparam Param				引数リスト
	*/
	template <typename Ret, typename Params>
	class NG_DECL CFunctor : public IFunctor<Ret, Params>
	{
	public:
		typedef Ret RetType;
		typedef typename Params::T1 P1;
		typedef typename Params::T2 P2;
		typedef typename Params::T3 P3;
		typedef typename Params::T4 P4;
		typedef typename Params::T5 P5;
		typedef typename Params::T6 P6;
		typedef typename Params::T7 P7;
		typedef typename Params::T8 P8;

		/*! 関数型解決 */
		template <typename TypeNum = typename Params::TypeNum>
		struct FuncSolver
		{ };
		/*! 関数型解決 パラメータ0 */
		template <>
		struct FuncSolver<TypeNum0>
		{
			typedef RetType(*FuncType)();
		};
		/*! 関数型解決 パラメータ1 */
		template <>
		struct FuncSolver<TypeNum1>
		{
			typedef RetType(*FuncType)(P1);
		};
		/*! 関数型解決 パラメータ2 */
		template <>
		struct FuncSolver<TypeNum2>
		{
			typedef RetType(*FuncType)(P1, P2);
		};
		/*! 関数型解決 パラメータ3 */
		template <>
		struct FuncSolver<TypeNum3>
		{
			typedef RetType(*FuncType)(P1, P2, P3);
		};
		/*! 関数型解決 パラメータ4 */
		template <>
		struct FuncSolver<TypeNum4>
		{
			typedef RetType(*FuncType)(P1, P2, P3, P4);
		};
		/*! 関数型解決 パラメータ5 */
		template <>
		struct FuncSolver<TypeNum5>
		{
			typedef RetType(*FuncType)(P1, P2, P3, P4, P5);
		};
		/*! 関数型解決 パラメータ6 */
		template <>
		struct FuncSolver<TypeNum6>
		{
			typedef RetType(*FuncType)(P1, P2, P3, P4, P5, P6);
		};
		/*! 関数型解決 パラメータ7 */
		template <>
		struct FuncSolver<TypeNum7>
		{
			typedef RetType(*FuncType)(P1, P2, P3, P4, P5, P6, P7);
		};
		/*! 関数型解決 パラメータ8 */
		template <>
		struct FuncSolver<TypeNum8>
		{
			typedef RetType(*FuncType)(P1, P2, P3, P4, P5, P6, P7, P8);
		};
		typedef typename FuncSolver<typename Params::TypeNum>::FuncType FuncType;

	public:
		/*!
		* @brief					コンストラクタ
		* @param pFunc				呼び出す関数
		*/
		explicit CFunctor(FuncType pFunc)
			: m_pFunc(pFunc)
		{ }

		#define _FUNCTOR_POINTER_ASSERT() \
			{ \
				NG_ASSERT_NOT_NULL(m_pFunc); \
			}

		/*! 登録関数実行 パラメータ0 */
		RetType operator()()
		{
			_FUNCTOR_POINTER_ASSERT();
			(*m_pFunc)();
		}
		/*! 登録関数実行 パラメータ1 */
		RetType operator()(P1 p1)
		{
			_FUNCTOR_POINTER_ASSERT();
			(*m_pFunc)(p1);
		}
		/*! 登録関数実行 パラメータ2 */
		RetType operator()(P1 p1, P2 p2)
		{
			_FUNCTOR_POINTER_ASSERT();
			(*m_pFunc)(p1, p2);
		}
		/*! 登録関数実行 パラメータ3 */
		RetType operator()(P1 p1, P2 p2, P3 p3)
		{
			_FUNCTOR_POINTER_ASSERT();
			(*m_pFunc)(p1, p2, p3);
		}
		/*! 登録関数実行 パラメータ4 */
		RetType operator()(P1 p1, P2 p2, P3 p3, P4 p4)
		{
			_FUNCTOR_POINTER_ASSERT();
			(*m_pFunc)(p1, p2, p3, p4);
		}
		/*! 登録関数実行 パラメータ5 */
		RetType operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
		{
			_FUNCTOR_POINTER_ASSERT();
			(*m_pFunc)(p1, p2, p3, p4, p5);
		}
		/*! 登録関数実行 パラメータ6 */
		RetType operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6)
		{
			_FUNCTOR_POINTER_ASSERT();
			(*m_pFunc)(p1, p2, p3, p4, p5, p6);
		}
		/*! 登録関数実行 パラメータ7 */
		RetType operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7)
		{
			_FUNCTOR_POINTER_ASSERT();
			(*m_pFunc)(p1, p2, p3, p4, p5, p6, p7);
		}
		/*! 登録関数実行 パラメータ8 */
		RetType operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8)
		{
			_FUNCTOR_POINTER_ASSERT();
			(*m_pFunc)(p1, p2, p3, p4, p5, p6, p7, p8);
		}

		#undef _FUNCTOR_POINTER_ASSERT
		
		/*! 呼び出す関数を設定 */
		void SetFunc(FuncType pFunc) { m_pFunc = pFunc; }

	private:
		FuncType m_pFunc;	//!< 呼び出す関数
	};

}	// namespace ng

#endif	// __NG_CORE_FUNCTOR_H__
/*!
* @file		ngTupleArgs.h
* @brief	std::tuple の引数展開
* @date		2020-07-18
* @author	s.fukami
*/

#ifndef __NG_CORE_TUPLE_ARGS_H__
#define __NG_CORE_TUPLE_ARGS_H__

#include <type_traits>

namespace ng
{
	/*!
	* @brief					std::tuple引数関数の呼び出し実装
	*/
	template <typename Func, typename Tuple, bool Done, int Total, int... N>
	struct NG_DECL CallFuncImpl
	{
		static void CallFunc(Func& func, Tuple&& args)
		{
			CallFuncImpl<Func, Tuple, Total == 1 + sizeof...(N), Total, N..., sizeof...(N)>
				::CallFunc(func, std::forward<Tuple>(args));
		}
	};
	template <typename Func, typename Tuple, int Total, int... N>
	struct NG_DECL CallFuncImpl<Func, Tuple, true, Total, N...>
	{
		static void CallFunc(Func& func, Tuple&& args)
		{
			func(std::get<N>(std::forward<Tuple>(args))...);
		}
	};

	/*!
	* @brief					std::tuple引数関数の呼び出し
	*/
	template <typename Func, typename Tuple>
	void CallFunc(Func& func, Tuple&& args)
	{
		typedef typename std::decay<Tuple>::type TupleType;
		CallFuncImpl<Func, Tuple, 0 == std::tuple_size<TupleType>::value, std::tuple_size<TupleType>::value>
			::CallFunc(func, std::forward<Tuple>(args));
	}

}	// namespace ng

#endif	// __NG_CORE_TUPLE_ARGS_H__
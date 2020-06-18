/*!
* @file		ngTypeUtil.h
* @brief	型ユーティリティ
* @date 	2015-11-04
* @author 	s.fukami
*/

#ifndef __NG_CORE_TYPE_UTIL_H__
#define __NG_CORE_TYPE_UTIL_H__

namespace ng
{
	/*!
	* 型解決テンプレート 実体用
	*/
	template <class T>
	struct TypeSolver
	{
		typedef T RealType;
		typedef T* PtrType;
		typedef T& RefType;
	};

	/*!
	* 型解決テンプレート ポインタ用
	*/
	template <class T>
	struct TypeSolver<T*>
	{
		typedef T RealType;
		typedef T* PtrType;
		typedef T& RefType;
	};
	
}	// namespace ng

#endif	// __NG_CORE_TYPE_UTIL_H__

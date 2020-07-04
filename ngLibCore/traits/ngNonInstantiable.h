/*!
* @file		ngNonInstantiable.h
* @brief	インスタンス化禁止
* @date		2020-07-03
* @author	s.fukami
*/

#ifndef __NG_CORE_NON_INSTANTIABLE_H__
#define __NG_CORE_NON_INSTANTIABLE_H__

namespace ng
{
	/*!
	* @brief					インスタンス化禁止
	* @note						継承して使用する
	*/
	class NG_DECL CNonInstantiable
	{
	public:
		CNonInstantiable() = delete;
		CNonInstantiable(const CNonInstantiable&) = delete;
		CNonInstantiable(CNonInstantiable&&) = delete;
	};

}	// namespace ng

#endif	// __NG_CORE_NON_INSTANTIABLE_H__
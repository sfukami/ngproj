/*!
* @file		ngNonCopyable.h
* @brief	コピー禁止
* @date		2014-07-07
* @author	s.fukami
*/
// 更新履歴
//	2013-05-25
//	テンプレートクラスに変更（CRTP）
//	多重継承の際の「空の基底クラスに対する最適化」を行うため

#ifndef __NG_CORE_NONCOPYABLE_H__
#define __NG_CORE_NONCOPYABLE_H__

namespace ng
{
	/*!
	* @brief					派生クラスの代入・コピー禁止クラス
	* @note						継承して使用する。継承はprivateで行うこと
	* @attention				派生クラスでコピーコンストラクタ等を実装することでコピーが可能になるので注意
	*/
	template <class T>
	class NG_DECL CNonCopyable
	{
	protected:
		/*!
		* @brief					コンストラクタ
		* @note						このクラス単体では使用しないのでprotected
		*/
		CNonCopyable() { }

		/*!
		* @brief					デストラクタ
		* @node						ポリモーフィズムは禁止するのでprotected。virtualも不要
		*/
		~CNonCopyable() { }

	#if NG_CHECK_CPLUSPLUS_COMPILER_SUPPORT(11)
		/*!
		* @brief					コピーコンストラクタ
		* @note						呼び出し禁止
		*/
		CNonCopyable(const CNonCopyable&) = delete;

		/*!
		* @brief					代入演算子のオーバーロード
		* @note						呼び出し禁止
		*/
		CNonCopyable& operator=(const CNonCopyable&) = delete;
	#else
	private:
		/*!
		* @brief					コピーコンストラクタ
		* @note						呼び出し禁止のためprivate宣言
		*							実装不要
		*/
		CNonCopyable(const CNonCopyable&);

		/*!
		* @brief					代入演算子のオーバーロード
		* @note						呼び出し禁止のためprivate宣言
		*							実装不要
		*/
		CNonCopyable& operator=(const CNonCopyable&);
	#endif
	};

}	// namespace ng

#endif	// __NG_CORE_NONCOPYABLE_H__
/*!
* @file		ngSingleton.h
* @brief	シングルトン
* @date		2015-02-20
* @author	s.fukami
*/

#ifndef __NG_CORE_SINGLETON_H__
#define __NG_CORE_SINGLETON_H__

#include "ngLibCore/common/debug/ngDbgMacro.h"
#include "ngNonCopyable.h"

/*!
* シングルトンクラス用定義
*/
#define NG_SINGLETON(_class)	friend class ng::CSingleton<_class>; \
								private: \
								static _class* _createInstance(); \
								static void _destroyInstance(_class* pInst);
								
namespace ng
{
	/*!
	* @brief					シングルトンクラス
	* @tparam T					派生クラス（CRTP）
	* @attention				派生クラスのコンストラクタをprivate指定すること
	*							派生クラスにて次のメソッドを実装する必要がある
	*							static T* _createInstance();		シングルトンインスタンスの生成を行う
	*							static void _destroyInstance(T*);	シングルトンインスタンスの破棄を行う
	*/
	template <class T>
	class NG_DECL CSingleton : private CNonCopyable<CSingleton<T> >
	{
	protected:
		/*!
		* @brief					コンストラクタ
		* @note						このクラス単体では使用しないのでprotected
		*/
		CSingleton() { }

		/*!
		* @brief					デストラクタ
		* @note						ポリモーフィズムは禁止するのでprotected
		* 							及び、非仮想
		*/
		~CSingleton() { }

	public:
		/*!
		* @brief					シングルトンインスタンス生成
		*/
		static void CreateInstance();

		/*!
		* @brief					シングルトンインスタンス破棄
		*/
		static void DestroyInstance();

		/*!
		* @brief					シングルトンインスタンス取得
		*/
		static T& GetInstance();

	private:
		static T* m_pInstance;	//!< シングルトンインスタンスへの参照
	};

	template <class T>
	T* CSingleton<T>::m_pInstance = nullptr;

	/*!
	* @brief					シングルトンインスタンス生成
	*/
	template <class T>
	void CSingleton<T>::CreateInstance()
	{
		if( ! m_pInstance)
		{
			// インスタンス生成
			m_pInstance = T::_createInstance();
			NG_ASSERT(m_pInstance);
		}
	}

	/*!
	* @brief					シングルトンインスタンス破棄
	*/
	template <class T>
	void CSingleton<T>::DestroyInstance()
	{
		// インスタンス破棄
		T::_destroyInstance(m_pInstance);
		m_pInstance = nullptr;
	}

	/*!
	* @brief					シングルトンインスタンス取得
	*/
	template <class T>
	T& CSingleton<T>::GetInstance()
	{
		NG_ASSERT(m_pInstance);
		return *m_pInstance;
	}

}	// namespace ng

#endif	// __NG_CORE_SINGLETON_H__
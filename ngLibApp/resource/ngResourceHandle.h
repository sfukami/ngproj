/*!
* @file		ngResourceHandle.h
* @brief	リソースハンドル
* @date		2020-07-20
* @author	s.fukami
*/

#ifndef __NG_APP_RESOURCE_HANDLE_H__
#define __NG_APP_RESOURCE_HANDLE_H__

#include "ngResourceHandleIf.h"
#include "ngLibCore/memory/pointer/ngSharedPtr.h"
#include "ngLibCore/memory/pointer/ngWeakPtr.h"

namespace ng
{
	class IResource;
}

namespace ng
{
	/*!
	* @brief					リソースハンドル
	*/
	template <class T>
	class NG_DECL CResourceHandle : public IResourceHandle
	{
	public:
		CResourceHandle();
		~CResourceHandle();

		/*!
		* @brief					リソース取得
		*/
		CWeakPtr<T> GetResource() const;

		/*!
		* @brief					解放
		*/
		void Release();

		/*! 有効か */
		bool IsValid() const;

	private:
		/*!
		* @brief					リソース設定
		*/
		void SetResource(CSharedPtr<IResource>& resPtr);

	private:
		CWeakPtr<T> m_resPtr;	//!< リソースへの参照
	};

	template <class T>
	CResourceHandle<T>::CResourceHandle()
	{
	}

	template <class T>
	CResourceHandle<T>::~CResourceHandle()
	{
	}

	template <class T>
	CWeakPtr<T> CResourceHandle<T>::GetResource() const
	{
		return m_resPtr;
	}

	template <class T>
	void CResourceHandle<T>::Release()
	{
		m_resPtr.reset();
	}

	template <class T>
	bool CResourceHandle<T>::IsValid() const
	{
		return (m_resPtr != nullptr);
	}

	template <class T>
	void CResourceHandle<T>::SetResource(CSharedPtr<IResource>& resPtr)
	{
		m_resPtr = CWeakPtr<T>(DynamicCast<T>(resPtr));
	}

}	// namespace ng

#endif	// __NG_APP_RESOURCE_HANDLE_H__
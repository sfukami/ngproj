/*!
* @file		ngResourceHandleIf.h
* @brief	リソースハンドル インターフェース
* @date		2020-07-22
* @author	s.fukami
*/

#ifndef __NG_APP_RESOURCE_HANDLE_IF_H__
#define __NG_APP_RESOURCE_HANDLE_IF_H__

namespace ng
{
	class IResource;
	template <class T> class CSharedPtr;
}

namespace ng
{
	/*!
	* @brief					リソースハンドル インターフェース
	*/
	class NG_DECL IResourceHandle
	{
		friend class CResourceManager;

	public:
		IResourceHandle() { }
		virtual ~IResourceHandle() { }

		/*!
		* @brief					解放
		*/
		virtual void Release() = 0;

		/*! 有効か */
		virtual bool IsValid() const = 0;

	private:
		/*!
		* @brief					リソース設定
		*/
		virtual void SetResource(CSharedPtr<IResource>& resPtr) = 0;
	};

}	// namespace ng

#endif	// __NG_APP_RESOURCE_HANDLE_IF_H__
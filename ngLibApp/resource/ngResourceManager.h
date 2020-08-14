/*!
* @file		ngResourceManager.h
* @brief	リソース管理
* @date		2020-07-20
* @author	s.fukami
*/

#ifndef __NG_APP_RESOURCE_MANAGER_H__
#define __NG_APP_RESOURCE_MANAGER_H__

#include "ngLibCore/memory/pointer/ngSharedPtr.h"
#include "ngLibCore/container/map/ngFixedHashMap.h"
#include "ngResourceHandle.h"

namespace ng
{
	class IMemoryAllocator;
	class IResource;
	class IResourceHandle;
}

namespace ng
{
	/*!
	* @brief					リソース管理
	*/
	class NG_DECL CResourceManager
	{
	public:
		CResourceManager();
		~CResourceManager();

		/*
		* @brief					初期化
		* @param alloc				使用するメモリアロケータ
		* @param resMax				リソース最大数
		* @return					NG エラーコード
		*/
		NG_ERRCODE Initialize(IMemoryAllocator& alloc, u32 resMax);

		/*!
		* @brief					終了処理
		*/
		void Finalize();

		/*!
		* @brief					リソース追加
		* @param pKey				キー
		* @param resPtr				追加するリソース
		* @param pHandle			格納先のリソースハンドル。ハンドルを取得しない場合は null
		* @return					成否
		*/
		bool Add(const char* pKey, CSharedPtr<IResource>& resPtr, IResourceHandle* pHandle = nullptr);

		/*!
		* @brief					リソース追加
		* @tparam T					リソースの型
		* @param pKey				キー
		* @param resPtr				追加するリソース
		* @param pHandle			格納先のリソースハンドル。ハンドルを取得しない場合は null
		* @return					成否
		*/
		template <class T>
		bool Add(const char* pKey, CSharedPtr<T>& resPtr, IResourceHandle* pHandle = nullptr);

		/*!
		* @brief					リソース取得
		* @param pKey				キー
		* @param handle				格納先のリソースハンドル
		* @return					成否
		* @note						取得に失敗した場合は警告を出力
		*/
		bool Get(const char* pKey, IResourceHandle& handle);

		/*!
		* @brief					リソース取得
		* @param pKey				キー
		* @param handle				格納先のリソースハンドル
		* @return					成否
		* @note						取得に失敗した場合でも警告を出力しない
		*/
		bool TryGet(const char* pKey, IResourceHandle& handle);

	private:
		/*! 初期化済みか */
		bool _isInit() const;

	private:
		CFixedHashMap<const char*, CSharedPtr<IResource>> m_resMap;	//!< リソース格納マップ

		bool m_isInit;	//!< 初期化済みか
	};

	template <class T>
	bool CResourceManager::Add(const char* pKey, CSharedPtr<T>& resPtr, IResourceHandle* pHandle)
	{
		auto p = ng::StaticCast<ng::IResource>(resPtr);
		return Add(pKey, p, pHandle);
	}

}	// namespace ng

#endif	// __NG_APP_RESOURCE_MANAGER_H__
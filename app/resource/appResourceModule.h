/*!
* @file		appResourceModule.h
* @brief	リソースモジュール
* @date		2020-07-22
* @author	s.fukami
*/

#ifndef __APP_RESOURCE_MODULE_H__
#define __APP_RESOURCE_MODULE_H__

#include "ngLibCore/traits/ngNonInstantiable.h"
#include "appResourceSystem.h"
#include "memory/appResourceMemoryType.h"

namespace ng
{
	class IResourceHandle;
}

namespace app
{
	/*!
	* @brief					リソースモジュール
	*/
	class CResourceModule : public ng::CNonInstantiable
	{
		friend class CApplication;

	public:
		/*!
		* @brief					ファイルからリソース読み込み
		* @param filePath			リソースファイルのパス
		* @param resName			リソース名（ファイルパスが一意の場合は不要）
		* @param resMemType			リソースメモリタイプ
		* @param pBuildParam		ビルドパラメータ
		* @param handle				格納先のリソースハンドル
		* @return					成否
		*/
		template <class T>
		static bool LoadResourceFromFile(
			const char* filePath, const char* resName, eResourceMemoryType resMemType, const void* pBuildParam, ng::IResourceHandle& handle
			);
		template <class T>
		static bool LoadResourceFromFile(
			const char* filePath, eResourceMemoryType resMemType, const void* pBuildParam, ng::IResourceHandle& handle
			);
		template <class T>
		static bool LoadResourceFromFile(
			const char* filePath, eResourceMemoryType resMemType, ng::IResourceHandle& handle
			);

		/*!
		* @brief					メモリからリソース読み込み
		* @param pData				リソースデータ
		* @param dataSize			リソースデータのサイズ
		* @param owner				リソースの所有者（ファイルパスなど一意のもの）
		* @param resName			リソース名（ファイルパスが一意の場合は不要）
		* @param resMemType			リソースメモリタイプ
		* @param pBuildParam		ビルドパラメータ
		* @param handle				格納先のリソースハンドル
		* @return					成否
		*/
		template <class T>
		static bool LoadResourceFromMemory(
			const void* pData, ng::u32 dataSize, const char* owner, const char* resName, eResourceMemoryType resMemType, const void* pBuildParam, ng::IResourceHandle& handle
			);
		template <class T>
		static bool LoadResourceFromMemory(
			const void* pData, ng::u32 dataSize, const char* owner, eResourceMemoryType resMemType, const void* pBuildParam, ng::IResourceHandle& handle
			);
		template <class T>
		static bool LoadResourceFromMemory(
			const void* pData, ng::u32 dataSize, const char* owner, eResourceMemoryType resMemType, ng::IResourceHandle& handle
			);

	private:
		/*! リソースシステムへの参照を設定 */
		static void SetResourceSystem(CResourceSystem* pResSys);

		/*! 有効か */
		static bool _isValid();

	private:
		static CResourceSystem* s_pResSys;	//!< リソースシステムへの参照
	};

	template <class T>
	bool CResourceModule::LoadResourceFromFile(
		const char* filePath, const char* resName, eResourceMemoryType resMemType, const void* pBuildParam, ng::IResourceHandle& handle
		)
	{
		if(!_isValid()) return false;

		return s_pResSys->LoadResource<T>(
			CResourceSystem::LoadParam(
				CResourceSystem::LoadParam::File(filePath), resName, resMemType, pBuildParam
				)
			, handle
			);
	}
	template <class T>
	bool CResourceModule::LoadResourceFromFile(
		const char* filePath, eResourceMemoryType resMemType, const void* pBuildParam, ng::IResourceHandle& handle
		)
	{
		return LoadResourceFromFile<T>(filePath, nullptr, resMemType, pBuildParam, handle);
	}
	template <class T>
	bool CResourceModule::LoadResourceFromFile(
		const char* filePath, eResourceMemoryType resMemType, ng::IResourceHandle& handle
		)
	{
		return LoadResourceFromFile<T>(filePath, nullptr, resMemType, nullptr, handle);
	}

	template <class T>
	bool CResourceModule::LoadResourceFromMemory(
		const void* pData, ng::u32 dataSize, const char* owner, const char* resName, eResourceMemoryType resMemType, const void* pBuildParam, ng::IResourceHandle& handle
		)
	{
		return s_pResSys->LoadResource<T>(
			CResourceSystem::LoadParam(
				CResourceSystem::LoadParam::Binary(pData, dataSize, owner), resName, resMemType, pBuildParam
				)
			, handle
			);
	}
	template <class T>
	bool CResourceModule::LoadResourceFromMemory(
		const void* pData, ng::u32 dataSize, const char* owner, eResourceMemoryType resMemType, const void* pBuildParam, ng::IResourceHandle& handle
		)
	{
		return LoadResourceFromMemory<T>(pData, dataSize, owner, nullptr, resMemType, pBuildParam, handle);
	}
	template <class T>
	bool CResourceModule::LoadResourceFromMemory(
		const void* pData, ng::u32 dataSize, const char* owner, eResourceMemoryType resMemType, ng::IResourceHandle& handle
		)
	{
		return LoadResourceFromMemory<T>(pData, dataSize, owner, nullptr, resMemType, nullptr, handle);
	}

}	// namespace app

#endif	// __APP_RESOURCE_MODULE_H__
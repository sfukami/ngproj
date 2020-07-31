/*!
* @file		appResourceSystem.h
* @brief	リソースシステム
* @date		2020-07-22
* @author	s.fukami
*/

#ifndef __APP_RESOURCE_SYSTEM_H__
#define __APP_RESOURCE_SYSTEM_H__

#include "ngLibApp/resource/ngResourceManager.h"
#include "memory/appResourceMemory.h"
#include "memory/appResourceMemoryType.h"

namespace ng
{
	class IMemoryAllocator;
	class IResourceHandle;
}

namespace app
{
	/*!
	* @brief					リソースシステム
	*/
	class CResourceSystem
	{
	public:
		CResourceSystem();
		~CResourceSystem();

		/*!
		* @brief					初期化
		* @param alloc				利用するメモリアロケータ
		* @param resMax				リソース最大数
		* @return					成否
		*/
		bool Initialize(ng::IMemoryAllocator& alloc, unsigned int resMax);

		/*!
		* @brief					終了処理
		*/
		void Finalize();

		/*!
		* @brief					リソース読み込み
		* @param fileName			ファイル名
		* @param resMemType			リソースメモリタイプ
		* @param pBuildParam		ビルドパラメータ
		* @param handle				格納先のリソースハンドル
		* @return					成否
		*/
		bool LoadResource(
			const char* fileName, eResourceMemoryType resMemType, const void* pBuildParam, ng::IResourceHandle& handle
			);

	private:
		/*! ファイル拡張子判定 */
		bool _checkExtTable(const char* ext, const char* pExtTable[], unsigned int tableSize) const;

		/*! リソース読み込み */
		template <class T>
		bool _loadResource(
			const char* fileName, ng::IMemoryAllocator& alloc, const void* pBuildParam, ng::IResourceHandle& handle
			);

		/*! ファイル読み込み */
		bool _loadFile(const char* fileName, void** ppFileData, ng::size_type* pFileSize);

		/*! リソース構築 */
		bool _buildResource(
			ng::CSharedPtr<ng::IResource>& resPtr, const void* pFileData, ng::size_type fileSize, const void* pBuildParam
			);

		/*! リソース追加 */
		bool _addResource(
			const char* fileName, ng::CSharedPtr<ng::IResource>& resPtr, ng::IResourceHandle& handle
			);

	private:
		CResourceMemory m_resMem;	//!< リソースメモリ
		ng::CResourceManager m_resMngr;	//!< リソース管理
	};

	template <class T>
	bool CResourceSystem::_loadResource(
		const char* fileName, ng::IMemoryAllocator& alloc, const void* pBuildParam, ng::IResourceHandle& handle
		)
	{
		void* pFileData = nullptr;
		ng::size_type fileSize = 0;

		// ファイル読み込み
		if(!_loadFile(fileName, &pFileData, &fileSize)) {
			return false;
		}

		// リソース生成 & 構築
		auto resPtr = ng::StaticCast<ng::IResource>(NG_MAKE_SHARED_PTR(T, alloc));
		bool result = _buildResource(resPtr, pFileData, fileSize, pBuildParam);

		if(result) {
			// リソース追加
			result = _addResource(fileName, resPtr, handle);
		}

		return result;
	}

}	// namespace app

#endif	//__APP_RESOURCE_SYSTEM_H__
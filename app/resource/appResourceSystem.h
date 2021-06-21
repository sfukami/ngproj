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
		static const ng::u32 ResKeyLength;	//!< リソースのキーの長さ

	public:
		/*! ロードパラメータ */
		struct LoadParam
		{
			struct File;
			struct Binary;
			LoadParam(const File& _file, const char* _resName, eResourceMemoryType _resMemType, const void* _pBuildParam = nullptr);
			LoadParam(const Binary& _binary, const char* _resName, eResourceMemoryType _resMemType, const void* _pBuildParam = nullptr);

			//! ファイル
			struct File
			{
				File();
				File(const File& _file);
				File(const char* _filePath);
				bool IsValid() const;

				const char* filePath;	//!< リソースファイルのパス
			} file;
			//! バイナリ
			struct Binary
			{
				Binary();
				Binary(const Binary& _binary);
				Binary(const void* _pData, ng::u32 _dataSize, const char* _owner);
				bool IsValid() const;

				const void* pData;		//!< リソースデータ
				ng::u32 dataSize;		//!< リソースデータのサイズ
				const char* owner;		//!< リソースの所有者（ファイルパスなど一意のもの）
			} binary;

			const char* resName;	//!< リソース名（ファイルパスが一意の場合は不要）
			eResourceMemoryType resMemType;	//!< リソースメモリタイプ
			const void* pBuildParam;	//!< ビルドパラメータ
		};

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
		* @param param				ロードパラメータ
		* @param handle				格納先のリソースハンドル
		* @return					成否
		*/
		template <class T>
		bool LoadResource(const LoadParam& param, ng::IResourceHandle& handle);

	private:
		/*! リソース取得 */
		bool _findResource(const LoadParam& param, ng::IResourceHandle& handle) const;
		/*! リソース読み込み */
		bool _loadResource(const LoadParam& param, ng::CSharedPtr<ng::IResource>& resPtr, ng::IResourceHandle& handle);
		/*! ファイル読み込み */
		bool _loadFile(const char* fileName, void** ppData, ng::size_type* pDataSize) const;
		/*! リソース登録 */
		bool _addResource(const LoadParam& param, ng::CSharedPtr<ng::IResource>& resPtr, ng::IResourceHandle& handle);
		/*! リソースキー生成 */
		bool _createResKey(const LoadParam& param, char* pDst) const;

	private:
		CResourceMemory m_resMem;	//!< リソースメモリ
		ng::CResourceManager m_resMngr;	//!< リソース管理
	};

	template <class T>
	bool CResourceSystem::LoadResource(const LoadParam& param, ng::IResourceHandle& handle)
	{
		// 既にリソースが存在する場合は、それを返却
		if(_findResource(param, handle)) {
			return true;
		}

		auto allocPtr = m_resMem.GetAllocator(param.resMemType);
		auto resPtr = ng::StaticCast<ng::IResource>(NG_MAKE_SHARED_PTR(T, *allocPtr));

		// リソース読み込み
		return _loadResource(param, resPtr, handle);
	}

}	// namespace app

#endif	//__APP_RESOURCE_SYSTEM_H__
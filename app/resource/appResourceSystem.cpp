/*!
* @file		appResourceSystem.cpp
* @brief	リソースシステム
* @date		2020-07-22
* @author	s.fukami
*/

#include "ngLibCore/io/file/ngFile.h"
#include "appResourceSystem.h"
#include "../graphic/texture/appTexture.h"
#include "../graphic/shader/appShader.h"
#include "app/memory/appMemoryUtil.h"

//! ログ出力有効
#define _ENABLE_LOG
//! 作業用メモリアロケータ
#define _MEMALLOC_TEMP	(APP_GET_MEMALLOC(TEMP))

namespace app
{
	const ng::u32 CResourceSystem::ResKeyLength = 256U;

	CResourceSystem::LoadParam::File::File()
		: File(nullptr)
	{ }
	CResourceSystem::LoadParam::File::File(const File& _file)
		: File(_file.filePath)
	{ }
	CResourceSystem::LoadParam::File::File(const char* _filePath)
		: filePath(_filePath)
	{ }
	bool CResourceSystem::LoadParam::File::IsValid() const
	{
		return (filePath != nullptr);
	}

	CResourceSystem::LoadParam::Binary::Binary()
		: Binary(nullptr, 0, nullptr)
	{ }
	CResourceSystem::LoadParam::Binary::Binary(const Binary& _binary)
		: Binary(_binary.pData, _binary.dataSize, _binary.owner)
	{ }
	CResourceSystem::LoadParam::Binary::Binary(const void* _pData, ng::u32 _dataSize, const char* _owner)
		: pData(_pData), dataSize(_dataSize), owner(_owner)
	{ }
	bool CResourceSystem::LoadParam::Binary::IsValid() const
	{
		return (pData != nullptr);
	}

	CResourceSystem::LoadParam::LoadParam(
		const File& _file, const char* _resName, eResourceMemoryType _resMemType, const void* _pBuildParam
		)
		: file(_file), resName(_resName), resMemType(_resMemType), pBuildParam(_pBuildParam)
	{ }
	CResourceSystem::LoadParam::LoadParam(
		const Binary& _binary, const char* _resName, eResourceMemoryType _resMemType, const void* _pBuildParam
		)
		: binary(_binary), resName(_resName), resMemType(_resMemType), pBuildParam(_pBuildParam)
	{ }

	CResourceSystem::CResourceSystem()
	{
	}
	CResourceSystem::~CResourceSystem()
	{
		Finalize();
	}

	bool CResourceSystem::Initialize(ng::IMemoryAllocator& alloc, unsigned int resMax)
	{
		// リソースメモリ初期化
		if(!m_resMem.Initialize(alloc)) {
			NG_ERRLOG("ResourceSystem", "リソースメモリの初期化に失敗しました.");
			return false;
		}

		// リソース管理初期化
		{
			auto allocPtr = m_resMem.GetAllocator(eResourceMemoryType::MANAGE);
			NG_ASSERT_NOT_NULL(allocPtr);

			NG_ERRCODE err = NG_ERRCODE_DEFAULT;

			if(NG_FAILED(err = m_resMngr.Initialize(*allocPtr, resMax))) {
				NG_ERRLOG_C("ResourceSystem", err, "リソース管理の初期化に失敗しました.");
				return false;
			}
		}

		return true;
	}

	void CResourceSystem::Finalize()
	{
		m_resMngr.Finalize();
		m_resMem.Finalize();
	}

	bool CResourceSystem::_findResource(const LoadParam& param, ng::IResourceHandle& handle) const
	{
		char resKey[ResKeyLength] = "";

		// リソースのキーを生成
		if(!_createResKey(param, resKey)) {
			NG_ERRLOG("ResourceSystem", "リソースのキーの生成に失敗しました.");
			return false;
		}

		// 既にリソースが存在する場合は、それを返却
		if(m_resMngr.TryGet(resKey, handle)) {
			return true;
		}

		return false;
	}

	bool CResourceSystem::_loadResource(const LoadParam& param, ng::CSharedPtr<ng::IResource>& resPtr, ng::IResourceHandle& handle)
	{
		NG_ASSERT_NOT_NULL(resPtr);

		bool result = false;

		// リソース構築
		if(param.file.IsValid()) {
			void* pFileData = nullptr;
			ng::size_type fileSize = 0;
			result = _loadFile(param.file.filePath, &pFileData, &fileSize);
			if(result) {
				result = resPtr->Build(pFileData, fileSize, param.pBuildParam);
			}
			NG_DELETE_BYTE(_MEMALLOC_TEMP, pFileData);
		}
		else if(param.binary.IsValid()) {
			result = resPtr->Build(param.binary.pData, param.binary.dataSize, param.pBuildParam);
		}
		else {
			NG_ERRLOG("ResourceSystem", "パラメータが無効のため、リソースの読み込みに失敗しました.");
		}

		// リソース登録
		if(result) {
			result = _addResource(param, resPtr, handle);
		}

	#if defined(_ENABLE_LOG)
		if(result) {
			if(param.file.IsValid()) {
				NG_DPRINTF("[CResourceSystem] Load file. filePath:%s, resName:%s", param.file.filePath, (param.resName ? param.resName : ""));
			}
			else if(param.binary.IsValid()) {
				NG_DPRINTF("[CResourceSystem] Load binary. owner:%s, resName:%s", param.binary.owner, param.resName);
			}
			NG_DPRINTF(", resMemType:%d, resourceType:%d\n", param.resMemType, resPtr->GetResourceType());
		}
	#endif
		return result;
	}

	bool CResourceSystem::_addResource(const LoadParam& param, ng::CSharedPtr<ng::IResource>& resPtr, ng::IResourceHandle& handle)
	{
		char resKey[ResKeyLength] = "";

		// リソースのキーを生成
		if(!_createResKey(param, resKey)) {
			NG_ERRLOG("ResourceSystem", "リソースのキーの生成に失敗しました.");
			return false;
		}

		// リソース登録
		if(!m_resMngr.Add(resKey, resPtr, &handle)) {
			NG_ERRLOG("ResourceSystem", "リソース登録に失敗しました. resKey:%s", resKey);
			return false;
		}

		return true;
	}

	bool CResourceSystem::_loadFile(const char* fileName, void** ppData, ng::size_type* pDataSize) const
	{
		ng::CFile file;

		// ファイルオープン
		{
			NG_ERRCODE err = NG_ERRCODE_DEFAULT;
			if(NG_FAILED(err = file.Open(fileName, "rb"))) {
				NG_ERRLOG_C("ResourceSystem", err, "ファイルオープンに失敗しました. fileName:%s", fileName);
				return false;
			}
		}

		// ファイル読み込み
		ng::size_type fileSize = file.GetFileSize();
		void* pFileData = NG_NEW_BYTE(_MEMALLOC_TEMP, fileSize);

		if(!file.ReadAll(pFileData)) {
			NG_ERRLOG("ResourceSystem", "ファイル読み込みに失敗しました. fileName:%s", fileName);
			NG_DELETE_BYTE(_MEMALLOC_TEMP, pFileData);
			return false;
		}

		(*ppData) = pFileData;
		(*pDataSize) = fileSize;

		return true;
	}

	bool CResourceSystem::_createResKey(const LoadParam& param, char* pDst) const
	{
		NG_ASSERT_NOT_NULL(pDst);

		// ファイルが有効の場合
		if(param.file.IsValid()) {
			// リソース名がある場合は、「ファイルパス:リソース名」とする
			if(param.resName != nullptr)
				NG_SPRINTF(pDst, "%s:%s", param.file.filePath, param.resName);
			else
				NG_STRCPY(pDst, param.file.filePath);
		}
		// バイナリが有効の場合
		else if(param.binary.IsValid()) {
			// 「所有者:リソース名」とする
			if(param.binary.owner != nullptr && param.resName != nullptr) {
				NG_SPRINTF(pDst, "%s:%s", param.binary.owner, param.resName);
			}
			else {
				NG_ERRLOG("ResourceSystem", "リソースキーの生成に失敗しました. owner:%s, resName:%s",
					(param.binary.owner ? param.binary.owner : ""),
					(param.resName ? param.resName : "")
					);
			}
		}
		else {
			NG_ERRLOG("ResourceSystem", "パラメータが無効のため、リソースキーの生成に失敗しました.");
			return false;
		}

		return true;
	}

}	// namespace app
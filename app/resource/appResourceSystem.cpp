/*!
* @file		appResourceSystem.cpp
* @brief	リソースシステム
* @date		2020-07-22
* @author	s.fukami
*/

#include <shlwapi.h>
#include "ngLibCore/io/file/ngFile.h"
#include "appResourceSystem.h"
#include "app/memory/appMemoryUtil.h"
#include "../graphic/texture/appTexture.h"
#include "../graphic/shader/appShader.h"

#pragma comment(lib, "shlwapi.lib")

//! ログ出力有効
#define _ENABLE_LOG

namespace app
{
	//! リソースの拡張子テーブル宣言
	#define _RESEXT_TABLE(_resName) \
		static const char* s_pExtTbl_##_resName[]

	_RESEXT_TABLE(Texture) = {".bmp"};	//!< テクスチャ
	_RESEXT_TABLE(Shader) = {".hlsl"};	//!< シェーダー

	//! リソース読み込み設定
	struct LoadSetting
	{
		using FuncType = bool(CResourceSystem::*)(const char*, ng::IMemoryAllocator&, const void*, ng::IResourceHandle&);

		const FuncType func;	//!< リソース読み込み関数
		const char** ppExtTable;	//!< 拡張子テーブル
		unsigned int extTableSize;	//!< 拡張子テーブルのサイズ
	};

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

	bool CResourceSystem::LoadResource(
		const char* fileName, eResourceMemoryType resMemType, const void* pBuildParam, ng::IResourceHandle& handle
		)
	{
		// 既にリソースが存在する場合は、それを返却
		if(m_resMngr.Get(fileName, handle)) {
			return true;
		}

		// ファイル拡張子取得
		const char* fileExt = ::PathFindExtensionA(fileName);
		if(NG_STRLEN(fileExt) <= 1) {
			NG_ERRLOG("ResourceSystem", "ファイル拡張子が見つかりませんでした. fileName:%s", fileName);
			return false;
		}

		bool result = false;
		auto allocPtr = m_resMem.GetAllocator(resMemType);

		//! リソース読み込み設定
		#define _LOAD_SETTING(_resName) \
			{ &CResourceSystem::_loadResource<C##_resName>, s_pExtTbl_##_resName, NG_ARRAY_SIZE(s_pExtTbl_##_resName) }

		static const LoadSetting s_loadSettings[] =
		{
			_LOAD_SETTING(Texture),
			_LOAD_SETTING(Shader),
		};

		// 拡張子が一致したリソースを読み込み
		for(unsigned int i = 0; i < NG_ARRAY_SIZE(s_loadSettings); i++)
		{
			const LoadSetting& setting = s_loadSettings[i];

			if(_checkExtTable(fileExt, setting.ppExtTable, setting.extTableSize)) {
				result = (this->*setting.func)(fileName, *allocPtr, pBuildParam, handle);
				break;
			}
		}

	#if defined(_ENABLE_LOG)
		if(result) {
			NG_DPRINTF("リソースの読み込みに成功しました. fileName:%s\n", fileName);
		} else {
			NG_DPRINTF("リソースの読み込みに失敗しました. fileName:%s\n", fileName);
		}
	#endif

		return result;
	}

	bool CResourceSystem::_checkExtTable(const char* ext, const char* pExtTable[], unsigned int tableSize) const
	{
		for(unsigned int i = 0; i < tableSize; i++)
		{
			if(NG_STRCMP(ext, pExtTable[i]) == 0) {
				return true;
			}
		}

		return false;
	}

	bool CResourceSystem::_loadFile(const char* fileName, void** ppFileData, ng::size_type* pFileSize)
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
		void* pFileData = NG_NEW_BYTE(APP_MEMALLOC_TEMP, fileSize);

		if(!file.ReadAll(pFileData)) {
			NG_ERRLOG("ResourceSystem", "ファイル読み込みに失敗しました. fileName:%s", fileName);
			NG_DELETE_BYTE(APP_MEMALLOC_TEMP, pFileData);
			return false;
		}

		(*ppFileData) = pFileData;
		(*pFileSize) = fileSize;

		return true;
	}

	bool CResourceSystem::_buildResource(
		ng::CSharedPtr<ng::IResource>& resPtr, const void* pFileData, ng::size_type fileSize, const void* pBuildParam
		)
	{
		bool result = resPtr->Build(pFileData, fileSize, pBuildParam);

		NG_DELETE_BYTE(APP_MEMALLOC_TEMP, pFileData);

		return result;
	}

	bool CResourceSystem::_addResource(
		const char* fileName, ng::CSharedPtr<ng::IResource>& resPtr, ng::IResourceHandle& handle
		)
	{
		if(!m_resMngr.Add(fileName, resPtr, &handle)) {
			NG_ERRLOG("ResourceSystem", "リソース追加に失敗しました. fileName:%s", fileName);
			return false;
		}

		return true;
	}

}	// namespace app
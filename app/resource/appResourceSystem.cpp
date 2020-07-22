/*!
* @file		appResourceSystem.cpp
* @brief	リソースシステム
* @date		2020-07-22
* @author	s.fukami
*/

#include "ngLibCore/io/file/ngFile.h"
#include "appResourceSystem.h"
#include "app/memory/appMemoryUtil.h"
#include "texture/appTexture.h"

namespace app
{
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
		const char* fileName, eResourceMemoryType resMemType, ng::IResourceHandle& handle
		)
	{
		bool result = false;

		// TODO: 拡張子で分岐

		// texture
		result = _loadTexture(fileName, resMemType, handle);

		return result;
	}

	bool CResourceSystem::_loadTexture(
		const char* fileName, eResourceMemoryType resMemType, ng::IResourceHandle& handle
		)
	{
		void* pFileData = nullptr;
		ng::size_type fileSize = 0;

		// ファイル読み込み
		{
			NG_ERRCODE err = NG_ERRCODE_DEFAULT;
			ng::CFile file;

			if(NG_FAILED(err = file.Open(fileName, "rb"))) {
				NG_ERRLOG_C("ResourceSystem", err, "画像ファイルのオープンに失敗しました. fileName:%s", fileName);
				return false;
			}

			fileSize = file.GetFileSize();
			pFileData = NG_NEW_BYTE(APP_MEMALLOC_TEMP, fileSize);

			ng::size_type dataNum = file.Read(pFileData, fileSize);
			if(dataNum == 0) {
				NG_ERRLOG("ResourceSystem", "画像ファイルの読み込みに失敗しました. fileName:%s", fileName);
				NG_DELETE(APP_MEMALLOC_TEMP, pFileData);
				return false;
			}
		}

		// リソース生成 & 構築
		auto allocPtr = m_resMem.GetAllocator(resMemType);
		auto texPtr = NG_MAKE_SHARED_PTR(CTexture, *allocPtr, CTexture);
		texPtr->Build(pFileData, fileSize);

		NG_DELETE(APP_MEMALLOC_TEMP, pFileData);

		// リソース追加
		if(!m_resMngr.Add<CTexture>(fileName, texPtr, &handle)) {
			NG_ERRLOG("ResourceSystem", "テクスチャのリソース追加に失敗しました.");
			return false;
		}

		return true;
	}

}	// namespace app
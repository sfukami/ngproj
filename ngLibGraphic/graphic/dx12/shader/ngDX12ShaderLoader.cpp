/*!
* @file		ngDX12ShaderLoader.h
* @brief	DX12シェーダーローダー
* @date		2020-07-23
* @author	s.fukami
*/

#include <d3d12.h>
#include <d3dx12.h>
#include <D3Dcompiler.h>
#include "ngLibCore/common/ngCommon.h"
#include "ngLibCore/allocator/ngMemoryAllocator.h"
#include "ngLibCore/io/file/ngFile.h"
#include "../common/ngDX12Common.h"
#include "ngDX12ShaderLoader.h"
#include "ngDX12Shader.h"

namespace ng
{
	//! シェーダーコンパイルのデバッグフラグ
	#define _COMPILE_DBGFLAG	(D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION)

	CDX12ShaderLoader::CDX12ShaderLoader()
	{
	}
	CDX12ShaderLoader::~CDX12ShaderLoader()
	{
	}

	NG_ERRCODE CDX12ShaderLoader::LoadShaderFromFile(
		CDX12Shader& dst,
		const wchar_t* pFileName,
		const char* pEntryPoint,
		const char* pTarget,
		u32 flags,
		bool isDebugCompile
		) const
	{
	#if defined(NG_DEBUG)
		// デバッグコンパイルオプション
		// デバッグ時はシェーダーデバッグ有効、最適化無効
		if(isDebugCompile) {
			flags |= (_COMPILE_DBGFLAG);
		}
	#endif

		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// シェーダーコンパイル
		ID3D10Blob* pIBlob = nullptr;
		ID3DBlob* pIError = nullptr;
		if(NG_FAILED(ret = D3DCompileFromFile(
			pFileName,
			nullptr,
			nullptr,
			pEntryPoint,
			pTarget,
			flags,
			0,
			&pIBlob,
			&pIError
			))) {
			NG_DXERRLOG("DX12ShaderLoader", ret, D3DCompileFromFile, "シェーダーのコンパイルに失敗しました. pFilename:%ls, pEntryPoint:%s, pTarget:%s, pIError:%s", 
				pFileName, pEntryPoint, pTarget,
				pIError ? PointerCast<const char*>(pIError->GetBufferPointer()) : "none"
				);
			return ret;
		}

		// DX12シェーダー生成
		if(NG_FAILED(ret = dst.Create(pIBlob))) {
			NG_ERRLOG_C("DX12ShaderLoader", ret, "DX12シェーダーの生成に失敗しました. pFilename:%ls, pEntryPoint:%s, pTarget:%s",
				pFileName, pEntryPoint, pTarget);
		}

		NG_SAFE_RELEASE(pIBlob);
		
		return ret;
	}

	NG_ERRCODE CDX12ShaderLoader::LoadShaderFromMemory(
		CDX12Shader& dst,
		const void* pSrcData,
		size_type dataSize,
		const wchar_t* pFileName,
		const char* pEntryPoint,
		const char* pTarget,
		u32 flags,
		bool isDebugCompile
		) const
	{
	#if defined(NG_DEBUG)
		// デバッグコンパイルオプション
		// デバッグ時はシェーダーデバッグ有効、最適化無効
		if(isDebugCompile) {
			flags |= (_COMPILE_DBGFLAG);
		}
	#endif

		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// シェーダーコンパイル
		ID3D10Blob* pIBlob = nullptr;
		ID3DBlob* pIError = nullptr;
		if(NG_FAILED(ret = D3DCompile(
			pSrcData,
			dataSize,
			nullptr,
			nullptr,
			nullptr,
			pEntryPoint,
			pTarget,
			flags,
			0,
			&pIBlob,
			&pIError
			))) {
			NG_DXERRLOG("DX12Shader", ret, D3DCompile, "シェーダーのコンパイルに失敗しました. pSrcData:%P, pTarget:%s, pIError:%s", 
				pSrcData, pEntryPoint, pTarget,
				pIError ? PointerCast<const char*>(pIError->GetBufferPointer()) : "none"
				);
			return ret;
		}

		// DX12シェーダー生成
		if(NG_FAILED(ret = dst.Create(pIBlob))) {
			NG_ERRLOG_C("DX12ShaderLoader", ret, "DX12シェーダーの生成に失敗しました. pSrcData:%P, pEntryPoint:%s, pTarget:%s",
				pSrcData, pEntryPoint, pTarget);
		}

		NG_SAFE_RELEASE(pIBlob);

		return ret;
	}

	NG_ERRCODE CDX12ShaderLoader::LoadShaderFromFileCompiled(
		IMemoryAllocator& alloc,
		CDX12Shader& dst,
		const wchar_t* pFileName
		) const
	{

		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// シェーダーファイルオープン
		CFile file;
		if(NG_FAILED(ret = file.Open(pFileName, L"rb"))) {
			NG_ERRLOG_C("DX12ShaderLoader", ret, "シェーダーファイルのファイルオープンに失敗しました. pFileName:%ls", pFileName);
			return ret;
		}

		// シェーダーファイル読み込み
		size_type fileSize = file.GetFileSize();
		char* pBuf = NG_NEW_BYTE(alloc, fileSize);

		if(file.Read(pBuf, fileSize) != 1) {
			NG_ERRLOG("DX12ShaderLoader", "シェーダーファイルの読み込みに失敗しました. pFileName:%ls", pFileName);
			return eNG_E_UNKNOWN;
		}

		ret = LoadShaderFromMemoryCompiled(dst, pBuf, fileSize);

		NG_DELETE_BYTE(alloc, pBuf);

		return ret;
	}

	NG_ERRCODE CDX12ShaderLoader::LoadShaderFromMemoryCompiled(
		CDX12Shader& dst,
		const void* pSrcData,
		size_type dataSize
		) const
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// DX12シェーダー生成
		if(NG_FAILED(ret = dst.Create(pSrcData, dataSize))) {
			NG_ERRLOG_C("DX12ShaderLoader", ret, "DX12シェーダーの生成に失敗しました. pSrcData:%P", pSrcData);
		}

		return ret;
	}

}	// namespace ng
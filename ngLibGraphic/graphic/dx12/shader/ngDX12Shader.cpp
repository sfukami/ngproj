/*!
* @file		ngDX12Shader.cpp
* @brief	DX12シェーダー
* @date		2017-09-25
* @author	s.fukami
*/

#include <d3d12.h>
#include <d3dx12.h>
#include <D3Dcompiler.h>
#include "ngLibCore/common/ngCommon.h"
#include "../common/ngDX12Common.h"
#include "ngDX12Shader.h"

namespace ng
{
	CDX12Shader::CDX12Shader()
		: m_pIBlob(nullptr)
	{
	}

	CDX12Shader::~CDX12Shader()
	{
		Destroy();
	}

	NG_ERRCODE CDX12Shader::Create(
		const wchar_t* pFilename,
		const char* pEntryPoint,
		const char* pTarget,
		u32 flags,
		bool isDebugCompile
		)
	{
		NG_ASSERT(!IsValid());

		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

	#if defined(NG_DEBUG)
		// デバッグコンパイルオプション
		// デバッグ時はシェーダーデバッグ有効、最適化無効
		if(isDebugCompile) {
			flags |= (D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION);
		}
	#endif

		// シェーダーコンパイル
		ID3DBlob* pIError = nullptr;
		if(NG_FAILED(ret = D3DCompileFromFile(
			pFilename,
			nullptr,
			nullptr,
			pEntryPoint,
			pTarget,
			flags,
			0,
			&m_pIBlob,
			&pIError
			))) {
			NG_DXERRLOG("DX12Shader", ret, D3DCompileFromFile, "シェーダーのコンパイルに失敗しました. pFilename:%ls, pEntryPoint:%s, pTarget:%s, pIError:%s", 
				pFilename, pEntryPoint, pTarget,
				pIError ? PointerCast<const char*>(pIError->GetBufferPointer()) : "none"
				);
			return ret;
		}
		
		return ret;
	}

	bool CDX12Shader::IsValid() const
	{
		return (m_pIBlob != nullptr);
	}

	void CDX12Shader::Destroy()
	{
		NG_SAFE_RELEASE(m_pIBlob);
	}
	
	ID3DBlob* CDX12Shader::Interface()
	{
		return m_pIBlob;
	}
	const ID3DBlob* CDX12Shader::Interface() const
	{
		return m_pIBlob;
	}

}	// namespace ng
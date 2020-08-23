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
		const void* pCompiled,
		size_type dataSize
		)
	{
		NG_ASSERT(!IsValid());
		NG_ASSERT_NOT_NULL(pCompiled);

		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// DX12ブロブ生成
		if(NG_FAILED(ret = D3DCreateBlob(dataSize, &m_pIBlob))) {
			NG_ERRLOG_C("Shader", ret, "DX12ブロブの生成に失敗しました.");
			return ret;
		}

		// シェーダーデータをコピー
		NG_MEMCPY(m_pIBlob->GetBufferPointer(), pCompiled, dataSize);

		return ret;
	}

	NG_ERRCODE CDX12Shader::Create(
		ID3D10Blob* pBlob
		)
	{
		NG_ASSERT(!IsValid());
		NG_ASSERT_NOT_NULL(pBlob);

		m_pIBlob = pBlob;
		m_pIBlob->AddRef();

		return eNG_S_OK;
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
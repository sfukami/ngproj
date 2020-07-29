/*!
* @file		appShader.cpp
* @brief	シェーダー
* @date		2020-07-23
* @author	s.fukami
*/

#include "ngLibGraphic/graphic/dx12/shader/ngDX12ShaderLoader.h"
#include "appShader.h"

namespace app
{
	CShader::BuildParam::BuildParam()
	{
		ng::ClearString(entryPoint);
		ng::ClearString(target);
	}

	CShader::BuildParam::BuildParam(const char* _entryPoint, const char* _target)
	{
		NG_STRCPY(entryPoint, _entryPoint);
		NG_STRCPY(target, _target);
	}

	CShader::CShader()
	{
	}
	CShader::~CShader()
	{
		Destroy();
	}

	bool CShader::Build(const void* pBinary, ng::size_type size, const void* pBuildParam)
	{
		const BuildParam* pShaderBuildParam = ng::PointerCast<const BuildParam*>(pBuildParam);

		NG_ERRCODE err = NG_ERRCODE_DEFAULT;
		ng::CDX12ShaderLoader loader;
		if(NG_FAILED(err = loader.LoadShaderFromMemory(
			m_shader,
			pBinary,
			size,
			nullptr,
			pShaderBuildParam->entryPoint,
			pShaderBuildParam->target,
			0,
			true
			))) {
			NG_ERRLOG_C("Shader", err, "シェーダーの読み込みに失敗しました.");
			return false;
		}

		return true;
	}

	void CShader::Destroy()
	{
		m_shader.Destroy();
	}

	ng::CDX12Shader& CShader::GetDX12Shader()
	{
		return m_shader;
	}
	const ng::CDX12Shader& CShader::GetDX12Shader() const
	{
		return m_shader;
	}

}	// namespace app
/*!
* @file		appShader.h
* @brief	シェーダー
* @date		2020-07-23
* @author	s.fukami
*/

#ifndef __APP_SHADER_H__
#define __APP_SHADER_H__

#include "ngLibApp/resource/ngResource.h"
#include "ngLibGraphic/graphic/dx12/shader/ngDX12Shader.h"

namespace app
{
	/*!
	* @brief					シェーダー
	*/
	class CShader : public ng::IResource
	{
	public:
		/*! ビルドパラメータ */
		struct BuildParam
		{
			BuildParam();
			BuildParam(const char* _entryPoint, const char* _target);

			char entryPoint[32];	//!< エントリポイント
			char target[8];			//!< ビルドターゲット
		};

	public:
		CShader();
		~CShader();

		/*!
		* @brief					リソース構築
		* @param pBinary			リソースバイナリ
		* @param size				リソースバイナリのサイズ
		* @param pBuildParam		ビルドパラメータ
		* @return					成否
		*/
		bool Build(const void* pBinary, ng::size_type size, const void* pBuildParam);

		/*!
		* @brief					破棄
		*/
		void Destroy();

	private:
		ng::CDX12Shader m_shader;	//!< DX12シェーダー
	};

}	// namespace app

#endif	// __APP_SHADER_H__
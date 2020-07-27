﻿/*!
* @file		appShaderEffectTexture.h
* @brief	シェーダーエフェクト テクスチャ描画
* @date		2020-07-28
* @author	s.fukami
*/

#ifndef __APP_SHADER_EFFECT_TEXTURE_H__
#define __APP_SHADER_EFFECT_TEXTURE_H__

#include "ngLibCore/geometry/ngGeometry.h"
#include "ngLibGraphic/graphic/dx12/shader/ngDX12ConstantBuffer.h"
#include "ngLibApp/resource/ngResourceHandle.h"
#include "appShaderEffect.h"

namespace ng
{
	class CDX12Device;
	class CDX12DescriptorHeap;
}

namespace app
{
	/*!
	* @brief					シェーダーエフェクト テクスチャ描画
	*/
	class CShaderEffectTexture : public CShaderEffect
	{
	public:
		CShaderEffectTexture();
		~CShaderEffectTexture();

		/*!
		* @brief					生成
		* @param device				DX12デバイス
		* @param descHeap			DX12ディスクリプタヒープ
		* @return					NG エラーコード
		*/
		NG_ERRCODE Create(
			ng::CDX12Device& device,
			ng::CDX12DescriptorHeap& descHeap
			);

		/*!
		* @brief					破棄
		*/
		void Destroy();

		/*!
		* @brief					コンスタントバッファ更新
		*/
		void UpdateConstantBuffer();
		
		/*! ワールドビュープロジェクション行列設定 */
		void SetWVPMatrix(const ng::Matrix4& mat);

	private:
		//! シェーダーパラメータ
		struct ShaderParam
		{
			ng::Matrix4 matWVP;
		};

	private:
		ng::CDX12ConstantBuffer m_cb;	//!< DX12コンスタントバッファ
		ShaderParam m_shPrm;	//!< シェーダーパラメータ
	};

}	// namespace app

#endif	// __APP_SHADER_EFFECT_TEXTURE_H__
﻿/*!
* @file		appShaderEffectSprite.h
* @brief	シェーダーエフェクト スプライト描画
* @date		2020-07-28
* @author	s.fukami
*/

#ifndef __APP_SHADER_EFFECT_SPRITE_H__
#define __APP_SHADER_EFFECT_SPRITE_H__

#include "ngLibGraphic/graphic/dx12/descriptor/ngDX12DescriptorHeap.h"
#include "ngLibGraphic/graphic/dx12/shader/ngDX12ConstantBuffer.h"
#include "appShaderEffect.h"
#include "appShaderParam.h"

namespace ng
{
	class CDX12Device;
	class CDX12CommandList;
}

namespace app
{
	/*!
	* @brief					シェーダーエフェクト スプライト描画
	*/
	class CShaderEffectSprite : public CShaderEffect
	{
	public:
		CShaderEffectSprite();
		~CShaderEffectSprite();

		/*!
		* @brief					生成
		* @param device				DX12デバイス
		* @return					成否
		*/
		bool Create(ng::CDX12Device& device);

		/*!
		* @brief					破棄
		*/
		void Destroy();

		/*!
		* @brief					パラメータ設定
		*/
		void SetParameter(const ShaderParam& param);

		/*!
		* @brief					コンスタントバッファ更新
		*/
		void UpdateConstantBuffer();
		
		/*!
		* @brief					リソースをバインド
		* @param commandList		DX12コマンドリスト
		*/
		void BindResource(ng::CDX12CommandList& commandList);

		/*!
		* @brief					名称取得
		*/
		static const char* GetName();

	private:
		ng::CDX12DescriptorHeap m_descHeap;	//!< DX12ディスクリプタヒープ
		ng::CDX12ConstantBuffer m_cb;	//!< DX12コンスタントバッファ
		ShaderParam m_param;	//!< パラメータ
	};

}	// namespace app

#endif	// __APP_SHADER_EFFECT_SPRITE_H__
/*!
* @file		appRootSignatureDescSprite.h
* @brief	ルートシグネチャ記述子
* @date		2020-07-24
* @author	s.fukami
*/

#ifndef __APP_ROOT_SIGNATURE_DESC_SPRITE_H__
#define __APP_ROOT_SIGNATURE_DESC_SPRITE_H__

#include <d3dx12.h>

struct CD3DX12_ROOT_SIGNATURE_DESC;

namespace app
{
	/*!
	* @brief					ルートシグネチャ記述子 スプライト用
	*/
	class CRootSignatureDescSprite : public CD3DX12_ROOT_SIGNATURE_DESC
	{
	public:
		CRootSignatureDescSprite();

	private:
		CD3DX12_DESCRIPTOR_RANGE m_cbRange;		//!< DX12ディスクリプタレンジ コンスタントバッファ
		CD3DX12_DESCRIPTOR_RANGE m_texRange;	//!< DX12ディスクリプタレンジ テクスチャ
		CD3DX12_ROOT_PARAMETER m_rootParams[2];	//!< DX12ルートパラメータ
		CD3DX12_STATIC_SAMPLER_DESC m_samplerDesc;	//!< DX12サンプラー記述子
	};

}	// namespace app

#endif	// __APP_ROOT_SIGNATURE_DESC_SPRITE_H__
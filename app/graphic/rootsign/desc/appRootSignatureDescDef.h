/*!
* @file		appRootSignatureDescDef.h
* @brief	ルートシグネチャ記述子 定義
* @date		2020-07-24
* @author	s.fukami
*/

#ifndef __APP_ROOT_SIGNATURE_DESC_DEF_H__
#define __APP_ROOT_SIGNATURE_DESC_DEF_H__

#include <d3dx12.h>

struct CD3DX12_ROOT_SIGNATURE_DESC;

namespace app
{
	/*!
	* @brief					ルートシグネチャ記述子 基底クラス
	*/
	class CRootSignatureDescBase : public CD3DX12_ROOT_SIGNATURE_DESC
	{
	public:
		CRootSignatureDescBase(const char* name);
		virtual ~CRootSignatureDescBase();

		/*! 名称取得 */
		const char* GetName() const;

	private:
		char m_name[32];	//!< 名称
	};

	/*!
	* @brief					ルートシグネチャ記述子 スプライト用
	*/
	class CRootSignatureDescSprite : public CRootSignatureDescBase
	{
	public:
		CRootSignatureDescSprite();

	private:
		CD3DX12_DESCRIPTOR_RANGE m_cbRange;		//!< DX12ディスクリプタレンジ コンスタントバッファ
		CD3DX12_DESCRIPTOR_RANGE m_texRange;	//!< DX12ディスクリプタレンジ テクスチャ
		CD3DX12_ROOT_PARAMETER m_rootParams[2];	//!< DX12ルートパラメータ
		CD3DX12_STATIC_SAMPLER_DESC m_samplerDesc;	//!< DX12サンプラー記述子
	};

	/*!
	* @brief					ルートシグネチャ記述子 スプライト用 テクスチャ数:0
	*/
	class CRootSignatureDescSpriteT0 : public CRootSignatureDescBase
	{
	public:
		CRootSignatureDescSpriteT0();

	private:
		CD3DX12_DESCRIPTOR_RANGE m_cbRange;		//!< DX12ディスクリプタレンジ コンスタントバッファ
		CD3DX12_ROOT_PARAMETER m_rootParams[1];	//!< DX12ルートパラメータ
	};

	/*!
	* @brief					ルートシグネチャ記述子 スプライト用 テクスチャ数:1
	*/
	class CRootSignatureDescSpriteT1 : public CRootSignatureDescBase
	{
	public:
		CRootSignatureDescSpriteT1();

	private:
		CD3DX12_DESCRIPTOR_RANGE m_cbRange;		//!< DX12ディスクリプタレンジ コンスタントバッファ
		CD3DX12_DESCRIPTOR_RANGE m_texRange;	//!< DX12ディスクリプタレンジ テクスチャ
		CD3DX12_ROOT_PARAMETER m_rootParams[2];	//!< DX12ルートパラメータ
		CD3DX12_STATIC_SAMPLER_DESC m_samplerDesc;	//!< DX12サンプラー記述子
	};

	/*!
	* @brief					ルートシグネチャ記述子 モデル用
	*/
	class CRootSignatureDescModel : public CRootSignatureDescBase
	{
	public:
		CRootSignatureDescModel();

	private:
		CD3DX12_DESCRIPTOR_RANGE m_cbRange;		//!< DX12ディスクリプタレンジ コンスタントバッファ
		CD3DX12_DESCRIPTOR_RANGE m_texRange;	//!< DX12ディスクリプタレンジ テクスチャ
		CD3DX12_ROOT_PARAMETER m_rootParams[2];	//!< DX12ルートパラメータ
		CD3DX12_STATIC_SAMPLER_DESC m_samplerDesc;	//!< DX12サンプラー記述子
	};

}	// namespace app

#endif	// __APP_ROOT_SIGNATURE_DESC_DEF_H__
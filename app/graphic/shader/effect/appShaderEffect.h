/*!
* @file		appShaderEffect.h
* @brief	シェーダーエフェクト 基底クラス
* @date		2020-07-28
* @author	s.fukami
*/

#ifndef __APP_SHADER_EFFECT_H__
#define __APP_SHADER_EFFECT_H__

namespace ng
{
	class CDX12CommandList;
}

namespace app
{
	/*!
	* @brief					シェーダーエフェクト 基底クラス
	*/
	class CShaderEffect
	{
	public:
		CShaderEffect();
		virtual ~CShaderEffect();

		/*!
		* @brief					コンスタントバッファ更新
		*/
		virtual void UpdateConstantBuffer();

		/*!
		* @brief					リソースをバインド
		* @param commandList		DX12コマンドリスト
		*/
		virtual void BindResource(ng::CDX12CommandList& commandList);
	};

}	// namespace app

#endif	// __APP_SHADER_EFFECT_H__